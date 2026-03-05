#include "pch.h"


void SplitStringResource(int nID, CArray<CString>& res)
{
	res.RemoveAll();
	CString strSub;
	CString str;
	str.LoadString(nID);

	int i = 0;
	while (AfxExtractSubString(strSub, str, i))
	{
		res.Add(strSub);
		i++;
	}


	//CString sInput("one+two+three");
	//CString sToken("");
	//int i = 0; // substring index to extract
	//while (AfxExtractSubString(sToken, sInput, i, '+'))
	//{
	//	res.Add(sToken);
	//	i++;
	//}
}

CString GetFileExt(int nID)
{
	CArray<CString> parts;
	SplitStringResource(nID, parts);
	return parts.GetAt(1);
}

DocType GetDocTypeFromName(LPCTSTR pszPathName, CFileException& fe)
{
	DocType ret = DocType::RD_INVALID;

	CFileStatus status;
	if (CFile::GetStatus(pszPathName, status))
	{
		CString sfn = CString(pszPathName);
		
		CString extRtf = CString(".") + GetFileExt(IDS_RTF_DOC);
		CString extText = CString(".") + GetFileExt(IDS_TEXT_DOC);

		if (sfn.Find(extRtf) > 0) { ret = DocType::RD_RTF; }
		if (sfn.Find(extText) > 0) { ret = DocType::RD_TEXT; }
	}

	return ret;
}


// Use standard format - pipes.
CString FormatForFileDialog(int nID)
{
	CArray<CString> parts;
	SplitStringResource(nID, parts);
	CString str;
	str.Format(_T("%s (*.%s)|*.%s|"), parts.GetAt(0), parts.GetAt(1), parts.GetAt(1));
	return str;
}


BOOL PromptForFileName(CString& fileName)
{
	BOOL ret = FALSE;

	if (fileName.GetLength() == 0)
	{
		CString title;
		title.LoadString(AFX_IDS_OPENFILE);
		CString filter = FormatForFileDialog(IDS_RTF_DOC) + FormatForFileDialog(IDS_TEXT_DOC) + FormatForFileDialog(IDS_ALL_DOC);
		CFileDialog dlg(TRUE, GetFileExt(IDS_RTF_DOC), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter, NULL);
		dlg.m_ofn.lpstrTitle = title;

		// Display the dialog box
		if (dlg.DoModal() == IDOK)
		{
			// Get the full path of the selected file
			fileName = dlg.GetPathName();
			ret = TRUE;
		}
	}
	else // save as
	{
		CString title;
		title.LoadString(AFX_IDS_SAVEFILE);
		CString filter = FormatForFileDialog(IDS_RTF_DOC) + FormatForFileDialog(IDS_TEXT_DOC);
		CFileDialog dlg(FALSE, GetFileExt(IDS_RTF_DOC), fileName, OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, filter, NULL);
		dlg.m_ofn.lpstrTitle = title;

		// Display the dialog box
		if (dlg.DoModal() == IDOK)
		{
			// Get the full path of the selected file
			fileName = dlg.GetPathName();
			ret = TRUE;
		}
	}

	return ret;
}
