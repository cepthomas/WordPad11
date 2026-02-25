// formatpa.h : header file
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
// CFormatParaDlg dialog

class CFormatParaDlg : public CDialog
{
// Construction
public:
	CFormatParaDlg(PARAFORMAT2& pf, CWnd* pParent = NULL);   // standard constructor
	PARAFORMAT2 m_pf;

// Attributes
	int m_nWordWrap;

// Dialog Data
	//{{AFX_DATA(CFormatParaDlg)
	enum { IDD = IDD_FORMAT_PARA };
	int     m_nAlignment;
	int     m_nFirst;
	int     m_nLeft;
	int     m_nRight;
	BOOL	m_bPageBreak;
	int		m_nAfter;
	int		m_nBefore;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();

	// Generated message map functions
	//{{AFX_MSG(CFormatParaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinBefore(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAfter(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
