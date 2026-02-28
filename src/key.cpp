// key.cpp : implementation file
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
#include "key.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define _FAKE



/////////////////////////////////////////////////////////////////////////////
// CKey

#ifndef _FAKE
#include <winreg.h>

BOOL CKey::Create(HKEY hKey, LPCTSTR lpszKeyName)
{
	ASSERT(hKey != NULL);
	return (RegCreateKey(hKey, lpszKeyName, &m_hKey) == ERROR_SUCCESS);
}

BOOL CKey::Open(HKEY hKey, LPCTSTR lpszKeyName)
{
	ASSERT(hKey != NULL);
	return (RegOpenKey(hKey, lpszKeyName, &m_hKey) == ERROR_SUCCESS);
}

void CKey::Close()
{
	if (m_hKey != NULL)
	{
		LONG lRes = RegCloseKey(m_hKey);
		ASSERT(lRes == ERROR_SUCCESS);
		m_hKey = NULL;
	}
}

BOOL CKey::SetStringValue(LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	ASSERT(m_hKey != NULL);
	return (RegSetValueEx(m_hKey, lpszValueName, NULL, REG_SZ, (BYTE* const)lpszValue, (lstrlen(lpszValue) + 1) * sizeof(TCHAR)) == ERROR_SUCCESS);
}

BOOL CKey::GetStringValue(CString& str, LPCTSTR lpszValueName)
{
	ASSERT(m_hKey != NULL);
	str.Empty();
	DWORD dw = 0;
	DWORD dwType = 0;
	LONG lRes = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL, &dwType, NULL, &dw);
	if (lRes == ERROR_SUCCESS)
	{
		ASSERT(dwType == REG_SZ);
		LPTSTR lpsz = str.GetBufferSetLength(dw);
		lRes = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL, &dwType, (BYTE*)lpsz, &dw);
		ASSERT(lRes == ERROR_SUCCESS);
		str.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

#else
#pragma warning(disable: 4302 4311)

// Log reg writes without actually performing.
BOOL CKey::Create(HKEY hKey, LPCTSTR lpszKeyName)
{
	TRACE2("Create() [%ld] [%ws]\n", (unsigned long)hKey, lpszKeyName);
	m_hKey = hKey;
	return TRUE;
}

BOOL CKey::Open(HKEY hKey, LPCTSTR lpszKeyName)
{
	TRACE2("Open() [%ld] [%ws]\n", (unsigned long)hKey, lpszKeyName);
	return TRUE;
}

void CKey::Close()
{
	TRACE1("Close() [%ld]\n", (unsigned long)m_hKey);
	m_hKey = 0;
}

BOOL CKey::SetStringValue(LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	TRACE3("SetStringValue() [%ld] [%ws] [%ws]\n", (unsigned long)m_hKey, lpszValue, lpszValueName);
	return TRUE;
}

BOOL CKey::GetStringValue(CString& str, LPCTSTR lpszValueName)
{
	TRACE2("GetStringValue() [%ld] [%ws]\n", (unsigned long)m_hKey, lpszValueName);
	str = "something";
	return TRUE;
}

#endif
