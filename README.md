# WordPad11

Good old WordPad brought into the 21st century. MS quietly removed the executable from Win11 24H2 but  
handed over the keys as MIT licensed open source. There are several re-interpretations of this tool - search
github for them if interested.

Main aspects and changes from the original:
- Windows 11 and later
- x64 static portable executable in install directory
- No registry access, persistence to ini file


# Tech Notes

- Build it yourself using VS 2022+ with the C++ (+ MFC) workload.
- The project baseline is a copy (not fork) of [WordPad OG](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/wordpad).
- If you want all the original registry stuff back, uncomment `_REGISTER_APP` in `framework.h`.
- Historical cruft removed:
- Splash gone, replaced with about.
- Cleaned up convoluted includes.
- Removed string clutter.
- General code cleanup. Too many cooks in this broth.
