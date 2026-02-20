# WordPad11 TODO clean up

Good old WordPad brought into the 21st century.

The WordPad source code has been included as a sample in compilers since 1995 under restrictive terms.
These samples are now available under the MIT license, including the version bundled with Visual C++ 2008 and 2010.

This source is based on a copy (not fork) of [WordPad OG](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/wordpad).


> wordpad_orig is from https://github.com/malxau/wordpad
This repo is an attempt to maintain the WordPad source code and keep it useful and relevant.
The WordPad source code has been included as a sample in compilers since 1995 under restrictive terms.  These samples are now available under the MIT license, including the version bundled with Visual C++ 2008 and 2010.  This source is a fork of the [most recent code from the 2010 compiler](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/wordpad).

> This is a modern version for Win11 24H2 and beyond (since it was removed). Build it in VS 2022+ with the C++ (with MFC) workload.

# changes like malxau





# my changes
- mfc static
- remove 32bit x64 only, add amd?





# to add

- remove reg editing
??? Add MIT license to compiled binaries, which is required by the license
- remove wri support.


git archive
https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/wordpad
VC2010Samples/MFC/ole/wordpad


git archive -o ../wp.zip HEAD:subdir


This code is available under the same license as the sample code, MIT + All rights reserved.


> new
license/about
    <OutDir>bin\$(Platform)\$(Configuration)\</OutDir>

#if _MFC_VER >= 0x700 etc
search "https://github.com/malxau/wordpad"  IDD_ABOUT


