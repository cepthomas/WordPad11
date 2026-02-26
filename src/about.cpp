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

    // TODO Make this prettier.

    // Collect info to display.
    CString sError;
    UINT len;
    CString str;
    CString sDescription;
    CString sVersion;
    CString sLicense = L"License TODOhelp";
    BYTE* info = nullptr;

    // Get the file path of the current module
    TCHAR szFileName[MAX_PATH];
    if (GetModuleFileName(NULL, szFileName, MAX_PATH) == 0)
    {
        sError = "Invalid filename";
    }

    if (sError.IsEmpty())
    {
        DWORD hnd;
        DWORD size = GetFileVersionInfoSize(szFileName, &hnd);
        if (size == 0)
        {
            sError = "Invalid file version";
        }
        else
        {
            // Allocate buffer for version information
            info = (BYTE*)calloc(size, sizeof(BYTE));
            if (!GetFileVersionInfo(szFileName, hnd, size, info))
            {
                sError = "Invalid file version info";
            }
        }
    }

    if (sError.IsEmpty())
    {
        // Read the list of languages and code pages.
        struct LANGANDCODEPAGE
        {
            WORD wLanguage;
            WORD wCodePage;
        }* lpTranslate;

        VerQueryValue(info, L"\\VarFileInfo\\Translation", (LPVOID*)&lpTranslate, &len);
        int numPages = len / sizeof(struct LANGANDCODEPAGE);

        if (numPages == 0)
        {
            sError = "No code pages";
        }
        else
        {
            // Read the parts of interest.
            LPWSTR buff;

            str.Format(L"\\StringFileInfo\\%04x%04x\\FileDescription", lpTranslate[0].wLanguage, lpTranslate[0].wCodePage);
            if (VerQueryValue(info, str.GetString(), (LPVOID*)&buff, &len))
            {
                sDescription = buff;
            }
            else
            {
                sError = "Invalid FileDescription";
            }

            str.Format(L"\\StringFileInfo\\%04x%04x\\ProductVersion", lpTranslate[0].wLanguage, lpTranslate[0].wCodePage);
            if (VerQueryValue(info, str.GetString(), (LPVOID*)&buff, &len))
            {
                sVersion = buff;
            }
            else
            {
                sError = "Invalid ProductVersion";
            }
       }
    }

    //VS_FIXEDFILEINFO* fixed;
    //if (VerQueryValue(info, L"\\", (LPVOID*)&fixed, &len))

    // Output what we got.
    CEdit* pEditBox = (CEdit*)GetDlgItem(IDC_ABOUT_TEXT);
    if (sError.IsEmpty())
    {
        pEditBox->SetWindowText(sDescription + "\r\n\r\nVersion " + sVersion + "\r\n\r\n" + sLicense);
    }
    else
    {
        pEditBox->SetWindowText(sError + "\r\n\r\n" + sLicense);
    }

    return TRUE;  // return TRUE  unless you set the focus to a control
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDialog message handlers

