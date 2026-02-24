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
#include "framework.h"

#include "wordpad.h"
#include "about.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog dialog

CAboutDialog::CAboutDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDialog)
	//}}AFX_DATA_INIT
}

BOOL CAboutDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();

	//TODOhelp
	CEdit* pEditBox = (CEdit*)GetDlgItem(IDC_ABOUT_TEXT);



	CString text = CString("TODOhelp \"Warning: This computer program is protected by\" \
		           \"copyright law and international treaties.\" \
		           \"© 1998 - 2008 Microsoft Corporation.  All rights reserved. TODOhelp\" \
		           \"Licensed under the terms of the MIT license.\" ");
	
	pEditBox->SetWindowText(text);



//IDD_SPLASH DIALOGEX 0, 0, 253, 92  //TODOhelp
//STYLE DS_SETFONT | DS_MODALFRAME | WS_POPUP
//FONT 8, "MS Sans Serif", 0, 0, 0x0
//BEGIN
//CONTROL         "", IDC_BIGICON, "Button", BS_OWNERDRAW | WS_DISABLED, 6, 6, 38, 40
//LTEXT           "WordPad Version 1.0", IDC_STATIC, 60, 6, 164, 8, NOT WS_GROUP
//CONTROL         "", IDC_STATIC, "Static", SS_BLACKRECT, 60, 30, 188, 1
//LTEXT           "Warning: This computer program is protected by", IDC_STATIC, 60, 36, 188, 8
//LTEXT           "copyright law and international treaties.", IDC_STATIC, 60, 44, 188, 8
//LTEXT           "© 1998 - 2008 Microsoft Corporation.  All rights reserved. TODOhelp", IDC_STATIC, 60, 60, 188, 8
//LTEXT           "Licensed under the terms of the MIT license.", IDC_STATIC, 60, 68, 188, 8
//END
//

	//// initialize the big icon control
	//m_icon.SubclassDlgItem(IDC_BIGICON, this);
	//m_icon.SizeToContent();

	//HINSTANCE hInst = AfxGetInstanceHandle();

	//HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(IDR_LICENSE_TEXT), RT_RCDATA);
	//if (hRsrc == NULL)
	//	return FALSE;

	//HGLOBAL hLoadedRsrc = ::LoadResource(hInst, hRsrc);
	//if (hLoadedRsrc == NULL)
	//	return FALSE;

	//DWORD ResourceSize = ::SizeofResource(hInst, hRsrc);

	//LPCSTR LicenseTextPtr = (LPCSTR)::LockResource(hLoadedRsrc);

	//if (LicenseTextPtr == NULL)
	//	return FALSE;

	//CString LicenseText(LicenseTextPtr, ResourceSize);

	//CEdit* pEditBox = (CEdit*)GetDlgItem(IDC_LICENSE_TEXT);
	//pEditBox->SetWindowText(LicenseText);

	return FALSE;  // return TRUE unless you set the focus to a control
}

