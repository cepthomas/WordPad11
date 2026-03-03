# WordPad11

Good old WordPad brought into the 21st century. MS quietly removed the executable from Win11 24H2 but  
handed over the keys as MIT licensed open source. There are several re-interpretations of this tool - search
github for them if interested.

Main aspects and changes from the original:
- Windows 11 and later.
- Build (and debug) with Visual Studio.
- x64 static portable executable in install directory.
- No registry access, persistence to ini file.
- Remove all vestiges of outdated MFC help. This *may* be useful: http://hs.windows.microsoft.com/hhweb/content/m-en-us/p-6.2/id-7479c387-8dc4-40b6-9506-cc7a58c61f0a/.


# Tech Notes

- Build it yourself using VS 2022+ with the C++ (+ MFC) workload.
- The project baseline is a copy (not fork) of [WordPad OG](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/wordpad).
- If you want all the original registry stuff back, uncomment `_REGISTER_APP` in `framework.h`.
- Historical cruft addressed:
    - Splash gone, replaced with `about` - includes license.
    - Removed support for Word6 and Write files.
    - Reorganize convoluted includes.
    - Remove string and resource clutter.
    - Simplify doc type management.
    - General code cleanup. Too many cooks in this broth. Still a lot of entangled objects.
