#pragma once

// TODO clean this up later. Includes stuff from original stdafx.h.
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

// Define these before any includes.
//#define _CRT_NON_CONFORMING_SWPRINTFS 1
#define _CRT_SECURE_NO_WARNINGS 1

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
//#include <afxdisp.h>        // MFC Automation classes

//#ifndef _AFX_NO_OLE_SUPPORT
//#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
//#endif
//#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>             // MFC support for Windows Common Controls
//#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars

// Turns on writing the registry - the original way.
//#define _REGISTER_APP

///////////////////////////////// original stdafx.h ////////////////////////////////////////
///////////////////////////////// original stdafx.h ////////////////////////////////////////


// #ifndef _UNICODE
// #define VC_EXTRALEAN        // use stripped down Win32 headers
// #endif


// #define _UNICODE 1
// #define UNICODE 1

//#ifdef _MSC_VER // -> 1944
//#if _MSC_VER >= 1700
//#define WINVER 0x601
//#elif _MSC_VER >= 1600
//#define WINVER 0x501
//#elif _MSC_VER >= 1500
//#define WINVER 0x500
//#else
//#define WINVER 0x400
//#endif
//#endif

// #if _MSC_VER >= 1600
#pragma warning(disable: 4996) // Function declared deprecated
// #endif
// #endif

#define CONVERTERS

// #include <afxwin.h>         // MFC core and standard components
// #include <afxext.h>         // MFC extensions
//#include <afxole.h>         // MFC OLE classes
//#include <afxodlgs.h>       // MFC OLE dialog classes
// #include <afxcmn.h>
#include <afxrich.h>
//#include <afxpriv.h>

#define HORZ_TEXTOFFSET 15
#define VERT_TEXTOFFSET 5

// #if !defined(_WIN64) && defined(_MSC_VER) && _MSC_VER < 1300
// typedef INT WP_INT_PTR;
// typedef LONG LONG_PTR;
// typedef DWORD DWORD_PTR;
// #else
typedef INT_PTR WP_INT_PTR;
// #endif

// #if _MFC_VER >= 0x700
typedef CHARFORMAT2 WP_CHARFORMAT;
typedef PARAFORMAT2 WP_PARAFORMAT;
typedef ULONGLONG WP_FILE_SIZE;
// #else
// typedef CHARFORMAT WP_CHARFORMAT;
// typedef PARAFORMAT WP_PARAFORMAT;
// typedef DWORD WP_FILE_SIZE;
// #endif

//#ifndef ENSURE
//#define ENSURE(x) if (!(x)) ::AfxThrowMemoryException()
//#endif

class CDisplayIC : public CDC
{
public:
    CDisplayIC() { CreateIC(_T("DISPLAY"), NULL, NULL, NULL); }
};

struct CCharFormat : public WP_CHARFORMAT
{
    CCharFormat() {cbSize = sizeof(WP_CHARFORMAT);}
    BOOL operator==(CCharFormat& cf);
};

struct CParaFormat : public WP_PARAFORMAT
{
    CParaFormat() {cbSize = sizeof(_paraformat);}
    BOOL operator==(WP_PARAFORMAT& pf);
};

#include "doctype.h"
#include "chicdial.h"

///////////////////////////////// end original stdafx.h ////////////////////////////////////////
///////////////////////////////// end original stdafx.h ////////////////////////////////////////



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

