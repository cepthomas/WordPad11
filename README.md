# WordPad11 TODO clean up

Good old WordPad brought into the 21st century. The executaable was quietly removed from Win11 24H2 but MS 
handed over the keys as MIT licensed open-source. There are several re-interpretations of this tool - search
github for them if interested.

Main aspects:
- Windows 11 and later - build it in VS 2022+ with the C++ (with MFC) workload.
- 64 bit static/portable executable, no default registry writing.
- Historical cruft removed.

The project baseline is a copy (not fork) of [WordPad OG](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/wordpad).


# Future?

- Support AMD64?
- Cosmetics?

# from original html help file - any useful?

WORDPAD Sample: The Windows Application

WORDPAD is the word processing application included with Windows. It is an example of a full-fledged word processing application written using MFC.

WORDPAD comes with a help file describing its user interface.
Security Note

This sample code is provided to illustrate a concept and should not be used in applications or Web sites, as it may not illustrate the safest coding practices.
Building and Running the Sample
To build and run the WORDPAD sample

    Open the solution wordpad.sln.

    On the Build menu, click Build.

    Run WordPad as a stand-alone application so it can register itself with the system.

WORDPAD Features

The SUPERPAD sample illustrates a basic word processor based on the CEditView class. In contrast, WORDPAD is based on the CRichEditView, CRichEditDoc, and CRichEditCntrItem classes, and — besides supporting the features that SUPERPAD supports — also demonstrates the following features.

    The ability to read, write, and convert between multiple file formats, including the Word file format, .rtf (Rich Text Format) format, and ASCII text format.

    Text formatting, including the use of fonts, character formatting (bold, italics, underlining), color, and point sizes. These attributes are available in a formatting toolbar.

    Per-paragraph formatting, including alignment (left, center, or right), tabs, margins, and first-line indentation. These attributes are also available in a ruler toolbar.

    Undo support.

    ActiveX component support, both container and server.