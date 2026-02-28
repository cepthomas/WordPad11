#pragma once

// Miscellaneous definitions and utilities that have no other home.

// Lonely lost items.
const int HORZ_TEXTOFFSET = 15;
const int VERT_TEXTOFFSET = 5;


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

#define FN_SETFORMAT    0x1000
#define FN_GETFORMAT    0x1001

