#include <stdafx.h>
#include "codedis.h"

u32   g_uiCurrentAddr;
char  g_strInstrText[1024];
u8    g_bItCond;
u8    g_bItMask;
u8    g_bCurrentCond;
bool  g_bShowComments;
bool  g_bGccCompatible;
bool  g_bShowLdrLabels;

u8  AdvanceIT()
{
   if (0 == g_bItMask)
      return 255;

   u8 bCond = g_bItCond;

   // Advance to next
   if (0 == (g_bItMask & 0x07))
      g_bItMask = 0, g_bItCond = 0;
   else
   {
      g_bItMask = (g_bItMask << 1) & 0x1F;
      g_bItCond = (g_bItMask & 0x10) ? (g_bItCond | 0x01) : (g_bItCond & 0xFE);
   }

   return bCond;
}

char *RunCmd(char *cmd);

extern "C"
{
   void decode_inst(long inst, char *buf);
};

int DecodeInstruction(u32 uiAddr, u16 usInstr, u16 usInstr2)
{
   g_uiCurrentAddr = uiAddr;

   // TODO: Just for testing
//   StartInstructionChain();

   // IT condition
   g_bCurrentCond = AdvanceIT();

   // Decode
   int iSize = FindInstruction(usInstr, usInstr2);
   if (1 == iSize)
      printf("  l%08x:  %04X       %s\n", uiAddr, usInstr, g_strInstrText);
   else
      printf("  l%08x:  %04X %04X  %s\n", uiAddr, usInstr, usInstr2, g_strInstrText);

   return iSize;
}

void  StartInstructionChain()
{
   // Resets IT condition state
   g_bItCond = 0;
   g_bItMask = 0;
}