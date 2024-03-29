/* -*- mode: C++; c-basic-offset: 4; tab-width: 4 -*-
 *
 * Copyright (c) 2005-2010 Apple  Inc. All rights reserved.
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

#ifndef __OPTIONS__
#define __OPTIONS__


#include <stdint.h>
#include <mach/machine.h>

#include <vector>
#include <ext/hash_set>
#include <ext/hash_map>

#include "ld.hpp"

extern void throwf (const char* format, ...) __attribute__ ((noreturn,format(printf, 1, 2)));
extern void warning(const char* format, ...) __attribute__((format(printf, 1, 2)));

class LibraryOptions
{
public:
	LibraryOptions() : fWeakImport(false), fReExport(false), fBundleLoader(false), 
						fLazyLoad(false), fUpward(false), fForceLoad(false) {}
	// for dynamic libraries
	bool		fWeakImport;
	bool		fReExport;
	bool		fBundleLoader;
	bool		fLazyLoad;
	bool		fUpward;
	// for static libraries
	bool		fForceLoad;
};



//
// The public interface to the Options class is the abstract representation of what work the linker
// should do.
//
// This abstraction layer will make it easier to support a future where the linker is a shared library
// invoked directly from Xcode.  The target settings in Xcode would be used to directly construct an Options
// object (without building a command line which is then parsed).
//
//
class Options
{
public:
	Options(int argc, const char* argv[]);
	~Options();

	enum OutputKind { kDynamicExecutable, kStaticExecutable, kDynamicLibrary, kDynamicBundle, kObjectFile, kDyld, kPreload, kKextBundle };
	enum NameSpace { kTwoLevelNameSpace, kFlatNameSpace, kForceFlatNameSpace };
	// Standard treatment for many options.
	enum Treatment { kError, kWarning, kSuppress, kNULL, kInvalid };
	enum UndefinedTreatment { kUndefinedError, kUndefinedWarning, kUndefinedSuppress, kUndefinedDynamicLookup };
	enum WeakReferenceMismatchTreatment { kWeakReferenceMismatchError, kWeakReferenceMismatchWeak,
										  kWeakReferenceMismatchNonWeak };
	enum CommonsMode { kCommonsIgnoreDylibs, kCommonsOverriddenByDylibs, kCommonsConflictsDylibsError };
	enum UUIDMode { kUUIDNone, kUUIDRandom, kUUIDContent };
	enum LocalSymbolHandling { kLocalSymbolsAll, kLocalSymbolsNone, kLocalSymbolsSelectiveInclude, kLocalSymbolsSelectiveExclude };
	enum DebugInfoStripping { kDebugInfoNone, kDebugInfoMinimal, kDebugInfoFull };

	struct FileInfo {
		const char*				path;
		uint64_t				fileLen;
		time_t					modTime;
		LibraryOptions			options;
	};

	struct ExtraSection {
		const char*				segmentName;
		const char*				sectionName;
		const char*				path;
		const uint8_t*			data;
		uint64_t				dataLen;
		typedef ExtraSection* iterator;
		typedef const ExtraSection* const_iterator;
	};

	struct SectionAlignment {
		const char*				segmentName;
		const char*				sectionName;
		uint8_t					alignment;
	};

	struct OrderedSymbol {
		const char*				symbolName;
		const char*				objectFileName;
	};
	typedef const OrderedSymbol*	OrderedSymbolsIterator;

	struct SegmentStart {
		const char*				name;
		uint64_t				address;
	};
	
	struct SegmentSize {
		const char*				name;
		uint64_t				size;
	};
	
	struct SegmentProtect {
		const char*				name;
		uint32_t				max;
		uint32_t				init;
	};
	
	struct DylibOverride {
		const char*				installName;
		const char*				useInstead;
	};

	struct AliasPair {
		const char*			realName;
		const char*			alias;
	};

	typedef const char* const*	UndefinesIterator;

//	const ObjectFile::ReaderOptions&	readerOptions();
	const char*							outputFilePath() const { return fOutputFile; }
	const std::vector<FileInfo>&		getInputFiles() const { return fInputFiles; }

	cpu_type_t					architecture() const { return fArchitecture; }
	bool						preferSubArchitecture() const { return fHasPreferredSubType; }
	cpu_subtype_t				subArchitecture() const { return fSubArchitecture; }
	bool						allowSubArchitectureMismatches() const { return fAllowCpuSubtypeMismatches; }
	bool						forceCpuSubtypeAll() const { return fForceSubtypeAll; }
	const char*					architectureName() const { return fArchitectureName; }
	void						setArchitecture(cpu_type_t, cpu_subtype_t subtype);
	OutputKind					outputKind() const { return fOutputKind; }
	bool						prebind() const { return fPrebind; }
	bool						bindAtLoad() const { return fBindAtLoad; }
	NameSpace					nameSpace() const { return fNameSpace; }
	const char*					installPath() const;			// only for kDynamicLibrary
	uint32_t					currentVersion() const { return fDylibCurrentVersion; }		// only for kDynamicLibrary
	uint32_t					compatibilityVersion() const { return fDylibCompatVersion; }	// only for kDynamicLibrary
	const char*					entryName() const { return fEntryName; }		// only for kDynamicExecutable or kStaticExecutable
	const char*					executablePath();
	uint64_t					baseAddress() const { return fBaseAddress; }
	uint64_t					maxAddress() const { return fMaxAddress; }
	bool						keepPrivateExterns() const { return fKeepPrivateExterns; }		// only for kObjectFile
	bool						needsModuleTable() const { return fNeedsModuleTable; }			// only for kDynamicLibrary
	bool						interposable(const char* name) const;
	bool						hasExportRestrictList() const { return (fExportMode != kExportDefault); }	// -exported_symbol or -unexported_symbol
	bool						hasExportMaskList() const { return (fExportMode == kExportSome); }		// just -exported_symbol
	bool						hasWildCardExportRestrictList() const;
	bool						hasReExportList() const { return ! fReExportSymbols.empty(); }
	bool						wasRemovedExport(const char* sym) const { return ( fRemovedExports.find(sym) != fRemovedExports.end() ); }
	bool						allGlobalsAreDeadStripRoots() const;
	bool						shouldExport(const char*) const;
	bool						shouldReExport(const char*) const;
	bool						ignoreOtherArchInputFiles() const { return fIgnoreOtherArchFiles; }
	bool						traceDylibs() const	{ return fTraceDylibs; }
	bool						traceArchives() const { return fTraceArchives; }
	bool						deadCodeStrip()	const	{ return fDeadStrip; }
	UndefinedTreatment			undefinedTreatment() const { return fUndefinedTreatment; }
	ld::MacVersionMin			macosxVersionMin() const { return fMacVersionMin; }
	ld::IPhoneVersionMin		iphoneOSVersionMin() const { return fIPhoneVersionMin; }
	bool						minOS(ld::MacVersionMin mac, ld::IPhoneVersionMin iPhoneOS);
	bool						messagesPrefixedWithArchitecture();
	Treatment					picTreatment();
	WeakReferenceMismatchTreatment	weakReferenceMismatchTreatment() const { return fWeakReferenceMismatchTreatment; }
	const char*					umbrellaName() const { return fUmbrellaName; }
	const std::vector<const char*>&	allowableClients() const { return fAllowableClients; }
	const char*					clientName() const { return fClientName; }
	const char*					initFunctionName() const { return fInitFunctionName; }			// only for kDynamicLibrary
	const char*					dotOutputFile();
	uint64_t					pageZeroSize() const { return fZeroPageSize; }
	bool						hasCustomStack() const { return (fStackSize != 0); }
	uint64_t					customStackSize() const { return fStackSize; }
	uint64_t					customStackAddr() const { return fStackAddr; }
	bool						hasExecutableStack() const { return fExecutableStack; }
	bool						hasNonExecutableHeap() const { return fNonExecutableHeap; }
	UndefinesIterator			initialUndefinesBegin() const { return &fInitialUndefines[0]; }
	UndefinesIterator			initialUndefinesEnd() const { return &fInitialUndefines[fInitialUndefines.size()]; }
	bool						printWhyLive(const char* name) const;
	uint32_t					minimumHeaderPad() const { return fMinimumHeaderPad; }
	bool						maxMminimumHeaderPad() const { return fMaxMinimumHeaderPad; }
	ExtraSection::const_iterator	extraSectionsBegin() const { return &fExtraSections[0]; }
	ExtraSection::const_iterator	extraSectionsEnd() const { return &fExtraSections[fExtraSections.size()]; }
	CommonsMode					commonsMode() const { return fCommonsMode; }
	bool						warnCommons() const { return fWarnCommons; }
	bool						keepRelocations();
	FileInfo					findFile(const char* path) const;
	UUIDMode					UUIDMode() const { return fUUIDMode; }
	bool						warnStabs();
	bool						pauseAtEnd() { return fPause; }
	bool						printStatistics() const { return fStatistics; }
	bool						printArchPrefix() const { return fMessagesPrefixedWithArchitecture; }
	void						gotoClassicLinker(int argc, const char* argv[]);
	bool						sharedRegionEligible() const { return fSharedRegionEligible; }
	bool						printOrderFileStatistics() const { return fPrintOrderFileStatistics; }
	const char*					dTraceScriptName() { return fDtraceScriptName; }
	bool						dTrace() { return (fDtraceScriptName != NULL); }
	unsigned long				orderedSymbolsCount() const { return fOrderedSymbols.size(); }
	OrderedSymbolsIterator		orderedSymbolsBegin() const { return &fOrderedSymbols[0]; }
	OrderedSymbolsIterator		orderedSymbolsEnd() const { return &fOrderedSymbols[fOrderedSymbols.size()]; }
	bool						splitSeg() const { return fSplitSegs; }
	uint64_t					baseWritableAddress() { return fBaseWritableAddress; }
	uint64_t					segmentAlignment() const { return fSegmentAlignment; }
	uint64_t					segPageSize(const char* segName) const;
	uint64_t					customSegmentAddress(const char* segName) const;
	bool						hasCustomSegmentAddress(const char* segName) const;
	bool						hasCustomSectionAlignment(const char* segName, const char* sectName) const;
	uint8_t						customSectionAlignment(const char* segName, const char* sectName) const;
	uint32_t					initialSegProtection(const char*) const; 
	uint32_t					maxSegProtection(const char*) const; 
	bool						saveTempFiles() const { return fSaveTempFiles; }
	const std::vector<const char*>&   rpaths() const { return fRPaths; }
	bool						readOnlyx86Stubs() { return fReadOnlyx86Stubs; }
	const std::vector<DylibOverride>&	dylibOverrides() const { return fDylibOverrides; }
	const char*					generatedMapPath() const { return fMapPath; }
	bool						positionIndependentExecutable() const { return fPositionIndependentExecutable; }
	Options::FileInfo			findFileUsingPaths(const char* path) const;
	bool						deadStripDylibs() const { return fDeadStripDylibs; }
	bool						allowedUndefined(const char* name) const { return ( fAllowedUndefined.find(name) != fAllowedUndefined.end() ); }
	bool						someAllowedUndefines() const { return (fAllowedUndefined.size() != 0); }
	LocalSymbolHandling			localSymbolHandling() { return fLocalSymbolHandling; }
	bool						keepLocalSymbol(const char* symbolName) const;
	bool						allowTextRelocs() const { return fAllowTextRelocs; }
	bool						warnAboutTextRelocs() const { return fWarnTextRelocs; }
	bool						usingLazyDylibLinking() const { return fUsingLazyDylibLinking; }
	bool						verbose() const { return fVerbose; }
	bool						makeEncryptable() const { return fEncryptable; }
	bool						needsUnwindInfoSection() const { return fAddCompactUnwindEncoding; }
	const std::vector<const char*>&	llvmOptions() const{ return fLLVMOptions; }
	const std::vector<const char*>&	dyldEnvironExtras() const{ return fDyldEnvironExtras; }
	bool						makeCompressedDyldInfo() const { return fMakeCompressedDyldInfo; }
	bool						hasExportedSymbolOrder();
	bool						exportedSymbolOrder(const char* sym, unsigned int* order) const;
	bool						orderData() { return fOrderData; }
	bool						errorOnOtherArchFiles() const { return fErrorOnOtherArchFiles; }
	bool						markAutoDeadStripDylib() const { return fMarkDeadStrippableDylib; }
	bool						removeEHLabels() const { return fNoEHLabels; }
	bool						useSimplifiedDylibReExports() const { return fUseSimplifiedDylibReExports; }
	bool						objCABIVersion2POverride() const { return fObjCABIVersion2Override; }
	bool						useUpwardDylibs() const { return fCanUseUpwardDylib; }
	bool						fullyLoadArchives() const { return fFullyLoadArchives; }
	bool						loadAllObjcObjectsFromArchives() const { return fLoadAllObjcObjectsFromArchives; }
	bool						autoOrderInitializers() const { return fAutoOrderInitializers; }
	bool						optimizeZeroFill() const { return fOptimizeZeroFill; }
	bool						logAllFiles() const { return fLogAllFiles; }
	DebugInfoStripping			debugInfoStripping() const { return fDebugInfoStripping; }
	bool						flatNamespace() const { return fFlatNamespace; }
	bool						linkingMainExecutable() const { return fLinkingMainExecutable; }
	bool						implicitlyLinkIndirectPublicDylibs() const { return fImplicitlyLinkPublicDylibs; }
	bool						whyLoad() const { return fWhyLoad; }
	const char*					traceOutputFile() const { return fTraceOutputFile; }
	bool						outputSlidable() const { return fOutputSlidable; }
	bool						haveCmdLineAliases() const { return (fAliases.size() != 0); }
	const std::vector<AliasPair>& cmdLineAliases() const { return fAliases; }
	bool						makeTentativeDefinitionsReal() const { return fMakeTentativeDefinitionsReal; }
	const char*					dyldInstallPath() const { return fDyldInstallPath; }
	bool						warnWeakExports() const { return fWarnWeakExports; }
	bool						objcGcCompaction() const { return fObjcGcCompaction; }
	bool						objcGc() const { return fObjCGc; }
	bool						objcGcOnly() const { return fObjCGcOnly; }
	bool						canUseThreadLocalVariables() const { return fTLVSupport; }
	bool						demangleSymbols() const { return fDemangle; }
	bool						addVersionLoadCommand() const { return fVersionLoadCommand; }
	bool						addFunctionStarts() const { return fFunctionStartsLoadCommand; }
	bool						canReExportSymbols() const { return fCanReExportSymbols; }
	const char*					tempLtoObjectPath() const { return fTempLtoObjectPath; }
	bool						objcCategoryMerging() const { return fObjcCategoryMerging; }
	bool						hasWeakBitTweaks() const;
	bool						forceWeak(const char* symbolName) const;
	bool						forceNotWeak(const char* symbolName) const;
	bool						forceWeakNonWildCard(const char* symbolName) const;
	bool						forceNotWeakNonWildcard(const char* symbolName) const;

private:
	class CStringEquals
	{
	public:
		bool operator()(const char* left, const char* right) const { return (strcmp(left, right) == 0); }
	};
	typedef __gnu_cxx::hash_map<const char*, unsigned int, __gnu_cxx::hash<const char*>, CStringEquals> NameToOrder;
	typedef __gnu_cxx::hash_set<const char*, __gnu_cxx::hash<const char*>, CStringEquals>  NameSet;
	enum ExportMode { kExportDefault, kExportSome, kDontExportSome };
	enum LibrarySearchMode { kSearchDylibAndArchiveInEachDir, kSearchAllDirsForDylibsThenAllDirsForArchives };
	enum InterposeMode { kInterposeNone, kInterposeAllExternal, kInterposeSome };

	class SetWithWildcards {
	public:
		void					insert(const char*);
		bool					contains(const char*) const;
		bool					containsNonWildcard(const char*) const;
		bool					empty() const			{ return fRegular.empty() && fWildCard.empty(); }
		bool					hasWildCards() const	{ return !fWildCard.empty(); }
		NameSet::iterator		regularBegin() const	{ return fRegular.begin(); }
		NameSet::iterator		regularEnd() const		{ return fRegular.end(); }
		void					remove(const NameSet&); 
	private:
		static bool				hasWildCards(const char*);
		bool					wildCardMatch(const char* pattern, const char* candidate) const;
		bool					inCharRange(const char*& range, unsigned char c) const;

		NameSet							fRegular;
		std::vector<const char*>		fWildCard;
	};


	void						parse(int argc, const char* argv[]);
	void						checkIllegalOptionCombinations();
	void						buildSearchPaths(int argc, const char* argv[]);
	void						parseArch(const char* architecture);
	FileInfo					findLibrary(const char* rootName, bool dylibsOnly=false);
	FileInfo					findFramework(const char* frameworkName);
	FileInfo					findFramework(const char* rootName, const char* suffix);
	bool						checkForFile(const char* format, const char* dir, const char* rootName,
											 FileInfo& result) const;
	uint32_t					parseVersionNumber(const char*);
	void						parseSectionOrderFile(const char* segment, const char* section, const char* path);
	void						parseOrderFile(const char* path, bool cstring);
	void						addSection(const char* segment, const char* section, const char* path);
	void						addSubLibrary(const char* name);
	void						loadFileList(const char* fileOfPaths);
	uint64_t					parseAddress(const char* addr);
	void						loadExportFile(const char* fileOfExports, const char* option, SetWithWildcards& set);
	void						parseAliasFile(const char* fileOfAliases);
	void						parsePreCommandLineEnvironmentSettings();
	void						parsePostCommandLineEnvironmentSettings();
	void						setUndefinedTreatment(const char* treatment);
	void						setMacOSXVersionMin(const char* version);
	void						setIPhoneVersionMin(const char* version);
	void						setWeakReferenceMismatchTreatment(const char* treatment);
	void						addDylibOverride(const char* paths);
	void						addSectionAlignment(const char* segment, const char* section, const char* alignment);
	CommonsMode					parseCommonsTreatment(const char* mode);
	Treatment					parseTreatment(const char* treatment);
	void						reconfigureDefaults();
	void						checkForClassic(int argc, const char* argv[]);
	void						parseSegAddrTable(const char* segAddrPath, const char* installPath);
	void						addLibrary(const FileInfo& info);
	void						warnObsolete(const char* arg);
	uint32_t					parseProtection(const char* prot);
	void						loadSymbolOrderFile(const char* fileOfExports, NameToOrder& orderMapping);



//	ObjectFile::ReaderOptions			fReaderOptions;
	const char*							fOutputFile;
	std::vector<Options::FileInfo>		fInputFiles;
	cpu_type_t							fArchitecture;
	cpu_subtype_t						fSubArchitecture;
	const char*							fArchitectureName;
	OutputKind							fOutputKind;
	bool								fHasPreferredSubType;
	bool								fPrebind;
	bool								fBindAtLoad;
	bool								fKeepPrivateExterns;
	bool								fNeedsModuleTable;
	bool								fIgnoreOtherArchFiles;
	bool								fErrorOnOtherArchFiles;
	bool								fForceSubtypeAll;
	InterposeMode						fInterposeMode;
	bool								fDeadStrip;
	NameSpace							fNameSpace;
	uint32_t							fDylibCompatVersion;
	uint32_t							fDylibCurrentVersion;
	const char*							fDylibInstallName;
	const char*							fFinalName;
	const char*							fEntryName;
	uint64_t							fBaseAddress;
	uint64_t							fMaxAddress;
	uint64_t							fBaseWritableAddress;
	bool								fSplitSegs;
	SetWithWildcards					fExportSymbols;
	SetWithWildcards					fDontExportSymbols;
	SetWithWildcards					fInterposeList;
	SetWithWildcards					fForceWeakSymbols;
	SetWithWildcards					fForceNotWeakSymbols;
	SetWithWildcards					fReExportSymbols;
	NameSet								fRemovedExports;
	NameToOrder							fExportSymbolsOrder;
	ExportMode							fExportMode;
	LibrarySearchMode					fLibrarySearchMode;
	UndefinedTreatment					fUndefinedTreatment;
	bool								fMessagesPrefixedWithArchitecture;
	WeakReferenceMismatchTreatment		fWeakReferenceMismatchTreatment;
	std::vector<const char*>			fSubUmbellas;
	std::vector<const char*>			fSubLibraries;
	std::vector<const char*>			fAllowableClients;
	std::vector<const char*>			fRPaths;
	const char*							fClientName;
	const char*							fUmbrellaName;
	const char*							fInitFunctionName;
	const char*							fDotOutputFile;
	const char*							fExecutablePath;
	const char*							fBundleLoader;
	const char*							fDtraceScriptName;
	const char*							fSegAddrTablePath;
	const char*							fMapPath;
	const char*							fDyldInstallPath;
	const char*							fTempLtoObjectPath;
	uint64_t							fZeroPageSize;
	uint64_t							fStackSize;
	uint64_t							fStackAddr;
	bool								fExecutableStack;
	bool								fNonExecutableHeap;
	bool								fDisableNonExecutableHeap;
	uint32_t							fMinimumHeaderPad;
	uint64_t							fSegmentAlignment;
	CommonsMode							fCommonsMode;
	enum UUIDMode						fUUIDMode;
	SetWithWildcards					fLocalSymbolsIncluded;
	SetWithWildcards					fLocalSymbolsExcluded;
	LocalSymbolHandling					fLocalSymbolHandling;
	bool								fWarnCommons;
	bool								fVerbose;
	bool								fKeepRelocations;
	bool								fWarnStabs;
	bool								fTraceDylibSearching;
	bool								fPause;
	bool								fStatistics;
	bool								fPrintOptions;
	bool								fSharedRegionEligible;
	bool								fPrintOrderFileStatistics;
	bool								fReadOnlyx86Stubs;
	bool								fPositionIndependentExecutable;
	bool								fPIEOnCommandLine;
	bool								fDisablePositionIndependentExecutable;
	bool								fMaxMinimumHeaderPad;
	bool								fDeadStripDylibs;
	bool								fAllowTextRelocs;
	bool								fWarnTextRelocs;
	bool								fUsingLazyDylibLinking;
	bool								fEncryptable;
	bool								fOrderData;
	bool								fMarkDeadStrippableDylib;
	bool								fMakeCompressedDyldInfo;
	bool								fMakeCompressedDyldInfoForceOff;
	bool								fNoEHLabels;
	bool								fAllowCpuSubtypeMismatches;
	bool								fUseSimplifiedDylibReExports;
	bool								fObjCABIVersion2Override;
	bool								fObjCABIVersion1Override;
	bool								fCanUseUpwardDylib;
	bool								fFullyLoadArchives;
	bool								fLoadAllObjcObjectsFromArchives;
	bool								fFlatNamespace;
	bool								fLinkingMainExecutable;
	bool								fForFinalLinkedImage;
	bool								fForStatic;
	bool								fForDyld;
	bool								fMakeTentativeDefinitionsReal;
	bool								fWhyLoad;
	bool								fRootSafe;
	bool								fSetuidSafe;
	bool								fImplicitlyLinkPublicDylibs;
	bool								fAddCompactUnwindEncoding;
	bool								fWarnCompactUnwind;
	bool								fRemoveDwarfUnwindIfCompactExists;
	bool								fAutoOrderInitializers;
	bool								fOptimizeZeroFill;
	bool								fLogObjectFiles;
	bool								fLogAllFiles;
	bool								fTraceDylibs;
	bool								fTraceIndirectDylibs;
	bool								fTraceArchives;
	bool								fOutputSlidable;
	bool								fWarnWeakExports;
	bool								fObjcGcCompaction;
	bool								fObjCGc;
	bool								fObjCGcOnly;
	bool								fDemangle;
	bool								fTLVSupport;
	bool								fVersionLoadCommand;
	bool								fFunctionStartsLoadCommand;
	bool								fCanReExportSymbols;
	bool								fObjcCategoryMerging;
	DebugInfoStripping					fDebugInfoStripping;
	const char*							fTraceOutputFile;
	ld::MacVersionMin					fMacVersionMin;
	ld::IPhoneVersionMin				fIPhoneVersionMin;
	std::vector<AliasPair>				fAliases;
	std::vector<const char*>			fInitialUndefines;
	NameSet								fAllowedUndefined;
	NameSet								fWhyLive;
	std::vector<ExtraSection>			fExtraSections;
	std::vector<SectionAlignment>		fSectionAlignments;
	std::vector<OrderedSymbol>			fOrderedSymbols;
	std::vector<SegmentStart>			fCustomSegmentAddresses;
	std::vector<SegmentSize>			fCustomSegmentSizes;
	std::vector<SegmentProtect>			fCustomSegmentProtections;
	std::vector<DylibOverride>			fDylibOverrides; 
	std::vector<const char*>			fLLVMOptions;
	std::vector<const char*>			fLibrarySearchPaths;
	std::vector<const char*>			fFrameworkSearchPaths;
	std::vector<const char*>			fSDKPaths;
	std::vector<const char*>			fDyldEnvironExtras;
	bool								fSaveTempFiles;
};



#endif // __OPTIONS__
