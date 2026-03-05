// wordpdoc.cpp : implementation of the CWordPadDoc class
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
#include "wordpdoc.h"
#include "wordpad.h"
#include "wordpvw.h"
#include "cntritem.h"
#include "srvritem.h"
#include "buttondi.h"
#include "optionsh.h"
#include "trackfil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWordPadDoc
IMPLEMENT_DYNCREATE(CWordPadDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CWordPadDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CWordPadDoc)
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_POPUP, OnUpdateOleVerbPopup)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateIfEmbedded)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateIfEmbedded)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateIfEmbedded)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateIfEmbedded)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_DIRECT, OnUpdateIfEmbedded)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateIfEmbedded)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, CRichEditDoc::OnUpdateObjectVerbMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, CRichEditDoc::OnUpdateObjectVerbMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordPadDoc construction/destruction

CWordPadDoc::CWordPadDoc()
{
	m_nDocType = DocType::RD_INVALID;
	m_nNewDocType = DocType::RD_INVALID;
}

BOOL CWordPadDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// Default type is always rtf.
	DocType nDocType = (IsEmbedded()) ? DocType::RD_EMBEDDED : DocType::RD_RTF;

	GetView()->SetDefaultFont(nDocType == DocType::RD_TEXT); // TODO should be set by SetDocType()???
	SetDocType(nDocType);

	return TRUE;
}

void CWordPadDoc::ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDP)
{
	if (!m_bDeferErrors && e != NULL)
	{
		ASSERT_VALID(e);
		if (e->IsKindOf(RUNTIME_CLASS(CFileException)))
		{
			switch (((CFileException*)e)->m_cause)
			{
			case CFileException::fileNotFound:
			case CFileException::badPath:
				nIDP = AFX_IDP_FAILED_INVALID_PATH;
				break;
			case CFileException::diskFull:
				nIDP = AFX_IDP_FAILED_DISK_FULL;
				break;
			case CFileException::accessDenied:
				nIDP = bSaving ? AFX_IDP_FAILED_ACCESS_WRITE : AFX_IDP_FAILED_ACCESS_READ;
				if (((CFileException*)e)->m_lOsError == ERROR_WRITE_PROTECT)
					nIDP = IDS_WRITEPROTECT;
				break;
			case CFileException::tooManyOpenFiles:
				nIDP = IDS_TOOMANYFILES;
				break;
			case CFileException::directoryFull:
				nIDP = IDS_DIRFULL;
				break;
			case CFileException::sharingViolation:
				nIDP = IDS_SHAREVIOLATION;
				break;
			case CFileException::lockViolation:
			case CFileException::badSeek:
			case CFileException::genericException:
			case CFileException::invalidFile:
			case CFileException::hardIO:
				nIDP = bSaving ? AFX_IDP_FAILED_IO_ERROR_WRITE :
						AFX_IDP_FAILED_IO_ERROR_READ;
				break;
			default:
				break;
			}
			CString prompt;
			AfxFormatString1(prompt, nIDP, lpszPathName);
			AfxMessageBox(prompt, MB_ICONEXCLAMATION, nIDP);
			return;
		}
	}
	CRichEditDoc::ReportSaveLoadException(lpszPathName, e, bSaving, nIDP);
	return;
}

BOOL CWordPadDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (m_lpRootStg != NULL) // we are embedded
	{
		// we really want to use the converter on this storage
		m_nNewDocType = DocType::RD_EMBEDDED;
	}
	else
	{
		CFileException fe;
		m_nNewDocType = GetDocTypeFromName(lpszPathName, fe);
		if (m_nNewDocType == DocType::RD_INVALID)
		{
			// Assume/try text.
			m_nNewDocType = DocType::RD_TEXT;
			//ReportSaveLoadException(lpszPathName, &fe, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			//	AfxMessageBox(str, MB_OK|MB_ICONINFORMATION);
			//return FALSE;
		}
	}

	//SetDocType(nNewDocType);
	if (!CRichEditDoc::OnOpenDocument(lpszPathName))
		return FALSE;

	return TRUE;
}

void CWordPadDoc::Serialize(CArchive& ar)
{
	COleMessageFilter* pFilter = AfxOleGetMessageFilter();
	ENSURE(pFilter != NULL);
	pFilter->EnableBusyDialog(FALSE);
	if (ar.IsLoading())
		SetDocType(m_nNewDocType);
	CRichEditDoc::Serialize(ar);
	pFilter->EnableBusyDialog(TRUE);
}

BOOL CWordPadDoc::DoSave(LPCTSTR pszPathName, BOOL bReplace) // TODO if type to save is txt and doc has rtf content, do something - below GetView()->IsFormatText()
{
	// Save the document data to a file
	// pszPathName = path name where to save document file
	// if pszPathName is empty/NULL then the user will be prompted (SaveAs)
	// note: pszPathName can be different than 'm_strPathName'
	// if 'bReplace' is TRUE will change file name if successful (SaveAs)
	// if 'bReplace' is FALSE will not change path name (SaveCopyAs)
	CString newName = pszPathName;
	DocType nOrigDocType = m_nDocType;  //saved in case of SaveCopyAs or failure

	//  newName     bWrite  type    result
	//  empty       TRUE    -       SaveAs dialog
	//  empty       FALSE   -       SaveAs dialog
	//  notempty    TRUE    -       nothing
	//  notempty    FALSE   W6      warn (change to wordpad, save as, cancel)
	//  notempty    FALSE   other   warn (save as, cancel)

	BOOL bModified = IsModified();

	BOOL bSaveAs = FALSE;

	if (newName.IsEmpty())
	{
		bSaveAs = TRUE;
	}
	//else if (!doctypes[m_nDocType].bWrite)
	//{
	//	if (AfxMessageBox(IDS_SAVE_UNSUPPORTED, MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
	//	{
	//		return FALSE;
	//	}
	//	else
	//	{
	//		bSaveAs = TRUE;
	//	}
	//}

	//if (m_lpRootStg == NULL && m_nDocType == DocType::RD_TEXT && !GetView()->IsFormatText())
	//{
	//	// formatting changed in plain old text file
	//	CString str;
	//	AfxFormatString1(str, IDS_SAVE_FORMAT_TEXT, GetTitle());
	//	INT_PTR nRes = CButtonDialog::DisplayMessageBox(str,
	//		MAKEINTRESOURCE(AFX_IDS_APP_TITLE),
	//		MAKEINTRESOURCE(IDS_TF_BUTTONS), MB_ICONEXCLAMATION, 0, 3);
	//	if (nRes == 3)
	//	{
	//		return FALSE;
	//	}

	//	DocType nDocType = (nRes == 0) ? DocType::RD_DEFAULT: (nRes == 1) ? DocType::RD_RTF : DocType::RD_TEXT;

	//	if (m_nDocType == DocType::RD_TEXT && nDocType != DocType::RD_TEXT)
	//	{
	//		SetDocType(nDocType, TRUE);
	//	}

	//	if (nDocType != DocType::RD_TEXT)
	//	{
	//		bSaveAs = TRUE;
	//	}
	//}

	GetView()->GetParentFrame()->RecalcLayout();

	if (bSaveAs)
	{
		newName = m_strPathName;

		if (bReplace && newName.IsEmpty())
		{
			newName = m_strTitle;
			int iBad = newName.FindOneOf(_T(" #%;/\\"));    // dubious filename
			if (iBad != -1)
				newName.ReleaseBuffer(iBad);

			//// append the default suffix if there is one
			//newName += GetExtFromType(m_nDocType);
		}

		DocType nDocType = m_nDocType;
		if (!PromptForFileName(newName))
		{
			SetDocType(nOrigDocType, TRUE);
			return FALSE; // don't even try to save
		}
		SetDocType(nDocType, TRUE);
	}

	BeginWaitCursor();
	if (!OnSaveDocument(newName))
	{
		if (pszPathName == NULL)
		{
			// be sure to delete the file
			CFile::Remove(newName);
		}
		// restore orginal document type
		SetDocType(nOrigDocType, TRUE);
		EndWaitCursor();
		return FALSE;
	}

	EndWaitCursor();
	if (bReplace)
	{
		DocType nType = m_nDocType;
		SetDocType(nOrigDocType, TRUE);
		SetDocType(nType);
		// Reset the title and change the document name
		SetPathName(newName, TRUE);
		ASSERT(m_strPathName == newName);
	}
	else // SaveCopyAs
	{
		SetDocType(nOrigDocType, TRUE);
		SetModifiedFlag(bModified);
	}
	return TRUE;
}

class COIPF : public COleIPFrameWnd
{
public:
	CFrameWnd* GetMainFrame() { return m_pMainFrame;}
	CFrameWnd* GetDocFrame() { return m_pDocFrame;}
};

void CWordPadDoc::OnDeactivateUI(BOOL bUndoable)
{
	if (GetView()->m_bDelayUpdateItems)
		UpdateAllItems(NULL);
	SaveState(m_nDocType);
	CRichEditDoc::OnDeactivateUI(bUndoable);
	COIPF* pFrame = (COIPF*)m_pInPlaceFrame;
	if (pFrame != NULL)
	{
		if (pFrame->GetMainFrame() != NULL)
			ForceDelayed(pFrame->GetMainFrame());
		if (pFrame->GetDocFrame() != NULL)
			ForceDelayed(pFrame->GetDocFrame());
	}
}

void CWordPadDoc::ForceDelayed(CFrameWnd* pFrameWnd)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pFrameWnd);

	POSITION pos = pFrameWnd->m_listControlBars.GetHeadPosition();
	while (pos != NULL)
	{
		// show/hide the next control bar
		CControlBar* pBar =
			(CControlBar*)pFrameWnd->m_listControlBars.GetNext(pos);

		BOOL bVis = pBar->GetStyle() & WS_VISIBLE;
		UINT swpFlags = 0;
		if ((pBar->m_nStateFlags & CControlBar::delayHide) && bVis)
			swpFlags = SWP_HIDEWINDOW;
		else if ((pBar->m_nStateFlags & CControlBar::delayShow) && !bVis)
			swpFlags = SWP_SHOWWINDOW;
		pBar->m_nStateFlags &= ~(CControlBar::delayShow|CControlBar::delayHide);
		if (swpFlags != 0)
		{
			pBar->SetWindowPos(NULL, 0, 0, 0, 0, swpFlags|
				SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWordPadDoc Attributes
CLSID CWordPadDoc::GetClassID()
{
	return (m_pFactory == NULL) ? CLSID_NULL : m_pFactory->GetClassID();
}

void CWordPadDoc::SetDocType(DocType nNewDocType, BOOL bNoOptionChange)//TODO
{
	//ASSERT(nNewDocType != -1);
	if (nNewDocType == m_nDocType)
	{
		return;
	}

	m_bRTF = nNewDocType != DocType::RD_TEXT;

	if (bNoOptionChange)
	{
		m_nDocType = nNewDocType;
	}
	else
	{
		SaveState(m_nDocType);
		m_nDocType = nNewDocType;
		RestoreState(m_nDocType);
	}
}

CWordPadView* CWordPadDoc::GetView()
{
	POSITION pos = GetFirstViewPosition();
	return (CWordPadView*)GetNextView(pos);
}

/////////////////////////////////////////////////////////////////////////////
// CWordPadDoc Operations

CFile* CWordPadDoc::GetFile(LPCTSTR pszPathName, UINT nOpenFlags, CFileException* pException)
{
	CTrackFile* pFile = NULL;
	CFrameWnd* pWnd = GetView()->GetParentFrame();

#ifdef _CONVERTERS
	ScanForConverters();

	// if writing use current doc type otherwise use new doc type
	int nType = (nOpenFlags & CFile::modeReadWrite) ? m_nDocType : m_nNewDocType;
	// m_nNewDocType will be same as m_nDocType except when opening a new file
	if (doctypes[nType].pszConverterName != NULL)
		pFile = new CConverter(doctypes[nType].pszConverterName, pWnd);
	else
		pFile = new CTrackFile(pWnd);
#else
	pFile = new CTrackFile(pWnd);
#endif

	if (!pFile->Open(pszPathName, nOpenFlags, pException))
	{
		delete pFile;
		return NULL;
	}

	pFile->m_dwLength = nOpenFlags & (CFile::modeWrite | CFile::modeReadWrite) ?
		0 : // can't estimate this
		(DWORD)pFile->GetLength();

	return pFile;
}

CRichEditCntrItem* CWordPadDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CWordPadCntrItem(preo, (CWordPadDoc*)this);
}

/////////////////////////////////////////////////////////////////////////////
// CWordPadDoc server implementation

COleServerItem* CWordPadDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	// that is associated with the document.  It is only called when necessary.

	CEmbeddedItem* pItem = new CEmbeddedItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

/////////////////////////////////////////////////////////////////////////////
// CWordPadDoc serialization

/////////////////////////////////////////////////////////////////////////////
// CWordPadDoc diagnostics

#ifdef _DEBUG
void CWordPadDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CWordPadDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWordPadDoc commands

DocType CWordPadDoc::MapType(DocType nType)//TODO
{
	if (!IsInPlaceActive() && nType == DocType::RD_EMBEDDED)
		nType = DocType::RD_RTF;

	return nType;
}

void CWordPadDoc::OnViewOptions()
{
	DocType nType = MapType(m_nDocType);
	int nFirstPage = 1;
	if (nType == DocType::RD_TEXT)
		nFirstPage = 1;
	else if (nType == DocType::RD_RTF)
		nFirstPage = 2;
	else if (nType == DocType::RD_EMBEDDED)
		nFirstPage = 3;

	SaveState(nType);

	COptionSheet sheet(IDS_OPTIONS, NULL, nFirstPage);//TODO which page???

	if (sheet.DoModal() == IDOK)
	{
		CWordPadView* pView = GetView();
		if (theApp.m_bWordSel)
		{
			pView->GetRichEditCtrl().SetOptions(ECOOP_OR, ECO_AUTOWORDSELECTION);
		}
		else
		{
			pView->GetRichEditCtrl().SetOptions(ECOOP_AND, ~(DWORD)ECO_AUTOWORDSELECTION);
		}
		RestoreState(nType);
	}
}

void CWordPadDoc::OnUpdateOleVerbPopup(CCmdUI* pCmdUI)
{
	pCmdUI->m_pParentMenu = pCmdUI->m_pMenu;
	CRichEditDoc::OnUpdateObjectVerbMenu(pCmdUI);
}

BOOL CWordPadDoc::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (nCode == CN_COMMAND && nID == ID_OLE_VERB_POPUP)
		nID = ID_OLE_VERB_FIRST;
	return CRichEditDoc::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CWordPadDoc::SaveState(DocType nType)
{
	if (nType == DocType::RD_INVALID)
		return;
	nType = MapType(nType);
	CWordPadView* pView = GetView();
	if (pView != NULL)
	{
		CFrameWnd* pFrame = pView->GetParentFrame();
		ENSURE(pFrame != NULL);
		// save current state
		pFrame->SendMessage(WPM_BARSTATE, 0, (int)nType);
		theApp.GetDocOptions(nType).m_nWordWrap = pView->m_nWordWrap;
	}
}

void CWordPadDoc::RestoreState(DocType nType)
{
	if (nType == DocType::RD_INVALID)
		return;

	nType = MapType(nType);
	CWordPadView* pView = GetView();
	if (pView != NULL)
	{
		CFrameWnd* pFrame = pView->GetParentFrame();
		ENSURE(pFrame != NULL);
		// set new state
		pFrame->SendMessage(WPM_BARSTATE, 1, (int)nType);
		int nWrapNew = theApp.GetDocOptions(nType).m_nWordWrap;
		if (pView->m_nWordWrap != nWrapNew)
		{
			pView->m_nWordWrap = nWrapNew;
			pView->WrapChanged();
		}
	}
}

void CWordPadDoc::OnCloseDocument()
{
	SaveState(m_nDocType);
	CRichEditDoc::OnCloseDocument();
}

void CWordPadDoc::PreCloseFrame(CFrameWnd* pFrameArg)
{
	CRichEditDoc::PreCloseFrame(pFrameArg);
	SaveState(m_nDocType);
}

void CWordPadDoc::OnUpdateIfEmbedded(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!IsEmbedded());
}
