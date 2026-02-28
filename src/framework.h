#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN // Exclude rarely-used stuff from Windows headers
#endif

// Define these before any includes.
#define _CRT_SECURE_NO_WARNINGS 1

// Some CString constructors will be explicit.
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

// Turns off MFC's hiding of some common and often safely ignored warning messages.
#define _AFX_ALL_WARNINGS

#include "targetver.h"
// MFC core and standard components
#include <afxwin.h>         
// MFC extensions
#include <afxext.h>         
// MFC Automation classes
//#include <afxdisp.h>        

//#ifndef _AFX_NO_OLE_SUPPORT
// MFC support for Internet Explorer 4 Common Controls
//#include <afxdtctl.h>           
//#endif
//#ifndef _AFX_NO_AFXCMN_SUPPORT
// MFC support for Windows Common Controls
//#include <afxcmn.h>             
//#endif

// MFC support for ribbons and control bars
#include <afxcontrolbars.h>     

#include <afxrich.h>
//#include <afxpriv.h>


// Enable version 6.0 of the Windows Common Controls for a modern look and feel: 
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

// Custom for this application.
// If defined, turns on writing OS associations etc and state persistence to the registry - the original way.
// If not, no OS associations and persistence is to an INI file in the executable dir - portable version.
//#define _REGISTER_APP

// If using multconv file converters. Currently only obsolete file types: Word 2/6, Write.
//#define _CONVERTERS



// Check version mins for building - Basically standard VS2022.
#if _MSC_VER < 1900 // major:19 minor:0
#error "MSC version invalid."
#endif

#if WINVER < 0X0A00 // aka _WIN32_WINNT
#error "WINVER invalid."
#endif

#if _MFC_VER < 0X0E00 // 14.00
#error "_MFC_VER invalid."
#endif

#if _RICHEDIT_VER < 0X0210
#error "_RICHEDIT_VER invalid."
#endif
