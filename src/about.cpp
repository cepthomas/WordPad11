// about.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "pch.h"
#include "about.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDialog dialog

CAboutDialog::CAboutDialog(CWnd* pParent)
	: CDialog(CAboutDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDialog)
	//}}AFX_DATA_INIT
}

BOOL CAboutDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();

	//TODOhelp Improve cosmetics of this.
    CEdit* pEditBox = (CEdit*)GetDlgItem(IDC_ABOUT_TEXT);
//    CRichEditView* pRichEditBox = (CRichEditView*)GetDlgItem(IDC_RICHEDIT21);


	// from splash
	CString text = CString("TODOhelp\nWarning: This computer program is protected by\r\n\
copyright law and international treaties.\r\n\
© 1998 - 2008 Microsoft Corporation.  All rights reserved.\r\n\
Licensed under the terms of the MIT license.");
	
	pEditBox->SetWindowText(text);
//    pRichEditBox->SetWindowTextW(text);

    /////////////////////////////////////////////////////////////////////

    // Get the file path of the current module
    TCHAR szFileName[MAX_PATH];
    GetModuleFileName(NULL, szFileName, MAX_PATH);

    DWORD dwHandle, dwSize;
    dwSize = GetFileVersionInfoSize(szFileName, &dwHandle);

    if (dwSize == 0)
    {
        text = "Unknown Version 1";
    }

    // Allocate buffer for version information
    //std::unique_ptr<BYTE[]> pVersionInfo(new BYTE[dwSize]);
    BYTE* pVersionInfo = (BYTE*)calloc(dwSize, sizeof(BYTE));


    if (!GetFileVersionInfo(szFileName, dwHandle, dwSize, pVersionInfo))
    {
        text = "Unknown Version 2";
    }

    VS_FIXEDFILEINFO* pFixedInfo;
    UINT uLen;
    // Query the fixed-info structure
    if (VerQueryValue(pVersionInfo, L"\\", (LPVOID*)&pFixedInfo, &uLen))
    {
        DWORD dwFileVersionMS = pFixedInfo->dwFileVersionMS;
        DWORD dwFileVersionLS = pFixedInfo->dwFileVersionLS;

        DWORD dwMajor = HIWORD(dwFileVersionMS);
        DWORD dwMinor = LOWORD(dwFileVersionMS);
        DWORD dwBuild = HIWORD(dwFileVersionLS);
        DWORD dwRevision = LOWORD(dwFileVersionLS);

        // Format the version string
        //std::wstring version = std::to_wstring(dwMajor) + L"." +
        //    std::to_wstring(dwMinor) + L"." +
        //    std::to_wstring(dwBuild) + L"." +
        //    std::to_wstring(dwRevision);
        //return version;

        text = "pFixedInfo->TODOhelp";
    }

    // Fallback to string-based version if fixed-info fails.
    //https://learn.microsoft.com/en-us/windows/win32/api/winver/nf-winver-verqueryvaluea#varfileinfotranslation
    LPWSTR pStringInfo;
    UINT uSLen;
    //if (VerQueryValue(pVersionInfo, L"\\StringFileInfo\\040904B0\\FileVersion", (LPVOID*)&pStringInfo, &uLen))
    if (VerQueryValue(pVersionInfo, L"\\VarFileInfo\\Translation", (LPVOID*)&pStringInfo, &uSLen))
    {
        //return std::wstring(pStringInfo);
        text = (char*)pStringInfo;
    }

    pEditBox->SetWindowText(text);


    /////////////////////////////////////////////////////////////////////

	return FALSE;  // ???? return TRUE unless you set the focus to a control
    return TRUE;  // return TRUE  unless you set the focus to a control

}


//#include <windows.h>
//#include <tchar.h>
//#include <string>

char* GetAppVersion() // TODOhelp
{
    // Get the file path of the current module
    TCHAR szFileName[MAX_PATH];
    GetModuleFileName(NULL, szFileName, MAX_PATH);

    DWORD dwHandle, dwSize;
    dwSize = GetFileVersionInfoSize(szFileName, &dwHandle);

    if (dwSize == 0)
    {
        return "Unknown Version";
    }

    // Allocate buffer for version information
    //std::unique_ptr<BYTE[]> pVersionInfo(new BYTE[dwSize]);
    BYTE* pVersionInfo = (BYTE * )calloc(dwSize, sizeof(BYTE));


    if (!GetFileVersionInfo(szFileName, dwHandle, dwSize, pVersionInfo))
    {
        return "Unknown Version";
    }

    VS_FIXEDFILEINFO* pFixedInfo;
    UINT uLen;
    // Query the fixed-info structure
    if (VerQueryValue(pVersionInfo, L"\\", (LPVOID*)&pFixedInfo, &uLen))
    {
        DWORD dwFileVersionMS = pFixedInfo->dwFileVersionMS;
        DWORD dwFileVersionLS = pFixedInfo->dwFileVersionLS;

        DWORD dwMajor = HIWORD(dwFileVersionMS);
        DWORD dwMinor = LOWORD(dwFileVersionMS);
        DWORD dwBuild = HIWORD(dwFileVersionLS);
        DWORD dwRevision = LOWORD(dwFileVersionLS);

        // Format the version string
        //std::wstring version = std::to_wstring(dwMajor) + L"." +
        //    std::to_wstring(dwMinor) + L"." +
        //    std::to_wstring(dwBuild) + L"." +
        //    std::to_wstring(dwRevision);
        //return version;

        return "pFixedInfo->TODOhelp";
    }

    // Fallback to string-based version if fixed-info fails
    LPWSTR pStringInfo;
    if (VerQueryValue(pVersionInfo, L"\\StringFileInfo\\040904B0\\FileVersion", (LPVOID*)&pStringInfo, &uLen))
    {
        //return std::wstring(pStringInfo);
        return (char*)pStringInfo;
    }

    return "Unknown Version";
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog message handlers

