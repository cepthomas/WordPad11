// richdoc.cpp : implementation of the CRichEditDoc class
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

#include "doctype.h"
// #include "resource.h"
// #include "strings.h"
//#include "multconv.h"

#ifdef _DEBUG
#undef THIS_FILE	
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static const BYTE byteRTFPrefix[5] = {'{', '\\', 'r', 't', 'f'};
static const BYTE byteExePrefix[2] = {0x4D, 0x5A};

/////////////////////////////////////////////////////////////////////////////


DocType doctypes[NUM_DOC_TYPES] =
{
	DECLARE_DOCTYPE(RICHTEXT, TRUE, TRUE, FALSE, NULL),
	DECLARE_DOCTYPE(TEXT, TRUE, TRUE, FALSE, NULL),
	DECLARE_DOCTYPE(ALL, TRUE, FALSE, FALSE, NULL),
	DECLARE_DOCTYPE(EXE, FALSE, FALSE, FALSE, NULL),
	DECLARE_DOCTYPE_NULL(EMBEDDED, FALSE, FALSE, FALSE, NULL)
};

CString DocType::GetString(int nID)
{
	ASSERT(idStr != NULL);
	CString str;
	VERIFY(str.LoadString(idStr));
	CString strSub;
	AfxExtractSubString(strSub, str, nID);
	return strSub;
}

static BOOL IsLeadMatch(CFile& file, const BYTE* pb, UINT nCount)
{
	// check for match at beginning of file
	BOOL b = FALSE;
	BYTE* buf = new BYTE[nCount];

	TRY
	{
		file.SeekToBegin();
		memset(buf, 0, nCount);
		file.Read(buf, nCount);
		if (memcmp(buf, pb, nCount) == 0)
		{
			b = TRUE;
		}
	}
	END_TRY

	delete [] buf;
	return b;
}

int GetDocTypeFromName(LPCTSTR pszPathName, CFileException& fe)
{
	CFile file;
	ASSERT(pszPathName != NULL);

	if (!file.Open(pszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		return -1;
	}

	CFileStatus stat;
	VERIFY(file.GetStatus(stat));

	if (stat.m_size == 0) // file is empty
	{
		CString ext = CString(pszPathName).Right(4);
		if (ext[0] != '.')
		{
			return RD_TEXT;
		}
		if (lstrcmpi(ext, _T(".rtf"))==0)
		{
			return RD_RICHTEXT;
		}
		return RD_TEXT;
	}

	// RTF
	if (IsLeadMatch(file, byteRTFPrefix, sizeof(byteRTFPrefix)))
	{
		return RD_RICHTEXT;
	}

	// EXE
	if (IsLeadMatch(file, byteExePrefix, sizeof(byteExePrefix)))
	{
		return RD_EXE;
	}

	// default
	return RD_TEXT;
}

void ScanForConverters()
{
	static BOOL bScanned = FALSE;
	if (bScanned)
	{
		return;
	}

	for (int i = 0; i < NUM_DOC_TYPES; i++)
	{
		LPCSTR lpsz = doctypes[i].pszConverterName;
		// if converter specified but can't find it
		if (lpsz != NULL && *lpsz != NULL && !IsDLLInPath(lpsz))
		{
			doctypes[i].bRead = doctypes[i].bWrite = FALSE;
		}
	}

	bScanned = TRUE;
}

BOOL IsDLLInPath(LPCSTR lpszName)
{
	ASSERT(lpszName != NULL);
	OFSTRUCT ofs;
	return (OpenFile(lpszName, &ofs, OF_EXIST) != HFILE_ERROR);
}

CString GetExtFromType(int nDocType)
{
	ScanForConverters();

	CString str = doctypes[nDocType].GetString(DOCTYPE_EXT);
	if (!str.IsEmpty())
	{
		ASSERT(str.GetLength() == 5); // "*.ext"
		ASSERT(str[1] == '.');
		return str.Right(str.GetLength()-1);
	}
	return str;
}

// returns an RD_* from an index into the openfile dialog types
int GetTypeFromIndex(int nIndex, BOOL bOpen)
{
	ScanForConverters();

	int nCnt = 0;
	for (int i = 0; i < NUM_DOC_TYPES; i++)
	{
		if (!doctypes[i].bDup && (bOpen ? doctypes[i].bRead : doctypes[i].bWrite))
		{
			if (nCnt == nIndex)
			{
				return i;
			}
			nCnt++;
		}
	}

	ASSERT(FALSE);
	return -1;
}

// returns an index into the openfile dialog types for the RD_* type
int GetIndexFromType(int nType, BOOL bOpen)
{
	ScanForConverters();

	int nCnt = 0;
	for (int i = 0; i < NUM_DOC_TYPES; i++)
	{
		if (!doctypes[i].bDup && (bOpen ? doctypes[i].bRead : doctypes[i].bWrite))
		{
			if (i == nType)
			{
				return nCnt;
			}
			nCnt++;
		}
	}
	return -1;
}

CString GetFileTypes(BOOL bOpen)
{
	ScanForConverters();

	CString str;
	for (int i = 0; i < NUM_DOC_TYPES; i++)
	{
		if (bOpen && doctypes[i].bRead && !doctypes[i].bDup)
		{
			str += doctypes[i].GetString(DOCTYPE_DESC);
			str += (TCHAR)NULL;
			str += doctypes[i].GetString(DOCTYPE_EXT);
			str += (TCHAR)NULL;
		}
		else if (!bOpen && doctypes[i].bWrite && !doctypes[i].bDup)
		{
			str += doctypes[i].GetString(DOCTYPE_DOCTYPE);
			str += (TCHAR)NULL;
			str += doctypes[i].GetString(DOCTYPE_EXT);
			str += (TCHAR)NULL;
		}
	}
	return str;
}
