# WordPad11 TODO clean up

Good old WordPad brought into the 21st century. The executaable was quietly removed from Win11 24H2 but MS 
handed over the keys as MIT licensed open-source. There are several re-interpretations of this tool - search
github for them if interested.

Main aspects:
- Windows 11 and later - build it in VS 2022+ with the C++ (with MFC) workload.
- 64 bit static/portable executable, no default registry writing.

The project baseline is a copy (not fork) of [WordPad OG](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/wordpad).

Main documentation is in doc directory.


# Tech Notes

- Historical cruft removed:
- Splash gone, replaced with about.
- Cleaned up convoluted includes.
- Removed string clutter.
- General code cleanup.  interns in code...


# Future?

- Support AMD64?
- Cosmetics?

