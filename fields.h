/*
 *  fields.h
 *  cortex_disasm
 *
 *  Created by Sergej Kravcenko on 12/1/10.
 *  Copyright 2010 Codewaves. All rights reserved.
 *
 */

#ifndef FIELDS_H
#define FIELDS_H

class CFieldSet
{
public:
   CFieldSet();
   
   void PushBit(char chField, int iValue);
   s32  GetInt(char chField);
   s64  GetLong(char chField);

   s32 operator [] (char chField) { return GetInt(chField); }

   void ProcessExpressions(const char *lpstrExpr);
   void Align4(char chField);
   void Negate(char chField);
   void Add(char chField, s64 iVal);
   
private:
   s64   m_arrValues[26];
   s64   m_arrLengths[26];
};


#endif