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
#include <winreg.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#ifndef _REGISTER_APP
// Log reg writes without actually performing.
#include "Windows.h"
const int MSIZE = 500;
char message[MSIZE+1];
#pragma warning(disable : 4302 4311)
#endif


/////////////////////////////////////////////////////////////////////////////
// CKey

void CKey::Close()
{
#ifndef _REGISTER_APP
	snprintf(message, MSIZE, "Close() [%ld]\n", (unsigned long)m_hKey);
	OutputDebugStringA(message);
#else
	if (m_hKey != NULL)
	{
		LONG lRes = RegCloseKey(m_hKey);
		ASSERT(lRes == ERROR_SUCCESS);
		m_hKey = NULL;
	}
#endif
}

BOOL CKey::Create(HKEY hKey, LPCTSTR lpszKeyName)
{
#ifndef _REGISTER_APP
	snprintf(message, MSIZE, "Create() [%ld] [%ws]\n", (unsigned long)hKey, lpszKeyName);
	m_hKey = hKey;
	OutputDebugStringA(message);
	return TRUE;
#else
	ASSERT(hKey != NULL);
	return (RegCreateKey(hKey, lpszKeyName, &m_hKey) == ERROR_SUCCESS);
#endif
}

BOOL CKey::Open(HKEY hKey, LPCTSTR lpszKeyName)
{
#ifndef _REGISTER_APP
	snprintf(message, MSIZE, "Open() [%ld] [%ws]\n", (unsigned long)hKey, lpszKeyName);
	OutputDebugStringA(message);
	return TRUE;
#else
	ASSERT(hKey != NULL);
	return (RegOpenKey(hKey, lpszKeyName, &m_hKey) == ERROR_SUCCESS);
#endif
}

BOOL CKey::SetStringValue(LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
#ifndef _REGISTER_APP
	snprintf(message, MSIZE, "SetStringValue() [%ld] [%ws] [%ws]\n", (unsigned long)m_hKey, lpszValue, lpszValueName);
	OutputDebugStringA(message);
	return TRUE;
#else
	ASSERT(m_hKey != NULL);
	return (RegSetValueEx(m_hKey, lpszValueName, NULL, REG_SZ, (BYTE* const)lpszValue, (lstrlen(lpszValue) + 1) * sizeof(TCHAR)) == ERROR_SUCCESS);
#endif
}

BOOL CKey::GetStringValue(CString& str, LPCTSTR lpszValueName)
{
#ifndef _REGISTER_APP
	snprintf(message, MSIZE, "GetStringValue() [%ld] [%ws]\n", (unsigned long)m_hKey, lpszValueName);
	OutputDebugStringA(message);
	str = "something";
	return TRUE;
#else
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
#endif
}
