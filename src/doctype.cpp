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
#include "doctype.h"

//TODO Refactor doctype, maybe with wordpdoc.

#ifdef _DEBUG
#undef THIS_FILE	
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static const BYTE byteRTFPrefix[5] = {'{', '\\', 'r', 't', 'f'};
static const BYTE byteExePrefix[2] = {0x4D, 0x5A};

//#define DOCTYPE_DOCTYPE 0
//#define DOCTYPE_DESC 1
//#define DOCTYPE_EXT 2
//#define DOCTYPE_PROGID 3

//#define DECLARE_DOCTYPE(name, b1, b2, b3, p) { RD_##name, IDS_##name##_DOC, b1, b2, b3, p }
//#define DECLARE_DOCTYPE_NULL(name, b1, b2, b3, p) { RD_##name, NULL, b1, b2, b3, p }

/////////////////////////////////////////////////////////////////////////////

//struct DocTypeDesc
//{
//public:
//	DocType eID;
//	int idStr;
//	BOOL bRead;
//	BOOL bWrite;
//	BOOL bDup;
//	LPCSTR pszConverterName;
//	//CString GetString(int nID);
//};
//
//DocTypeDesc doctypes [] =//(int)DocType::NUM_DOC_TYPES] =
//{
//	{ DocType::RD_RTF, IDS_RTF_DOC, TRUE, TRUE, FALSE, NULL },
//	{ DocType::RD_TEXT, IDS_TEXT_DOC, TRUE, TRUE, FALSE, NULL },
//	{ DocType::RD_ALL, IDS_ALL_DOC, TRUE, TRUE, FALSE, NULL },
//	//{ DocType::RD_EXE, IDS_EXE_DOC, TRUE, TRUE, FALSE, NULL },
//	{ DocType::RD_EMBEDDED, -1, TRUE, TRUE, FALSE, NULL },
//};
//
//const int NUM_DOC_TYPES = sizeof(doctypes) / sizeof(DocTypeDesc);

//DocType GetDocTypeFromName(LPCTSTR pszPathName, CFileException& fe)
//{
//	return DocType::RD_INVALID;
//}


//void ScanForConverters()
//{
//	int i = 999;
//}





//struct DocTypeDesc
//{
//public:
//	int nID;
//	int idStr;
//	BOOL bRead;
//	BOOL bWrite;
//	BOOL bDup;
//	LPCSTR pszConverterName;
//	CString GetString(int nID);
//};
//
//DocTypeDesc doctypes[NUM_DOC_TYPES] =
//{
//	DECLARE_DOCTYPE(RTF, TRUE, TRUE, FALSE, NULL),
//	DECLARE_DOCTYPE(TEXT, TRUE, TRUE, FALSE, NULL),
//	DECLARE_DOCTYPE(ALL, TRUE, FALSE, FALSE, NULL),
//	DECLARE_DOCTYPE(EXE, FALSE, FALSE, FALSE, NULL),
//	DECLARE_DOCTYPE_NULL(EMBEDDED, FALSE, FALSE, FALSE, NULL)
//};



//CString DocType::GetString(int nID)
//{
//	ASSERT(idStr != NULL);
//	CString str;
//	VERIFY(str.LoadString(idStr));
//	CString strSub;
//	AfxExtractSubString(strSub, str, nID);
//	return strSub;
//}

/*
static BOOL IsLeadMatch(CFile& file, const BYTE* pb, UINT nCount)
{
	// check for match at beginning of file
	BOOL b = FALSE;
	BYTE* buf = new BYTE[nCount];

	file.SeekToBegin();
	memset(buf, 0, nCount);
	file.Read(buf, nCount);
	if (memcmp(buf, pb, nCount) == 0)
	{
		b = TRUE;
	}

	delete [] buf;
	return b;
}

DocType GetDocTypeFromName(LPCTSTR pszPathName, CFileException& fe)
{
	CFile file;
	ASSERT(pszPathName != NULL);

	if (!file.Open(pszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		return DocType::RD_INVALID;
	}

	CFileStatus stat;
	VERIFY(file.GetStatus(stat));

	if (stat.m_size == 0) // file is empty
	{
		CString ext = CString(pszPathName).Right(4);
		if (ext[0] != '.')
		{
			return DocType::RD_TEXT;
		}
		if (lstrcmpi(ext, _T(".rtf"))==0)
		{
			return DocType::RD_RTF;
		}
		return DocType::RD_TEXT;
	}

	// RTF
	if (IsLeadMatch(file, byteRTFPrefix, sizeof(byteRTFPrefix)))
	{
		return DocType::RD_RTF;
	}

	// EXE
	if (IsLeadMatch(file, byteExePrefix, sizeof(byteExePrefix)))
	{
		return DocType::RD_EXE;
	}

	// default
	return DocType::RD_TEXT;
}

#ifdef _CONVERTERS
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
#endif

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
DocType GetTypeFromIndex(int nIndex, BOOL bOpen)
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
int GetIndexFromType(DocType nType, BOOL bOpen)
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
			str += doctypes[i].GetString(DOCTYPE_DESC); 1
			str += (TCHAR)NULL;
			str += doctypes[i].GetString(DOCTYPE_EXT); 2
			str += (TCHAR)NULL;
		}
		else if (!bOpen && doctypes[i].bWrite && !doctypes[i].bDup)
		{
			str += doctypes[i].GetString(DOCTYPE_DOCTYPE); 0
			str += (TCHAR)NULL;
			str += doctypes[i].GetString(DOCTYPE_EXT); 2
			str += (TCHAR)NULL;
		}
	}
	return str;
}
*/
