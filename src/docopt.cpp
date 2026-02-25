// docopt.cpp : implementation file
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
#include "docopt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocOptPage property page

CDocOptPage::CDocOptPage() : CPropertyPage(CDocOptPage::IDD)
{
	//{{AFX_DATA_INIT(CDocOptPage)
	m_nWordWrap = -1;
	m_bFormatBar = FALSE;
	m_bRulerBar = FALSE;
	m_bStatusBar = FALSE;
	m_bToolBar = FALSE;
	//}}AFX_DATA_INIT
}

CDocOptPage::CDocOptPage(UINT nIDCaption) :
	CPropertyPage(CDocOptPage::IDD, nIDCaption)
{
	m_nWordWrap = -1;
	m_bFormatBar = FALSE;
	m_bRulerBar = FALSE;
	m_bStatusBar = FALSE;
	m_bToolBar = FALSE;
}

CDocOptPage::~CDocOptPage()
{
}

void CDocOptPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDocOptPage)
	DDX_Radio(pDX, IDC_WRAP_NONE, m_nWordWrap);
	DDX_Check(pDX, IDC_CHECK_FORMATBAR, m_bFormatBar);
	DDX_Check(pDX, IDC_CHECK_RULERBAR, m_bRulerBar);
	DDX_Check(pDX, IDC_CHECK_STATUSBAR, m_bStatusBar);
	DDX_Check(pDX, IDC_CHECK_TOOLBAR, m_bToolBar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDocOptPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDocOptPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDocOptPage message handlers

/////////////////////////////////////////////////////////////////////////////
// CEmbeddedOptPage property page

CEmbeddedOptPage::CEmbeddedOptPage() : CDocOptPage(IDS_EMBEDDED_OPTIONS)
{
}

BOOL CEmbeddedOptPage::OnInitDialog()
{
	BOOL b = CDocOptPage::OnInitDialog();
	GetDlgItem(IDC_CHECK_STATUSBAR)->ShowWindow(SW_HIDE);
	return b;
}
