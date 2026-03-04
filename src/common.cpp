#include "pch.h"


void GetMultipartResource(int nID, CArray<CString>& res)
{
	res.RemoveAll();
	CString strSub;
	CString str;
	str.LoadString(nID);

	int i = 0;
	while (AfxExtractSubString(strSub, str, i++, '\n'))
		res.Add(strSub);
}

CString GetFileExt(int nID)
{
	CArray<CString> parts;
	GetMultipartResource(nID, parts);
	return parts.GetAt(1);
}

DocType GetDocTypeFromName(LPCTSTR pszPathName, CFileException& fe)
{
	DocType ret = DocType::RD_INVALID;

	CFileStatus status;
	if (CFile::GetStatus(pszPathName, status))
	{
		CString sfn = CString(pszPathName);
		if (sfn.GetLength() >= 4)
		{
			CString ext = CString(pszPathName).Right(4);

			if (lstrcmpi(ext, GetFileExt(IDS_RTF_DOC)) == 0)
			{
				ret = DocType::RD_RTF;
			}
			else // assume text
			{
				ret = DocType::RD_TEXT;
			}
		}
	}

	return ret;
}
