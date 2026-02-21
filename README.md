# WordPad11 TODO clean up

Good old WordPad brought into the 21st century. The executaable was quietly removed from Win11 24H2 but MS 
handed over the keys as MIT licensed open-source. There are several re-interpretations of this tool - search
github for them if interested.

Main aspects:
- Windows 11 and later - build it in VS 2022+ with the C++ (with MFC) workload.
- 64 bit static/portable executable, no default registry writing.
- Historical cruft removed.

The repo baseline is a copy (not fork) of [WordPad OG](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/wordpad).

TODO - output location - for portable/release
    <Target Name="PostBuild" AfterTargets="PostBuildEvent" Condition="'$(TOOLS_PATH)' != ''">
        <Exec Command="copy /Y $(OutputPath)Shellinator.exe $(TOOLS_PATH)" />
    </Target>

# my changes
- mfc static - portable
- remove 32bit -> x64 only
- remove reg editing - optional
- removed all old version-specific stuff < VS2022  - all WP_XXX macros


# to add

- remove wri support. word6? other txt? TODOx
    case RD_WINWORD6:
    case RD_WORDPAD:
    case RD_RICHTEXT:
    case RD_TEXT:
    case RD_OEMTEXT:
    case RD_WRITE:
    case RD_EMBEDDED:

    IDR_MAINFRAME           "WordPad\nDocument\nWordPad Document\nWord for Windows 6.0 (*.doc)\n.DOC\nWordPad.Document.1\nWordPad Document"
    IDS_TEXT_DOC            "Text Document\nText Documents (*.txt)\n*.txt\nText Document"
    IDS_RICHTEXT_DOC        "Rich Text Format (RTF)\nRich Text Format (*.rtf)\n*.rtf\nRich Text Document"
//    IDS_WRITE_DOC           "Windows Write\nWindows Write (*.wri)\n*.wri\nWrite Document"
    IDS_ALL_DOC             "All\nAll Documents (*.*)\n*.*"
    IDS_WINWORD6_DOC        "Word for Windows 6.0\nWord for Windows 6.0 (*.doc)\n*.doc\nWord Document"
    IDS_WINWORD2_DOC        "Word for Windows 2.0\nWord for Windows 2.0 (*.doc)\n*.doc"
    IDS_EXE_DOC             "Executable\nExecutable (*.exe)\n*.exe"
    IDS_FILE_EXISTS         "%1 already exists.\nDo you want to replace it?"
    IDS_OEMTEXT_DOC         "Text Document - MS-DOS Format\nText Documents - MS-DOS Format (*.txt)\n*.txt\nMS-DOS Text Document"
    IDS_CLIP_TEXT           "Unformatted Text\ntext without any formatting"

    IDS_WORD6_OPTIONS       "Word 6"
    IDS_WORD6_DOCUMENT      "Word 6 Document"

#define IDS_WORD6_WARNING               126
#define IDS_WORD6_WARNING_BUTTONS       127
#define IDS_WRITE_DOC                   131
#define IDS_WINWORD6_DOC                133
#define IDS_WINWORD2_DOC                134
#define IDS_OEMTEXT_DOC                 137
#define IDS_WORD6_OPTIONS               185
#define IDS_WRITE_OPTIONS               187
#define IDS_WORD6_DOCUMENT              191





- help/about
search "https://github.com/malxau/wordpad"  IDD_ABOUT
??? Add MIT license to compiled binaries, which is required by the license
TODO bunch of these:
  ON_MESSAGE(WM_HELP, OnHelp)
  ON_MESSAGE(WM_CONTEXTMENU, OnHelpContextMenu)
  ON_COMMAND(ID_DEFAULT_HELP, OnHelpFinder)
  irtual const DWORD* GetHelpIDs() = 0;
  CMainFrame::OnHelpFinder()
  IDD_ABOUT DIALOGEX


IDD_SPLASH DIALOGEX 0, 0, 253, 92
STYLE DS_SETFONT | DS_MODALFRAME | WS_POPUP
FONT 8, "MS Sans Serif", 0, 0, 0x0
BEGIN
    CONTROL         "",IDC_BIGICON,"Button",BS_OWNERDRAW | WS_DISABLED,6,6,38,40
    LTEXT           "WordPad Version 1.0",IDC_STATIC,60,6,164,8,NOT WS_GROUP
    CONTROL         "",IDC_STATIC,"Static",SS_BLACKRECT,60,30,188,1
    LTEXT           "Warning: This computer program is protected by", IDC_STATIC,60,36,188,8
    LTEXT           "copyright law and international treaties.",IDC_STATIC, 60,44,188,8
    LTEXT           "© 1998 - 2008 Microsoft Corporation.  All rights reserved.",IDC_STATIC,60,60,188,8
    LTEXT           "Licensed under the terms of the MIT license.",IDC_STATIC,60,68,188,8
END


IDD_ABOUT DIALOGEX 0, 0, 422, 250
STYLE DS_SETFONT | DS_MODALFRAME | WS_CAPTION | WS_SYSMENU
CAPTION "About WordPad"
FONT 8, "MS Sans Serif", 0, 0, 0x0
BEGIN
    CONTROL         "",IDC_BIGICON,"Button",BS_OWNERDRAW | WS_DISABLED,6,6,38,40
    LTEXT           "WordPad Version 1.0",-1,60,6,164,8,NOT WS_GROUP
    LTEXT           "https://github.com/malxau/wordpad",-1,60,18,188,8
    EDITTEXT        IDC_LICENSE_TEXT,60,33,350,206,ES_MULTILINE | ES_AUTOHSCROLL | ES_NOHIDESEL | ES_READONLY | WS_VSCROLL | NOT WS_TABSTOP
    DEFPUSHBUTTON   "&Close",IDOK,332,7,78,18
END


# TO-DO later

- add amd64?
- cosmetics

