// wordpad.h : main header file for the WORDPAD application
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

#include "pch.h"
#include "options.h"

#define WPM_BARSTATE WM_USER
const TCHAR WORDPAD_CLASS[] = _T("WordPadClass");


/////////////////////////////////////////////////////////////////////////////
// CWordPadApp:

class CWordPadCommandLineInfo : public CCommandLineInfo
{
public:
	 CWordPadCommandLineInfo() { m_bForceTextMode = FALSE; }
	 BOOL m_bForceTextMode;
	virtual void ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast);
};

class CWordPadApp : public CWinApp
{
public:
	CWordPadApp();
	~CWordPadApp();

	CWordPadCommandLineInfo cmdInfo;

// Attributes that shouldn't be.
	CDC DcScreen;
	LOGFONT LogFont;
	int DefFont;

	CDocOptions OptionsText;
	CDocOptions OptionsRTF;
	CDocOptions OptionsIP;
	CDocOptions OptionsNull;

	// ??????????
	CRect m_rectPageMargin;
	CRect m_rectInitialFrame;
	BOOL m_bMaximized;
	BOOL m_bLargeIcons;
	BOOL m_bWordSel;
	DocType m_nNewDocType;

	// Mystery stuff.
	CList<HWND, HWND> m_listPrinterNotify;
	static int m_nOpenMsg;
	static int m_nPrinterChangedMsg;

// Attributes
	BOOL IsDocOpen(LPCTSTR lpszFileName);
	int GetUnits() { return m_nUnits; }
	int GetTPU() { return GetTPU(m_nUnits); }
	int GetTPU(int n) { return m_units[n].m_nTPU; }
	LPCTSTR GetAbbrev() { return m_units[m_nUnits].m_strAbbrev; }
	LPCTSTR GetAbbrev(int n) { return m_units[n].m_strAbbrev; }
	const CUnit& GetUnit() { return m_units[m_nUnits]; }
	CDockState& GetDockState(DocType nDocType, BOOL bPrimary = TRUE);
	CDocOptions& GetDocOptions(DocType nDocType);

	void SetUnits(int n) { ASSERT(n >= 0 && n < m_nPrimaryNumUnits); m_nUnits = n; }

// Operations
#ifdef _REGISTER_APP
	void UpdateRegistry();
#endif
	void RegisterClipboardFormats();

	static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
	void NotifyPrinterChanged(BOOL bUpdatePrinterSelection = FALSE);
	BOOL PromptForFileName(CString& fileName);
	BOOL ParseMeasurement(TCHAR* buf, int& lVal);
	void PrintTwips(TCHAR* buf, int nSize, int nValue, int nDecimal);
	void SaveOptions();
	void LoadOptions();
	void LoadAbbrevStrings();
	HGLOBAL CreateDevNames();

// Overrides
	BOOL IsIdleMessage(MSG* pMsg);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordPadApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnDDECommand(LPTSTR lpszCommand);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
	// Server object for document creation

	//{{AFX_MSG(CWordPadApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nUnits;
	static const int m_nPrimaryNumUnits;
	static const int m_nNumUnits;
	static CUnit m_units[7];

	//CList<CString> GetDocTypeInfo(int nID);
};

/////////////////////////////////////////////////////////////////////////////

// This is not the right way to do this!
extern CWordPadApp theApp;
//inline CWordPadApp* GetWordPadApp() { return (CWordPadApp*)AfxGetApp(); }
