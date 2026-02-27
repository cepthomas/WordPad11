// docopt.h : header file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDocOptPage dialog

class CDocOptPage : public CPropertyPage
{
// Construction
public:
	CDocOptPage();
	CDocOptPage(UINT nIDCaption);
	~CDocOptPage();

// Dialog Data
	//{{AFX_DATA(CDocOptPage)
	enum { IDD = IDD_OPTIONS_WRAP };
	int     m_nWordWrap = 0;
	BOOL    m_bFormatBar = FALSE;
	BOOL    m_bRulerBar = FALSE;
	BOOL    m_bStatusBar = FALSE;
	BOOL    m_bToolBar = FALSE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDocOptPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDocOptPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

class CEmbeddedOptPage : public CDocOptPage
{
// Construction
public:
	CEmbeddedOptPage();

	// Overrides
	BOOL OnInitDialog();
};
