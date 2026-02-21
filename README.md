# WordPad11 TODO clean up

Good old WordPad brought into the 21st century. The executaable was quietly removed from Win11 24H2 but MS 
handed over the keys as MIT licensed open-source. There are several re-interpretations of this tool - search
github for them if interested.

Main aspects:
- Windows 11 and later - Build it in VS 2022+ with the C++ (with MFC) workload.
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



- add? help/about
search "https://github.com/malxau/wordpad"  IDD_ABOUT
??? Add MIT license to compiled binaries, which is required by the license
TODO bunch of these:
  ON_MESSAGE(WM_HELP, OnHelp)
  ON_MESSAGE(WM_CONTEXTMENU, OnHelpContextMenu)
  ON_COMMAND(ID_DEFAULT_HELP, OnHelpFinder)
  irtual const DWORD* GetHelpIDs() = 0;
  CMainFrame::OnHelpFinder()
  IDD_ABOUT DIALOGEX




# TO-DO later

- add amd64?
