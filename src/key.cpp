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
// Log reg writes without actually performing.
#include "Windows.h"
const int MSIZE = 500;
char message[MSIZE+1];
#pragma warning(disable : 4302 4311)

BOOL CKey::Create(HKEY hKey, LPCTSTR lpszKeyName)
{
	snprintf(message, MSIZE, "Create() [%ld] [%ws]\n", (unsigned long)hKey, lpszKeyName);
	m_hKey = hKey;
	OutputDebugStringA(message);
	return TRUE;
}

BOOL CKey::Open(HKEY hKey, LPCTSTR lpszKeyName)
{
	snprintf(message, MSIZE, "Open() [%ld] [%ws]\n", (unsigned long)hKey, lpszKeyName);
	OutputDebugStringA(message);
	return TRUE;
}

void CKey::Close()
{
	snprintf(message, MSIZE, "Close() [%ld]\n", (unsigned long)m_hKey);
	OutputDebugStringA(message);
}

BOOL CKey::SetStringValue(LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	snprintf(message, MSIZE, "SetStringValue() [%ld] [%ws] [%ws]\n", (unsigned long)m_hKey, lpszValue, lpszValueName);
	OutputDebugStringA(message);
	return TRUE;
}

BOOL CKey::GetStringValue(CString& str, LPCTSTR lpszValueName)
{
	snprintf(message, MSIZE, "GetStringValue() [%ld] [%ws]\n", (unsigned long)m_hKey, lpszValueName);
	OutputDebugStringA(message);
	str = "something";
	return TRUE;
}

#endif
