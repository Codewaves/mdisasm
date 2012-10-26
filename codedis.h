/*
 *  codedis.h
 *  cortex_disasm
 *
 *  Created by Sergej Kravcenko on 12/1/10.
 *  Copyright 2010 Codewaves. All rights reserved.
 *
 */

#ifndef CODEDIS_H
#define CODEDIS_H

#include "types.h"

class CFieldSet;
typedef int (*tDecodeFunc)(CFieldSet &cFieldSet, int iT);

typedef struct
{
   const char *lpstrPattern;
   const char *lpstrFormat;
   const char *lpstrExpr;
   bool        b32bit;
   const char *lpstrPattern2;
} tInstructionDef;

typedef struct  
{
   const char *lpstrName;
   const char *lpstrPattern;
   const char *lpstrPattern2;
   bool        b32bit;
   int         iT;
   tDecodeFunc lpfDecode;
} tInstructionInfo;



extern u32   g_uiCurrentAddr;
extern char  g_strInstrText[1024];
extern u8    g_bItCond;
extern u8    g_bItMask;
extern u8    g_bCurrentCond;
extern bool  g_bShowComments;
extern bool  g_bGccCompatible;
extern bool  g_bShowLdrLabels;

void  StartInstructionChain();
int   DecodeInstruction(u32 uiAddr, u16 usInstr, u16 usInstr2);
int   FindInstruction(u16 usInstr, u16 usInstr2);
void  FormatInstruction(const char *lpstrFormat, CFieldSet *lpcFieldSet, char *lpstrBuffer);

#endif