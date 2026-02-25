// about.h : header file
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
// CAbout dialog

class CAboutDialog : public CDialog
{
private:
	//BOOL Create(CWnd* pParent);

// Construction
public:
	CAboutDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CAboutDialog)
	enum { IDD = IDD_ABOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAboutDialog)
	virtual BOOL OnInitDialog();
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
};
