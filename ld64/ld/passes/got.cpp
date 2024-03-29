/* -*- mode: C++; c-basic-offset: 4; tab-width: 4 -*-
 *
 * Copyright (c) 2009 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */


#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <dlfcn.h>

#include <vector>
#include <map>
#include <ext/hash_map>

#include "ld.hpp"
#include "got.h"

namespace ld {
namespace passes {
namespace got {

class File; // forward reference

class GOTEntryAtom : public ld::Atom {
public:
											GOTEntryAtom(ld::Internal& internal, const ld::Atom* target, bool weakImport)
				: ld::Atom(_s_section, ld::Atom::definitionRegular, ld::Atom::combineNever,
							ld::Atom::scopeLinkageUnit, ld::Atom::typeNonLazyPointer, 
							symbolTableNotIn, false, false, false, ld::Atom::Alignment(3)), 
				_fixup(0, ld::Fixup::k1of1, ld::Fixup::kindStoreTargetAddressLittleEndian64, target),
				_target(target)
					{ _fixup.weakImport = weakImport; internal.addAtom(*this); }

	virtual const ld::File*					file() const					{ return NULL; }
	virtual bool							translationUnitSource(const char** dir, const char**) const 
																			{ return false; }
	virtual const char*						name() const					{ return _target->name(); }
	virtual uint64_t						size() const					{ return 8; }
	virtual uint64_t						objectAddress() const			{ return 0; }
	virtual void							copyRawContent(uint8_t buffer[]) const { }
	virtual void							setScope(Scope)					{ }
	virtual ld::Fixup::iterator				fixupsBegin() const				{ return &_fixup; }
	virtual ld::Fixup::iterator				fixupsEnd()	const 				{ return &((ld::Fixup*)&_fixup)[1]; }

private:
	mutable ld::Fixup						_fixup;
	const ld::Atom*							_target;
	
	static ld::Section						_s_section;
};

ld::Section GOTEntryAtom::_s_section("__DATA", "__got", ld::Section::typeNonLazyPointer);


static bool gotFixup(const Options& opts, ld::Internal& internal, const ld::Atom* targetOfGOT, const ld::Fixup* fixup, bool* optimizable)
{
	switch (fixup->kind) {
		case ld::Fixup::kindStoreTargetAddressX86PCRel32GOTLoad:
			// start by assuming this can be optimized
			*optimizable = true;
			// cannot do LEA optimization if target is in another dylib
			if ( targetOfGOT->definition() == ld::Atom::definitionProxy ) 
				*optimizable = false;
			// cannot do LEA optimization if target in __huge section
			if ( internal.usingHugeSections && (targetOfGOT->size() > 1024*1024)
											&& (   (targetOfGOT->section().type() == ld::Section::typeZeroFill)
												|| (targetOfGOT->section().type() == ld::Section::typeTentativeDefs)) ) {
				*optimizable = false;
			}
			if ( targetOfGOT->scope() == ld::Atom::scopeGlobal ) {	
				// cannot do LEA optimization if target is weak exported symbol
				if ( (targetOfGOT->definition() == ld::Atom::definitionRegular) && (targetOfGOT->combine() == ld::Atom::combineByName) )
					*optimizable = false;
				// cannot do LEA optimization if target is interposable
				if ( opts.interposable(targetOfGOT->name()) ) 
					*optimizable = false;
				// cannot do LEA optimization if target is resolver function
				if ( targetOfGOT->contentType() == ld::Atom::typeResolver ) 
					*optimizable = false;
				// cannot do LEA optimization for flat-namespace
				if ( opts.nameSpace() != Options::kTwoLevelNameSpace ) 
					*optimizable = false;
			}
			return true;
		case ld::Fixup::kindStoreX86PCRel32GOT:
			*optimizable = false;
			return true;
		default:
			break;
	}
	
	return false;
}

struct AtomByNameSorter
{
	 bool operator()(const ld::Atom* left, const ld::Atom* right)
	 {
		  return (strcmp(left->name(), right->name()) < 0);
	 }
};

void doPass(const Options& opts, ld::Internal& internal)
{
	const bool log = false;
	
	// only make got section in final linked images
	if ( opts.outputKind() == Options::kObjectFile )
		return;

	// walk all atoms and fixups looking for stubable references
	// don't create stubs inline because that could invalidate the sections walk
	std::vector<const ld::Atom*> atomsReferencingGOT;
	std::map<const ld::Atom*,ld::Atom*> gotMap;
	std::map<const ld::Atom*,bool>		weakImportMap;
	atomsReferencingGOT.reserve(128);
	for (std::vector<ld::Internal::FinalSection*>::iterator sit=internal.sections.begin(); sit != internal.sections.end(); ++sit) {
		ld::Internal::FinalSection* sect = *sit;
		for (std::vector<const ld::Atom*>::iterator ait=sect->atoms.begin();  ait != sect->atoms.end(); ++ait) {
			const ld::Atom* atom = *ait;
			bool atomUsesGOT = false;
			const ld::Atom* targetOfGOT = NULL;
			for (ld::Fixup::iterator fit = atom->fixupsBegin(), end=atom->fixupsEnd(); fit != end; ++fit) {
				if ( fit->firstInCluster() ) 
					targetOfGOT = NULL;
				switch ( fit->binding ) {
					case ld::Fixup::bindingsIndirectlyBound:
						targetOfGOT = internal.indirectBindingTable[fit->u.bindingIndex];
						break;
					case ld::Fixup::bindingDirectlyBound:
						targetOfGOT = fit->u.target;
						break;
                    default:
                        break;   
				}
				bool optimizable;
				if ( !gotFixup(opts, internal, targetOfGOT, fit, &optimizable) )
					continue;
				if ( optimizable ) {
					// change from load of GOT entry to lea of target
					if ( log ) fprintf(stderr, "optimized GOT usage in %s to %s\n", atom->name(), targetOfGOT->name());
					switch ( fit->binding ) {
						case ld::Fixup::bindingsIndirectlyBound:
						case ld::Fixup::bindingDirectlyBound:
							fit->binding = ld::Fixup::bindingDirectlyBound;
							fit->u.target = targetOfGOT;
							fit->kind = ld::Fixup::kindStoreTargetAddressX86PCRel32GOTLoadNowLEA;
							break;
						default:
							assert(0 && "unsupported GOT reference");
							break;
					}
				}
				else {
					// remember that we need to use GOT in this function
					if ( log ) fprintf(stderr, "found GOT use in %s to %s\n", atom->name(), targetOfGOT->name());
					if ( !atomUsesGOT ) {
						atomsReferencingGOT.push_back(atom);
						atomUsesGOT = true;
					}
					gotMap[targetOfGOT] = NULL;
					// record weak_import attribute
					std::map<const ld::Atom*,bool>::iterator pos = weakImportMap.find(targetOfGOT);
					if ( pos == weakImportMap.end() ) {
						// target not in weakImportMap, so add
						weakImportMap[targetOfGOT] = fit->weakImport;
						// <rdar://problem/5529626> If only weak_import symbols are used, linker should use LD_LOAD_WEAK_DYLIB
						const ld::dylib::File* dylib = dynamic_cast<const ld::dylib::File*>(targetOfGOT->file());
						if ( dylib != NULL ) {
							if ( fit->weakImport )
								(const_cast<ld::dylib::File*>(dylib))->setUsingWeakImportedSymbols();
							else
								(const_cast<ld::dylib::File*>(dylib))->setUsingNonWeakImportedSymbols();
						}
					}
					else {
						// target in weakImportMap, check for weakness mismatch
						if ( pos->second != fit->weakImport ) {
							// found mismatch
							switch ( opts.weakReferenceMismatchTreatment() ) {
								case Options::kWeakReferenceMismatchError:
									throwf("mismatching weak references for symbol: %s", targetOfGOT->name());
								case Options::kWeakReferenceMismatchWeak:
									pos->second = true;
									break;
								case Options::kWeakReferenceMismatchNonWeak:
									pos->second = false;
									break;
							}
						}
					}
				}
			}
		}
	}
	
	// make GOT entries	
	for (std::map<const ld::Atom*,ld::Atom*>::iterator it = gotMap.begin(); it != gotMap.end(); ++it) {
		it->second = new GOTEntryAtom(internal, it->first, weakImportMap[it->first]);
	}
	
	// update atoms to use GOT entries
	for (std::vector<const ld::Atom*>::iterator it=atomsReferencingGOT.begin(); it != atomsReferencingGOT.end(); ++it) {
		const ld::Atom* atom = *it;
		const ld::Atom* targetOfGOT = NULL;
		ld::Fixup::iterator fitThatSetTarget = NULL;
		for (ld::Fixup::iterator fit = atom->fixupsBegin(), end=atom->fixupsEnd(); fit != end; ++fit) {
			if ( fit->firstInCluster() ) {
				targetOfGOT = NULL;
				fitThatSetTarget = NULL;
			}
			switch ( fit->binding ) {
				case ld::Fixup::bindingsIndirectlyBound:
					targetOfGOT = internal.indirectBindingTable[fit->u.bindingIndex];
					fitThatSetTarget = fit;
					break;
				case ld::Fixup::bindingDirectlyBound:
					targetOfGOT = fit->u.target;
					fitThatSetTarget = fit;
					break;
                default:
                    break;    
			}
			bool optimizable;
			if ( (targetOfGOT == NULL) || !gotFixup(opts, internal, targetOfGOT, fit, &optimizable) )
				continue;
			if ( !optimizable ) {
				// GOT use not optimized away, update to bind to GOT entry
				assert(fitThatSetTarget != NULL);
				switch ( fitThatSetTarget->binding ) {
					case ld::Fixup::bindingsIndirectlyBound:
					case ld::Fixup::bindingDirectlyBound:
						fitThatSetTarget->binding = ld::Fixup::bindingDirectlyBound;
						fitThatSetTarget->u.target = gotMap[targetOfGOT];
						break;
					default:
						assert(0 && "unsupported GOT reference");
						break;
				}
			}
		}
	}
	
	// sort new atoms so links are consistent
	for (std::vector<ld::Internal::FinalSection*>::iterator sit=internal.sections.begin(); sit != internal.sections.end(); ++sit) {
		ld::Internal::FinalSection* sect = *sit;
		if ( sect->type() == ld::Section::typeNonLazyPointer ) {
			std::sort(sect->atoms.begin(), sect->atoms.end(), AtomByNameSorter());
		}
	}
}


} // namespace got
} // namespace passes 
} // namespace ld 
