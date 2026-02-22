// convert.h : header file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


/////////////////////////////////////////////////////////////////////////////
// CTrackFile
class CTrackFile : public CFile
{
public:
	//Construction
	CTrackFile(CFrameWnd* pWnd);
	~CTrackFile();

	//Attributes
	int m_nLastPercent;
	DWORD m_dwLength;
	CFrameWnd* m_pFrameWnd;
	CString m_strComplete;
	CString m_strWait;
	CString m_strSaving;
	//Operations
	void OutputPercent(int nPercentComplete = 0);
	void OutputString(LPCTSTR lpsz);
	virtual UINT Read(void FAR* lpBuf, UINT nCount);
	virtual void Write(const void FAR* lpBuf, UINT nCount);
};


/////////////////////////////////////////////////////////////////////////////
