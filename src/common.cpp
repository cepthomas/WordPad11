#include "pch.h"


// TODO ddxm.*
// TODO remove all extern -> better api
// TODO remove IsTextType
// TODO inline CWordPadApp* GetWordPadApp() {return (CWordPadApp*)AfxGetApp();} and AfxGetApp()->CreatePrinterDC(dc);


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

			if (lstrcmpi(ext, _T(".rtf")) == 0) // TODO get from resources
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
