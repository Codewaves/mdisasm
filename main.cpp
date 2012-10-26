#include "stdafx.h"
#include "codedis.h"

void usage()
{
   printf("Cortex M0/M3 Thumb-2 disassembler. Version 0.9 Copyright (c) 2011 Sergej Kravcenko\n");
   printf("Usage: mdisasm [options] binary-file\n");
   printf(" options:\n");
   printf("  -a <addr>     Set disassemble address, default is 0x00000000\n");
   printf("  -o <offset>   Set disassemble start offset, default is 0\n");
   printf("  -s <size>     Set disassemble size in halfwords, default is maximum available\n");
   printf("  -p            Show address in [pc, imm] format in ldr instructions\n");
   printf("\n");
}

bool parse_number(char *lpstrNum, u32 &iNum)
{
   int iRes;

   _strlwr(lpstrNum);
   iRes = sscanf(lpstrNum, "0x%x", &iNum);
   if (EOF == iRes || 0 == iRes)
   {
      iRes = sscanf(lpstrNum, "%u", &iNum);
      if (EOF == iRes || 0 == iRes)
         return false;
   }

   return true;
}

int main (int argc, char * const argv[]) 
{
   // Settings
   u32 uiStartAddress   = 0;
   u32 uiOffset         = 0;
   u32 uiSize           = 0xFFFFFFFF;

   g_bShowLdrLabels = true;
   g_bShowComments  = false;
   g_bGccCompatible = true;
      
   // Parse arguments
   bool bError = false;
   int  i      = 1;
   for (i = 1; i < argc; i++)
   {
      if ('-' == argv[i][0])
      {
         switch (argv[i][1])
         {
         case 'a':
            // Stating address
            i++;
            if (argc == i)
               bError = true;
            else
               bError = !parse_number(argv[i],  uiStartAddress);
         	break;
         case 'o':
            // Start offset
            i++;
            if (argc == i)
               bError = true;
            else
               bError = !parse_number(argv[i],  uiOffset);
            break;
         case 's':
            // Disassemble size
            i++;
            if (argc == i)
               bError = true;
            else
               bError = !parse_number(argv[i],  uiSize);
            break;
         case 'p':
            g_bShowLdrLabels = false;
            break;
         default:
            bError = true;
            break;
         }
         
      }
      else
         break;
   }

   if (1 >= argc || bError || i != (argc - 1))
   {
      usage();
      return 0;
   }

   // Align
   uiStartAddress = ALIGN2(uiStartAddress);
   uiOffset       = ALIGN2(uiOffset);

   uiStartAddress += uiOffset;

   // Open file and start disassembly
   FILE *in = fopen(argv[i], "rb");
   if (in == NULL)
   {
      printf("mdisasm: Failed to open input file.\n");
      return 0;
   }

   // Seek to offset
   if (0 != fseek(in, uiOffset, SEEK_SET))
   {
      // Offset too biga nd is behind the file end, quit silently
      fclose(in);
      return 0;
   }

   // Prepare
   StartInstructionChain();

   // Disassemble
   u16   usCode;
   u16   usCode2;
   bool  bSkipFirstRead = false;

   for (u32 pos = 0; pos < uiSize;)
   {
      // Load 2 bytes from the file
      if (!bSkipFirstRead && 2 != fread(&usCode, 1, 2, in))
      {
         // End of the file, exit
         fclose(in);
         return 0;
      }
      bSkipFirstRead = false;

      // Try to load 2 more bytes
      if (2 != fread(&usCode2, 1, 2, in))
      {
         // End of file, try to decode as 16bit and exit
         DecodeInstruction(uiStartAddress + pos * 2, usCode, 0);
         fclose(in);
         return 0;
      }

      // Decode
      int iSize = DecodeInstruction(uiStartAddress + pos * 2, usCode, usCode2);
      if (1 == iSize)
      {
         // This is 16bit instruction, shft halfwords and continue
         usCode         = usCode2;
         bSkipFirstRead = true;
      }
      
      pos += iSize;
   }

   fclose(in);
   
   return 0;
}
