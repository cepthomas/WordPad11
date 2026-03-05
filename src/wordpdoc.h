// wordpdoc.h : interface of the CWordPadDoc class
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

#include "formatba.h"
#include "srvritem.h"
#include "wordpvw.h"


class CWordPadDoc : public CRichEditDoc
{
private:
	using CRichEditDoc::GetView;

protected: // create from serialization only
	CWordPadDoc();
	DECLARE_DYNCREATE(CWordPadDoc)

// Attributes
	CLSID GetClassID();
	
private:
	DocType m_nDocType;
	DocType m_nNewDocType;
	void SetDocType(DocType nDocType, BOOL bNoOptionChange = FALSE);
	CWordPadView* GetView();
	LPCTSTR GetSection();

// Operations
public:
	void SaveState(DocType nType);
	void RestoreState(DocType nType);
	virtual CFile* GetFile(LPCTSTR pszPathName, UINT nOpenFlags, CFileException* pException);
	virtual BOOL DoSave(LPCTSTR pszPathName, BOOL bReplace = TRUE);
	DocType MapType(DocType nType);
	void ForceDelayed(CFrameWnd* pFrameWnd);

// Overrides
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual void Serialize(CArchive& ar);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordPadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void OnCloseDocument();
	virtual void ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault);
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void PreCloseFrame(CFrameWnd* pFrameArg);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CWordPadDoc)
	afx_msg void OnViewOptions();
	afx_msg void OnUpdateOleVerbPopup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIfEmbedded(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
