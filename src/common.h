#pragma once

// Miscellaneous definitions and utilities that have no better home.

///// Lonely lost items. /////
const int HORZ_TEXTOFFSET = 15;
const int VERT_TEXTOFFSET = 5;
const int FN_SETFORMAT = 0x1000;
const int FN_GETFORMAT = 0x1001;


///// Types. /////
enum class DocType
{
    RD_RTF,
    RD_TEXT,
    RD_ALL,
    RD_EMBEDDED,
    RD_DEFAULT = RD_RTF,
    RD_INVALID = -1  // bad file
};

class CDisplayIC : public CDC
{
public:
    CDisplayIC() { CreateIC(_T("DISPLAY"), NULL, NULL, NULL); }
};

struct CCharFormat : public CHARFORMAT2
{
    CCharFormat() { cbSize = sizeof(CHARFORMAT2); }
    BOOL operator == (CCharFormat& cf);
};

struct CParaFormat : public PARAFORMAT2
{
    CParaFormat() {cbSize = sizeof(_paraformat);}
    BOOL operator == (PARAFORMAT2& pf);
};

struct CHARHDR : public tagNMHDR
{
    CHARFORMAT2 cf;
    CHARHDR() {cf.cbSize = sizeof(CHARFORMAT2);}
};

///// Utility functions. /////

void GetMultipartResource(int nID, CArray<CString>& res);

DocType GetDocTypeFromName(LPCTSTR pszPathName, CFileException& fe);
