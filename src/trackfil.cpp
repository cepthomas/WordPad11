// convert.cpp : implementation file
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
#include "trackfil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CTrackFile::CTrackFile(CFrameWnd* pWnd) : CFile()
{
	m_nLastPercent = -1;
	m_dwLength = 0;
	m_pFrameWnd = pWnd;
	VERIFY(m_strComplete.LoadString(IDS_COMPLETE));
	VERIFY(m_strWait.LoadString(IDS_PLEASE_WAIT));
	VERIFY(m_strSaving.LoadString(IDS_SAVING));
//  OutputPercent(0);
}

CTrackFile::~CTrackFile()
{
	OutputPercent(100);
	if (m_pFrameWnd != NULL)
		m_pFrameWnd->SetMessageText(AFX_IDS_IDLEMESSAGE);
}

UINT CTrackFile::Read(void FAR* lpBuf, UINT nCount)
{
	UINT n = CFile::Read(lpBuf, nCount);
	if (m_dwLength != 0)
		OutputPercent((int)((GetPosition()*100)/m_dwLength));
	return n;
}

void CTrackFile::Write(const void FAR* lpBuf, UINT nCount)
{
	CFile::Write(lpBuf, nCount);
	OutputString(m_strSaving);
//  if (m_dwLength != 0)
//      OutputPercent((int)((GetPosition()*100)/m_dwLength));
}

void CTrackFile::OutputString(LPCTSTR lpsz)
{
	if (m_pFrameWnd != NULL)
	{
		m_pFrameWnd->SetMessageText(lpsz);
		CWnd* pBarWnd = m_pFrameWnd->GetMessageBar();
		if (pBarWnd != NULL)
			pBarWnd->UpdateWindow();
	}
}

void CTrackFile::OutputPercent(int nPercentComplete)
{
	if (m_pFrameWnd != NULL && m_nLastPercent != nPercentComplete)
	{
		m_nLastPercent = nPercentComplete;
		TCHAR buf[64];
		int n = nPercentComplete;
		_stprintf_s(buf, 64, (n==100) ? m_strWait : m_strComplete, n);
		OutputString(buf);
	}
}

