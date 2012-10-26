/*
 *  fields.cpp
 *  cortex_disasm
 *
 *  Created by Sergej Kravcenko on 12/1/10.
 *  Copyright 2010 Codewaves. All rights reserved.
 *
 */

#include "stdafx.h"
#include "fields.h"
#include "codedis.h"

CFieldSet::CFieldSet()
{
   for (int i = 0; i < 26; ++i)
   {
      m_arrValues[i]  = 0;
      m_arrLengths[i] = 0;
   }
}

void CFieldSet::PushBit(char chField, int iValue) // 65 97
{
   int   iFieldIdx = chField - 'A';
   bool  bCapital  = (iFieldIdx < 26);

   if (!bCapital)
   {
      iFieldIdx = chField - 'a';

      m_arrValues[iFieldIdx] <<= 1;
      m_arrValues[iFieldIdx]  |= iValue ? 1 : 0;
      m_arrLengths[iFieldIdx]++;
   }
   else
       m_arrValues[iFieldIdx] = iValue ? -1 : 0;
}

s32 CFieldSet::GetInt(char chField)
{
   int iFieldIdx = chField - 'a';

   return (s32)m_arrValues[iFieldIdx];
}

s64 CFieldSet::GetLong(char chField)
{
   int iFieldIdx = chField - 'a';

   return m_arrValues[iFieldIdx];
}

void CFieldSet::Align4(char chField)
{
   int iFieldIdx = chField - 'a';

   m_arrValues[iFieldIdx] &= 0xFFFFFFFFFFFFFFFCLL;
}

void CFieldSet::Negate(char chField)
{
   int iFieldIdx = chField - 'a';

   m_arrValues[iFieldIdx] = -m_arrValues[iFieldIdx];
}

void CFieldSet::Add(char chField, s64 iVal)
{
   int iFieldIdx = chField - 'a';

   m_arrValues[iFieldIdx] += iVal;
}

void CFieldSet::ProcessExpressions(const char *lpstrExpr)
{
   while (0 != *lpstrExpr)
   {
      switch (*lpstrExpr)
      {
      case 'B': // Bit concatenation B<field><length><bits>
         {
            lpstrExpr++;

            int iFieldIdx = *lpstrExpr++ - 'a';
            int iBitCount = *lpstrExpr++ - '0';

            while (iBitCount > 0)
            {
               m_arrValues[iFieldIdx] <<= 1;
               m_arrValues[iFieldIdx]  |= (*lpstrExpr++ == '1') ? 1 : 0;
               m_arrLengths[iFieldIdx]++;
               iBitCount--;
            }
         }
         break;
      case 'L': // Shift decode L<field>
         {
            lpstrExpr++;
   
            int iFieldIdx = *lpstrExpr++ - 'a';
   
            if (0 == m_arrValues[iFieldIdx])
               m_arrValues[iFieldIdx] = 32;
         }
         break;
      /*case 'M': // Immediate add or sub   M<flag_field><value_field>
         {
            lpstrExpr++;

            int iFieldIdxFlag = 0;
            
            if (*lpstrExpr != '0')
               iFieldIdxFlag = *lpstrExpr++ - 'a';
            else
               *lpstrExpr++;
            int iFieldIdx = *lpstrExpr++ - 'a';

            if (0 == m_arrValues[iFieldIdxFlag])
               m_arrValues[iFieldIdx] = -m_arrValues[iFieldIdx];
         }
         break;*/
      case 'T': // Condition override T<field>
         {
            lpstrExpr++;

            int iFieldIdx = *lpstrExpr++ - 'a';

            g_bCurrentCond = (u8)m_arrValues[iFieldIdx];
         }
         break;
      case 't': // ITSTATE processing t<cond_field><mask_field>
         {
            lpstrExpr++;

            int iFieldIdxCond = *lpstrExpr++ - 'a';
            int iFieldIdxMask = *lpstrExpr++ - 'a';

            g_bItCond = (u8)m_arrValues[iFieldIdxCond];
            g_bItMask = (u8)m_arrValues[iFieldIdxMask];
         }
         break;
      case 'U':  // Cast to unsigned U<field>
         {
            // Nothing to do, it's ok as it is
            lpstrExpr += 2;
         }
         break;
      case 'S':  // Cast to signed S<field>
      case 'E':  // Sign extend E<field>
         {
            lpstrExpr++;

            int iFieldIdx = *lpstrExpr++ - 'a';

            if (m_arrValues[iFieldIdx] & ((s64)1 << (m_arrLengths[iFieldIdx] - 1)))
            m_arrValues[iFieldIdx] = m_arrValues[iFieldIdx] - ((s64)1 << m_arrLengths[iFieldIdx]);
         }
         break;
      case 'C': // Concatenate fields C<count><result_field><field1>...<fieldN>
         {
            lpstrExpr++;

            int iCount       = *lpstrExpr++ - '0';
            int iFieldIdxRes = *lpstrExpr++ - 'a';
            s64 lResult = 0;
            s64 lLength = 0;

            for (int i = 0; i < iCount; ++i)
            {
               int iFieldIdx = *lpstrExpr++ - 'a';

               lResult <<= m_arrLengths[iFieldIdx];
               lResult  |= m_arrValues[iFieldIdx];
               lLength  += m_arrLengths[iFieldIdx];
            }
            
            m_arrValues[iFieldIdxRes] = lResult;
            m_arrLengths[iFieldIdxRes] = lLength;
         }
         break;
      case 'X': // XOR operation on single bit X<field1><field2>
         {
            lpstrExpr++;

            int iFieldIdx1 = *lpstrExpr++ - 'a';
            int iFieldIdx2 = *lpstrExpr++ - 'a';

            assert(m_arrLengths[iFieldIdx1] == 1);
            assert(m_arrLengths[iFieldIdx2] == 1);

            m_arrValues[iFieldIdx1] = m_arrValues[iFieldIdx1] ^ m_arrValues[iFieldIdx2];
         }
         break;
      case 'N': // NOT operation on single bit N<field>
         {
            lpstrExpr++;

            int iFieldIdx = *lpstrExpr++ - 'a';

             assert(m_arrLengths[iFieldIdx] == 1);
            m_arrValues[iFieldIdx] ^= 1;
         }
         break;
      case 'm': // Modified immediate constant decode
         {
            lpstrExpr++;

            int iFieldIdx = *lpstrExpr++ - 'a';

            s64 iConst  = m_arrValues[iFieldIdx] & 0xFF;
            s64 iType   = m_arrValues[iFieldIdx] >> 7;
            s64 lResult = 0;

            switch (iType)
            {
            case 0:
            case 1:
               lResult = iConst;
            	break;
            case 2:
            case 3:
               lResult = (iConst << 16) | iConst;
               break;
            case 4:
            case 5:
               lResult = (iConst << 24) | (iConst << 8);
               break;
            case 6:
            case 7:
               lResult = (iConst << 24) | (iConst << 16) | (iConst << 8) | iConst;
               break;
            default:
               {
                  s64 lShift = 32 - iType;
                  lResult = (iConst | 0x80) << lShift;
               }
               break;
            }
            
            m_arrValues[iFieldIdx] = lResult;
         }
         break;
      default:
         lpstrExpr++;
         break;
      }
   }
}