[Darwin](http://en.wikipedia.org/wiki/Darwin_(operating_system\)) is a free and 
open source UNIX operating system created by Apple Inc. to be used as the
base of OS X.

The aim of this project is the provide clean sources that can be used to build
a standalone distribution of Darwin without any Apple proprietary software.

## Installation

I use the same method as [Linux From Scratch](http://www.linuxfromscratch.org/lfs/read.html)
to build the Darwin system from sources. Of course, many modifications have to
be made, but the general idea stays the same :

* Compilation of a toolchain that outputs binaries independant from the host system
* Using this toolchain, compilation of a temporary system, and chroot in it
* Building the final system

The sources are taken from [Apple open source page](http://opensource.apple.com)
and patched so they can be build using this method. The main problem is that
most packages use dirty hard coded Makefiles or Apple's xcodebuild proprietary 
tool for the build system, so I wrote new build scripts using GNU Autotools.

Currently, only two components of Darwin have been repackaged and are thus 
able to be build like this, but more will be added soon. Detailed instructions 
about how to build, including parameters to pass to the build tools, will be
written as soon as I managed to do it myself.

## Packages

* cctools : This package contains various tools to deal with Mach-O files, which
is the default binary file format used by the XNU kernel. It is an equivalent
to the GNU binutils package on the GNU OS.
* ld64 : This package contains the dynamic linker ld, as well as other tools
and libraries related to it. It replaces the old ld-classic from the cctools 
package that was not 64 bit-capable. 
