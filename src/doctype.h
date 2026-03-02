// doctype.h : header file
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

//#define RD_RTF 0
//#define RD_TEXT 1
//#define RD_ALL 2
//#define RD_EXE 3
//#define RD_EMBEDDED 4
//#define NUM_DOC_TYPES 5
//#define RD_DEFAULT RD_RTF
//#define RD_NATIVE RD_RTF


// TODO these
//extern DocType GetDocTypeFromName(LPCTSTR pszPathName, CFileException& fe);
//extern DocType doctypes[NUM_DOC_TYPES];


// XX typedef BOOL (*PISFORMATFUNC)(LPCSTR pszConverter, LPCSTR pszPathName);
// XX inline BOOL IsTextType(LONG_PTR nType) {return nType == RD_TEXT;}
//
//struct DocType
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
//extern DocType doctypes[NUM_DOC_TYPES];
//extern int GetDocTypeFromName(LPCTSTR pszPathName, CFileException& fe);
//extern void ScanForConverters();
//extern BOOL IsDLLInPath(LPCSTR lpszName);
//
//int GetIndexFromType(int nType, BOOL bOpen);
//int GetTypeFromIndex(int nType, BOOL bOpen);
//CString GetExtFromType(int nDocType);
//CString GetFileTypes(BOOL bOpen);
