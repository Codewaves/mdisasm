#include "stdafx.h"
#include "codedis.h"
#include "fields.h"

int AdcImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("adc<Fs><c>.w <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int AdcReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("adc<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("adc<Fs><c>.w <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int AddImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("add<C> <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("add<C> <t><Rd>, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   case 3:
      if (15 == cFieldSet['d'] && 0 != cFieldSet['s']) // cmn
         return 0;

      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("add<Fs><c>.w <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   case 4:
      if (15 == cFieldSet['n']) // adr
         return 0;

      FormatInstruction("addw<c> <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int AddReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("add<C> <t><Rd>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("add<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 3:
      if (15 == cFieldSet['d'] && 0 != cFieldSet['s']) // cmn
         return 0;

      FormatInstruction("add<Fs><c>.w <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int AddSpImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("add<c> <t><Rd>, sp, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("add<c> <t>sp, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   }

   return 0;
}

int AdrImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("adr<c> <t><Rd>, <li>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      cFieldSet.Negate('i');
      FormatInstruction("adr<c>.w <t><Rd>, <li>", &cFieldSet, g_strInstrText);
      return 2;
   case 3:
      FormatInstruction("adr<c>.w <t><Rd>, <li>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int AndImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['d'] && 0 != cFieldSet['s']) // tst
         return 0;

      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("and<Fs><c>.w <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int AndReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("and<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['d'] && 0 != cFieldSet['s']) // tst
         return 0;

      FormatInstruction("and<Fs><c>.w <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int AsrImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Li");
      FormatInstruction("asr<C> <t><Rd>, <Rm>, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      cFieldSet.ProcessExpressions("Li");
      FormatInstruction("asr<Fs><c>.w <t><Rd>, <Rm>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int AsrReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("asr<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("asr<Fs><c>.w <t><Rd>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Branch(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['c'] || 14 == cFieldSet['c']) // svc or undef
         return 0;
      cFieldSet.ProcessExpressions("Tc");
   case 2:
      cFieldSet.ProcessExpressions("Bi10Ei");
      FormatInstruction("b<c>.n <t><Li>", &cFieldSet, g_strInstrText);
      return 1;
   case 3:
      if (15 == cFieldSet['c'] || 14 == cFieldSet['c'])
         return 0;

      cFieldSet.ProcessExpressions("TcBi10C4iskjiEi");
      FormatInstruction("b<c>.w <t><Li>", &cFieldSet, g_strInstrText);
      return 2;
   case 4:
      cFieldSet.ProcessExpressions("XjsXksNjNkBi10C4isjkiEi");
      FormatInstruction("b<c>.w <t><Li>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int BfcBfi(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.Add('m', 1);
      cFieldSet.Add('m', -cFieldSet['i']);
      FormatInstruction("bfc<c> <t><Rd>, <Ii>, <Im>", &cFieldSet, g_strInstrText);
      return 2;
   case 2:
      if (15 == cFieldSet['n']) // bfc
         return 0;

      cFieldSet.Add('m', 1);
      cFieldSet.Add('m', -cFieldSet['i']);
      FormatInstruction("bfi<c> <t><Rd>, <Rn>, <Ii>, <Im>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int BicImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("bic<Fs><c>.w <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int BicReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("bic<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("bic<Fs><c>.w <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Bkpt(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("bkpt <t><Ii>", &cFieldSet, g_strInstrText);
      return 1;
   }

   return 0;
}

int BxReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("blx<c> <t><Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("bx<c> <t><Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 3:
      cFieldSet.ProcessExpressions("XjsXksNjNkBi10C4isjkiEi");
      FormatInstruction("blx<c> <t><Li>", &cFieldSet, g_strInstrText);  // Not in M
      return 2;
   case 4:
      cFieldSet.ProcessExpressions("XjsXksNjNkBi10C4isjkiEi");
      FormatInstruction("bl<c> <t><Li>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int CbnzCbz(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bi10");
      FormatInstruction("cb<Ho:n>z <t><Rn>, <Li>", &cFieldSet, g_strInstrText);
      return 1;
   }

   return 0;
}

int Cdp(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("cdp<Ht:2><c> <t><Dc>, <Do>, c<Yd>, c<Yn>, c<Ym>, {<Dp>}", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Clrex(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("clrex<c>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Clz(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("clz<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int CmnImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("cmn<c>.w <t><Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int CmnReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("cmn<c> <t><Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("cmn<c>.w <t><Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int CmpImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("cmp<c> <t><Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("cmp<c>.w <t><Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int CmpReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("cmp<c> <t><Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("cmp<c> <t><Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 3:
      FormatInstruction("cmp<c>.w <t><Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Cps(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("cps<Haie:id> <t><Hb:a><Hi:i><Hf:f>", &cFieldSet, g_strInstrText);
      return 1;
   }

   return 0;
}

int Dbg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("dbg<c> <t><Ih>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Dmb(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['o'])
         FormatInstruction("dmb<c> <t>sy", &cFieldSet, g_strInstrText);
      else
         FormatInstruction("dmb<c> <t><Io>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Dsb(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['o'])
         FormatInstruction("dsb<c> <t>sy", &cFieldSet, g_strInstrText);
      else
         FormatInstruction("dsb<c> <t><Io>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int EorImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['d'] && 0 != cFieldSet['s']) // teq
         return 0;

      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("eor<Fs><c>.w <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int EorReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("eor<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['d'] && 0 != cFieldSet['s']) // teq
         return 0;

      FormatInstruction("eor<Fs><c>.w <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Isb(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['o'])
         FormatInstruction("isb<c> <t>sy", &cFieldSet, g_strInstrText);
      else
         FormatInstruction("isb<c> <t><Io>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int ItHints(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (cFieldSet['m'] == 0)
      {
         // Hints
         switch (cFieldSet['c'])
         {
         case 0: // Nop
            FormatInstruction("nop<c>", &cFieldSet, g_strInstrText);
            return 1;
         case 1: // Yield
            FormatInstruction("yield<c>", &cFieldSet, g_strInstrText);
            return 1;
         case 2: // Wfe
            FormatInstruction("wfe<c>", &cFieldSet, g_strInstrText);
            return 1;
         case 3: // Wfi
            FormatInstruction("wfi<c>", &cFieldSet, g_strInstrText);
            return 1;
         case 4: // Sev
            FormatInstruction("sev<c>", &cFieldSet, g_strInstrText);
            return 1;
         default:
            {
               if (g_bGccCompatible)
               {
                  FormatInstruction("nop<c> <t>{<Dc>}", &cFieldSet, g_strInstrText);
                  return 1;
               }
               else
                  return 0;
            }
         }
      }

      cFieldSet.ProcessExpressions("Tctcm");
      FormatInstruction("it<Tmc> <t><c>", &cFieldSet, g_strInstrText);
      return 1;
   }

   return 0;
}

int Ldc(CFieldSet &cFieldSet, int iT) // TODO: check special cases in literal, add literal
{
   switch (iT)
   {
   case 1:
      if (0 == cFieldSet['p'] && 0 == cFieldSet['u'] && 0 == cFieldSet['w']) // mrrc or undef
         return 0;

      if (0 != cFieldSet['p'] || 0 != cFieldSet['w'])
         cFieldSet.ProcessExpressions("Bi200");

      if (0 == cFieldSet['p']) // Index
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("ldc<Ht:2><Hl:l><c> <t><Dc>, c<Yd>, [<Rn>], {<Di>}", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("ldc<Ht:2><Hl:l><c> <t><Dc>, c<Yd>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      }
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("ldc<Ht:2><Hl:l><c> <t><Dc>, c<Yd>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("ldc<Ht:2><Hl:l><c> <t><Dc>, c<Yd>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }

      return 2;
   }

   return 0;
}

int LdmDb(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if ((u32)cFieldSet['r'] & 0x2000) // bit 13 is not zero
         return 0;

      FormatInstruction("ldmdb<c> <t><Rn><Hw:!>, {<rr>}", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Ldmia(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if ((1 << cFieldSet['n']) & cFieldSet['r'])
         FormatInstruction("ldm<c> <t><Rn>, {<rr>}", &cFieldSet, g_strInstrText);
      else
         FormatInstruction("ldm<c> <t><Rn>!, {<rr>}", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (cFieldSet['w'] && 13 == cFieldSet['n']) // pop
         return 0;

      if ((u32)cFieldSet['r'] & 0x2000) // bit 13 is not zero
         return 0;

      FormatInstruction("ldm<c>.w <t><Rn><Hw:!>, {<rr>}", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("ldr<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("ldr<c> <t><Rt>, [sp, <Ii>]", &cFieldSet, g_strInstrText);
      return 1;
   case 3:
      if (15 == cFieldSet['n']) // ldr (literal)
         return 0;

      FormatInstruction("ldr<c>.w <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 4:
      if (15 == cFieldSet['n']) // ldr (literal)
         return 0;

      if (0 != cFieldSet['p'] && 0 != cFieldSet['u'] && 0 == cFieldSet['w']) // ldrt
         return 0;

      if (13 == cFieldSet['n'] && 0 == cFieldSet['p'] && 0 != cFieldSet['u'] && 0 != cFieldSet['w'] && 4 == cFieldSet['i']) // pop
         return 0;

      if (0 == cFieldSet['p'] && 0 == cFieldSet['w'])
         return 0;

      if (0 == cFieldSet['p']) // Index
         FormatInstruction("ldr<c>.w <t><Rt>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("ldr<c>.w <t><Rt>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("ldr<c>.w <t><Rt>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }

      return 2;
   }

   return 0;
}

int LdrLiter(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("ldr<c> <t><Rt>, <A11i>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("ldr<c>.w <t><Rt>, <A1ui>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("ldr<c> <t><Rt>, [<Rn>, <Rm>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n']) // ldr (literal)
         return 0;

      FormatInstruction("ldr<c>.w <t><Rt>, [<Rn>, <Rm><Sai>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrbImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("ldrb<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n'] || 15 == cFieldSet['t']) // ldrb (literal) or pld
         return 0;

      FormatInstruction("ldrb<c>.w <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 3:
      if (0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 != cFieldSet['u']) // ldrbt
         return 0;

      if ((0 == cFieldSet['p'] && 0 == cFieldSet['w']) || 15 == cFieldSet['n']) // ldrb (literal) or undefined
         return 0;

      if (15 == cFieldSet['t'] && 0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 == cFieldSet['u']) // pld
         return 0;

      if (0 == cFieldSet['p']) // Index
         FormatInstruction("ldrb<c>.w <t><Rt>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("ldrb<c>.w <t><Rt>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("ldrb<c>.w <t><Rt>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }

      return 2;
   }

   return 0;
}

int LdrbLiter(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['t'])
         return 0;

      FormatInstruction("ldrb<c>.w <t><Rt>, <A1ui>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrbReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("ldrb<c> <t><Rt>, [<Rn>, <Rm>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n'] || 15 == cFieldSet['t']) // ldrb (literal) or pld
         return 0;

      FormatInstruction("ldrb<c>.w <t><Rt>, [<Rn>, <Rm><Sai>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Ldrbt(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // ldrb (literal)
         return 0;

      FormatInstruction("ldrbt<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrdImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (0 == cFieldSet['p'] && 0 == cFieldSet['w']) // related
         return 0;

      if (15 == cFieldSet['n']) // ldrd (literal)
         return 0;

      cFieldSet.ProcessExpressions("Bi200");

      if (0 == cFieldSet['p']) // Index
         FormatInstruction("ldrd<c> <t><Rt>, <Rd>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("ldrd<c> <t><Rt>, <Rd>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("ldrd<c> <t><Rt>, <Rd>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }
      return 2;
   }

   return 0;
}

int LdrdLiter(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (0 == cFieldSet['p'] && 0 == cFieldSet['w']) // related
         return 0;

      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("ldrd<c> <t><Rt>, <Rd>, <A0ui>", &cFieldSet, g_strInstrText); // pc not aligned to 4
      return 2;
   }

   return 0;
}

int Ldrex(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("ldrex<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 2: // ldrexb
      FormatInstruction("ldrexb<c> <t><Rt>, [<Rn>]", &cFieldSet, g_strInstrText);
      return 2;
   case 3: // ldrexd Not in M
      FormatInstruction("ldrexd<c> <t><Rt>, <Rm>, [<Rn>]", &cFieldSet, g_strInstrText);
      return 2;
   case 4: // ldrexh
      FormatInstruction("ldrexh<c> <t><Rt>, [<Rn>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrhImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bi10");
      FormatInstruction("ldrh<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n'] || 15 == cFieldSet['t']) // ldrh (literal) or hints
         return 0;

      FormatInstruction("ldrh<c>.w <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 3:
      if (0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 != cFieldSet['u']) // ldrht
         return 0;

      if ((0 == cFieldSet['p'] && 0 == cFieldSet['w']) || 15 == cFieldSet['n']) // ldrh (literal) or undefined
         return 0;

      if (15 == cFieldSet['t'] && 0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 == cFieldSet['u']) // hints
         return 0;

      if (0 == cFieldSet['p']) // Index
         FormatInstruction("ldrh<c>.w <t><Rt>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("ldrh<c>.w <t><Rt>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("ldrh<c>.w <t><Rt>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }

      return 2;
   }

   return 0;
}

int LdrhLiter(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['t']) // hints
         return 0;

      FormatInstruction("ldrh<c>.w <t><Rt>, <A1ui>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrhReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("ldrh<c> <t><Rt>, [<Rn>, <Rm>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n'] || 15 == cFieldSet['t']) // ldrh (literal) or hints
         return 0;

      FormatInstruction("ldrh<c>.w <t><Rt>, [<Rn>, <Rm><Sai>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Ldrht(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // ldrh (literal)
         return 0;

      FormatInstruction("ldrht<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrsbImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n'] || 15 == cFieldSet['t']) // ldrsb (literal) or plt
         return 0;

      FormatInstruction("ldrsb<c>.w <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 2:
      if (0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 != cFieldSet['u']) // ldrsbt
         return 0;

      if ((0 == cFieldSet['p'] && 0 == cFieldSet['w']) || 15 == cFieldSet['n']) // ldrsb (literal) or undefined
         return 0;

      if (15 == cFieldSet['t'] && 0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 == cFieldSet['u']) // pli
         return 0;

      if (0 == cFieldSet['p']) // Index
         FormatInstruction("ldrsb<c>.w <t><Rt>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("ldrsb<c>.w <t><Rt>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("ldrsb<c>.w <t><Rt>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }

      return 2;
   }

   return 0;
}

int LdrsbLiter(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['t']) // pli
         return 0;

      FormatInstruction("ldrsb<c>.w <t><Rt>, <A1ui>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrsbReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("ldrsb<c> <t><Rt>, [<Rn>, <Rm>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n'] || 15 == cFieldSet['t']) // ldrsb (literal) or pli
         return 0;

      FormatInstruction("ldrsb<c>.w <t><Rt>, [<Rn>, <Rm><Sai>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Ldrsbt(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // ldrsb (literal)
         return 0;

      FormatInstruction("ldrsbt<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrshImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n'] || 15 == cFieldSet['t']) // ldrsh (literal) or hints
         return 0;

      FormatInstruction("ldrsh<c>.w <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 2:
      if (0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 != cFieldSet['u']) // ldrsht
         return 0;

      if ((0 == cFieldSet['p'] && 0 == cFieldSet['w']) || 15 == cFieldSet['n']) // ldrsh (literal) or undefined
         return 0;

      if (15 == cFieldSet['t'] && 0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 == cFieldSet['u']) // hints
         return 0;

      if (0 == cFieldSet['p']) // Index
         FormatInstruction("ldrsh<c>.w <t><Rt>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("ldrsh<c>.w <t><Rt>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("ldrsh<c>.w <t><Rt>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }

      return 2;
   }

   return 0;
}

int LdrshLiter(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['t']) // hints
         return 0;

      FormatInstruction("ldrsh<c>.w <t><Rt>, <A1ui>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LdrshReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("ldrsh<c> <t><Rt>, [<Rn>, <Rm>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n'] || 15 == cFieldSet['t']) // ldrsh (literal) or hints
         return 0;

      FormatInstruction("ldrsh<c>.w <t><Rt>, [<Rn>, <Rm><Sai>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Ldrsht(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // ldrsh (literal)
         return 0;

      FormatInstruction("ldrsht<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Ldrt(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // ldr (literal)
         return 0;

      FormatInstruction("ldrt<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LslImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("lsl<C> <t><Rd>, <Rm>, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (cFieldSet['i'] == 0) // mov
         return 0;

      FormatInstruction("lsl<Hs:s><c>.w <t><Rd>, <Rm>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LslReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("lsl<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("lsl<Fs><c>.w <t><Rd>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LsrImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Li");
      FormatInstruction("lsr<C> <t><Rd>, <Rm>, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      cFieldSet.ProcessExpressions("Li");
      FormatInstruction("lsr<Hs:s><c>.w <t><Rd>, <Rm>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int LsrReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("lsr<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("lsr<Fs><c>.w <t><Rd>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Mcr(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("mcr<Hl:2><c> <t><Dc>, <Do>, <Rt>, c<Yn>, c<Ym>, {<Dp>}", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Mcrr(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("mcrr<Hl:2><c> <t><Dc>, <Do>, <Rt>, <Ru>, c<Ym>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int MlaMls(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['a']) // mul
         return 0;
      FormatInstruction("mla<c> <t><Rd>, <Rn>, <Rm>, <Ra>", &cFieldSet, g_strInstrText);
      return 2;
   case 2:
      FormatInstruction("mls<c> <t><Rd>, <Rn>, <Rm>, <Ra>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int MovImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("mov<C> <t><Rd>, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("mov<Fs><c>.w <t><Rd>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   case 3:
      cFieldSet.ProcessExpressions("C2iki");
      FormatInstruction("movw<c> <t><Rd>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int MovReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("mov<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 3:
      FormatInstruction("mov<Fs><c>.w <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int MovT(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("C2iki");
      FormatInstruction("movt<c> <t><Rd>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Mrc(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("mrc<Hl:2><c> <t><Dc>, <Do>, <Rt>, c<Yn>, c<Ym>, {<Dp>}", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Mrrc(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("mrrc<Hl:2><c> <t><Dc>, <Do>, <Rt>, <Ru>, c<Ym>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Mrs(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("mrs<c> <t><Rd>, <zs>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Msr(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("msr<c> <t><ysm>, <Rn>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int MulReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("mul<C> <t><Rn>, <Rm>, <Rn>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("mul<c>.w <t><Rd>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int MvnImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("mvn<Fs><c>.w <t><Rd>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int MvnReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("mvn<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("mvn<Fs><c>.w <t><Rd>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Nop(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      // Hints
      switch (cFieldSet['h'])
      {
      case 0: // Nop
         FormatInstruction("nop<c>.w", &cFieldSet, g_strInstrText);
         return 2;
      case 1: // Yield
         FormatInstruction("yield<c>.w", &cFieldSet, g_strInstrText);
         return 2;
      case 2: // Wfe
         FormatInstruction("wfe<c>.w", &cFieldSet, g_strInstrText);
         return 2;
      case 3: // Wfi
         FormatInstruction("wfi<c>.w", &cFieldSet, g_strInstrText);
         return 2;
      case 4: // Sev
         FormatInstruction("sev<c>.w", &cFieldSet, g_strInstrText);
         return 2;
      default:
         {
            if (g_bGccCompatible && (0xF0 & cFieldSet['h']) != 0xF0)
            {
               FormatInstruction("nop<c>.w <t>{<Dh>}", &cFieldSet, g_strInstrText);
               return 2;
            }
            else
               return 0;
         }
      }

      return 0;
   }

   return 0;
}

int OrnImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // mvn
         return 0;

      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("orn<Fs><c> <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int OrnReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // mvn
         return 0;

      FormatInstruction("orn<Fs><c> <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int OrrImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // mov
         return 0;

      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("orr<Fs><c>.w <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int OrrReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("orr<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n']) // mov
         return 0;

      FormatInstruction("orr<Fs><c>.w <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Pkhtb(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bt10");
      FormatInstruction("pkh<Htbt:tb><Fs><c> <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int PldImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // pld (literal)
         return 0;

      FormatInstruction("pld<c> <t>[<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 2:
      if (15 == cFieldSet['n']) // pld (literal)
         return 0;

      FormatInstruction("pld<c> <t>[<Rn>, <iai>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int PldLiter(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("pld<c> <t><A1ui>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int PldReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // pld (literal)
         return 0;

      FormatInstruction("pld<c> <t>[<Rn>, <Rm><Sts>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int PliImm(CFieldSet &cFieldSet, int iT) // TODO: addr or [pc, imm]
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // pli (literal)
         return 0;

      FormatInstruction("pli<c> <t>[<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 2:
      if (15 == cFieldSet['n']) // pli (literal)
         return 0;

      FormatInstruction("pli<c> <t>[<Rn>, <iai>]", &cFieldSet, g_strInstrText);
      return 2;
   case 3:
      FormatInstruction("pli<c> <t><A1ui>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int PliReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // pli (literal)
         return 0;

      FormatInstruction("pli<c> <t>[<Rn>, <Rm><Sts>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Pop(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bp70000000C2rpr");
      FormatInstruction("pop<c> <t>{<rr>}", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if ((u32)cFieldSet['r'] & 0x2000) // bit 13 is not zero
         return 0;
      FormatInstruction("pop<c>.w <t>{<rr>}", &cFieldSet, g_strInstrText);
      return 2;
   case 3:
      FormatInstruction("pop<c>.w <t>{<Rt>}", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Push(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bm6000000C2rmr");
      FormatInstruction("push<c> <t>{<rr>}", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if ((u32)cFieldSet['r'] & 0xA000)
         return 0;
      FormatInstruction("push<c>.w <t>{<rr>}", &cFieldSet, g_strInstrText);
      return 2;
   case 3:
      FormatInstruction("push<c>.w <t>{<Rt>}", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Rbit(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("rbit<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Rev(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("rev<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("rev<c>.w <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Rev16(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("rev16<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("rev16<c>.w <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int RevSh(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("revsh<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("revsh<c>.w <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int RorImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (cFieldSet['i'] == 0) // rrx
         return 0;

      FormatInstruction("ror<Fs><c>.w <t><Rd>, <Rm>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int RorReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("ror<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("ror<Fs><c>.w <t><Rd>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Rrx(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("rrx<Fs><c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int RsbImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("rsb<C> <t><Rd>, <Rn>, #0", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("rsb<Fs><c>.w <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int RsbReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("rsb<Fs><c> <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int SbcImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("sbc<Fs><c>.w <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int SbcReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("sbc<C> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("sbc<Fs><c>.w <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Sbfx(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.Add('w', 1);
      FormatInstruction("sbfx<c> <t><Rd>, <Rn>, <Ii>, <Iw>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Sdiv(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("sdiv<c> <t><Rd>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Sel(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("sel<c> <t><Rd>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int SetEnd(CFieldSet &cFieldSet, int iT) // Not in M
{
   switch (iT)
   {
   case 1:
      FormatInstruction("setend <t><Hale:be>", &cFieldSet, g_strInstrText);
      return 1;
   }

   return 0;
}

int Smlal(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("smlal<c> <t><Rl>, <Rh>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Smull(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("smull<c> <t><Rl>, <Rh>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Ssat(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (0 != cFieldSet['s'] && 0 == cFieldSet['i']) // ssat16 or undef
         return 0;

      cFieldSet.ProcessExpressions("Bs10");
      FormatInstruction("ssat<c> <t><Rd>, <Ik>, <Rn><Ssi>", &cFieldSet, g_strInstrText);
      return 2;
   case 2:
      FormatInstruction("ssat16<c> <t><Rd>, <Ik>, <Rn>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Stc(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (0 == cFieldSet['p'] && 0 == cFieldSet['u'] && 0 == cFieldSet['w']) // mcrr or undef
         return 0;

      if (0 != cFieldSet['p'] || 0 != cFieldSet['w'])
         cFieldSet.ProcessExpressions("Bi200");
      
      if (0 == cFieldSet['p']) // Index
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("stc<Ht:2><Hl:l><c> <t><Dc>, c<Yd>, [<Rn>], {<Di>}", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("stc<Ht:2><Hl:l><c> <t><Dc>, c<Yd>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      }
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("stc<Ht:2><Hl:l><c> <t><Dc>, c<Yd>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("stc<Ht:2><Hl:l><c> <t><Dc>, c<Yd>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }
      return 2;
   }

   return 0;
}

int Stmia(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("stm<c> <Rn>!, {<rr>}", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if ((u32)cFieldSet['r'] & 0xA000) // bits 15 and 13 are not zero
         return 0;
      FormatInstruction("stm<c>.w <t><Rn><Hw:!>, {<rr>}", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int StmDb(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (((u32)cFieldSet['r'] & 0xA000) || (cFieldSet['n'] == 13 && cFieldSet['w'] != 0)) // push or bits 15 and 13 are not zero
         return 0;
      FormatInstruction("stmdb<c> <t><Rn><Hw:!>, {<rr>}", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int StrImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("str<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("str<c> <t><Rt>, [sp, <Ii>]", &cFieldSet, g_strInstrText);
      return 1;
   case 3:
      if (15 == cFieldSet['n']) // undef
         return 0;

      FormatInstruction("str<c>.w <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 4:
      if (0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 != cFieldSet['u']) // strt
         return 0;

      if ((0 == cFieldSet['p'] && 0 == cFieldSet['w']) || 15 == cFieldSet['n']) // undef
         return 0;

      if (13 == cFieldSet['n'] && 0 != cFieldSet['p'] && 0 == cFieldSet['u'] && 0 != cFieldSet['w'] && 4 == cFieldSet['i']) // push
         return 0;

      if (0 == cFieldSet['p']) // Index
         FormatInstruction("str<c>.w <t><Rt>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("str<c>.w <t><Rt>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("str<c>.w <t><Rt>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }

      return 2;
   }

   return 0;
}

int StrReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("str<c> <t><Rt>, [<Rn>, <Rm>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n'])
         return 0;

      FormatInstruction("str<c>.w <t><Rt>, [<Rn>, <Rm><Sai>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int StrbImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("strb<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n']) // undef
         return 0;

      FormatInstruction("strb<c>.w <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 3:
      if (0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 != cFieldSet['u']) // strbt
         return 0;

      if ((0 == cFieldSet['p'] && 0 == cFieldSet['w']) || 15 == cFieldSet['n']) // undef
         return 0;

      if (0 == cFieldSet['p']) // Index
         FormatInstruction("strb<c>.w <t><Rt>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("strb<c>.w <t><Rt>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("strb<c>.w <t><Rt>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }

      return 2;
   }

   return 0;
}

int StrbReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("strb<c> <t><Rt>, [<Rn>, <Rm>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n'])
         return 0;

      FormatInstruction("strb<c>.w <t><Rt>, [<Rn>, <Rm><Sai>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Strbt(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // undef
         return 0;
         
      FormatInstruction("strbt<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);   
      return 2;
   }

   return 0;
}

int StrdImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (0 == cFieldSet['p'] && 0 == cFieldSet['w']) // related
         return 0;

      cFieldSet.ProcessExpressions("Bi200");

      if (0 == cFieldSet['p']) // Index
         FormatInstruction("strd<c> <t><Rt>, <Rd>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("strd<c> <t><Rt>, <Rd>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("strd<c> <t><Rt>, <Rd>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }
      return 2;
   }

   return 0;
}

int Strex(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1: // strex
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("strex<c> <t><Rd>, <Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 2: // strexb
      FormatInstruction("strexb<c> <t><Rd>, <Rt>, [<Rn>]", &cFieldSet, g_strInstrText);
      return 2;
   case 3: // strexd Not in M
      FormatInstruction("strexd<c> <t><Rd>, <Rt>, <Rm>, [<Rn>]", &cFieldSet, g_strInstrText);
      return 2;
   case 4: // strexh
      FormatInstruction("strexh<c> <t><Rd>, <Rt>, [<Rn>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int StrhImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bi10");
      FormatInstruction("strh<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n']) // undef
         return 0;

      FormatInstruction("strh<c>.w <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);
      return 2;
   case 3:
      if (0 != cFieldSet['p'] && 0 == cFieldSet['w'] && 0 != cFieldSet['u']) // strht
         return 0;

      if ((0 == cFieldSet['p'] && 0 == cFieldSet['w']) || 15 == cFieldSet['n']) // undef
         return 0;

      if (0 == cFieldSet['p']) // Index
         FormatInstruction("strh<c>.w <t><Rt>, [<Rn>], <iui>", &cFieldSet, g_strInstrText);
      else
      {
         if (0 == cFieldSet['w']) // Write back
            FormatInstruction("strh<c>.w <t><Rt>, [<Rn>, <iui>]", &cFieldSet, g_strInstrText);
         else
            FormatInstruction("strh<c>.w <t><Rt>, [<Rn>, <iui>]!", &cFieldSet, g_strInstrText);
      }

      return 2;
   }

   return 0;
}

int StrhReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("strh<c> <t><Rt>, [<Rn>, <Rm>]", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['n'])
         return 0;

      FormatInstruction("strb<c>.w <t><Rt>, [<Rn>, <Rm><Sai>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Strht(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // undef
         return 0;

      FormatInstruction("strht<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);   
      return 2;
   }

   return 0;
}

int Strt(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (15 == cFieldSet['n']) // undef
         return 0;

      FormatInstruction("strt<c> <t><Rt>, [<Rn>, <Ii>]", &cFieldSet, g_strInstrText);   
      return 2;
   }

   return 0;
}

int SubImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("sub<C> <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("sub<C> <t><Rd>, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   case 3:
      if (15 == cFieldSet['d'] && 0 != cFieldSet['s']) // cmp
         return 0;

      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("sub<Fs><c>.w <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   case 4:
      if (15 == cFieldSet['n']) // adr
         return 0;

      FormatInstruction("subw<c> <t><Rd>, <Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int SubReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("sub<C> <t><Rd>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      if (15 == cFieldSet['d'] && 0 != cFieldSet['s']) // cmp
         return 0;

      FormatInstruction("sub<Fs><c>.w <t><Rd>, <Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int SubSpImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("Bi200");
      FormatInstruction("sub<c> <t>sp, <Ii>", &cFieldSet, g_strInstrText);
      return 1;
   }

   return 0;
}

int Svc(CFieldSet &cFieldSet, int iT) // TODO: check syntax
{
   switch (iT)
   {
   case 1:
      FormatInstruction("svc<c> <t><Di>", &cFieldSet, g_strInstrText);
      return 1;
   }

   return 0;
}

int Sxtb(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("sxtb<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("sxtb<c>.w <t><Rd>, <Rm><Xr>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Sxth(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("sxth<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("sxth<c>.w <t><Rd>, <Rm><Xr>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int TbbTbh(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("tb<Hhb:h><c> <t>[<Rn>, <Rm><Hh:, lsl #1>]", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int TeqImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("teq<c> <t><Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int TeqReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("teq<c> <t><Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int TstImm(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.ProcessExpressions("mi");
      FormatInstruction("tst<c>.w <t><Rn>, <Ii>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int TstReg(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("tst<c> <t><Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("tst<c>.w <t><Rn>, <Rm><Sti>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Ubfx(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      cFieldSet.Add('w', 1);
      FormatInstruction("ubfx<c> <t><Rd>, <Rn>, <Ii>, <Iw>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Udiv(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("udiv<c> <t><Rd>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Umlal(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("umlal<c> <t><Rl>, <Rh>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Umull(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("umull<c> <t><Rl>, <Rh>, <Rn>, <Rm>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Usat(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      if (0 != cFieldSet['s'] && 0 == cFieldSet['i']) // usat16 or undef
         return 0;

      cFieldSet.ProcessExpressions("Bs10");
      FormatInstruction("usat<c> <t><Rd>, <Ik>, <Rn><Ssi>", &cFieldSet, g_strInstrText);
      return 2;
   case 2:
      FormatInstruction("usat16<c> <t><Rd>, <Ik>, <Rn>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Uxtb(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("uxtb<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("uxtb<c>.w <t><Rd>, <Rm><Xr>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int Uxth(CFieldSet &cFieldSet, int iT)
{
   switch (iT)
   {
   case 1:
      FormatInstruction("uxth<c> <t><Rd>, <Rm>", &cFieldSet, g_strInstrText);
      return 1;
   case 2:
      FormatInstruction("uxth<c>.w <t><Rd>, <Rm><Xr>", &cFieldSet, g_strInstrText);
      return 2;
   }

   return 0;
}

int UndefinedOp(CFieldSet &cFieldSet, int iT)
{
   if (g_bGccCompatible)
   {
      if ((u32)cFieldSet['a'] >= 0xE800)
      {
         FormatInstruction("undefined instruction ", &cFieldSet, g_strInstrText);
         sprintf(strchr(g_strInstrText, 0), "0x%04x%04x", cFieldSet['a'], cFieldSet['b']);
          return 2;
      }
      else
         FormatInstruction("undefined instruction <da>", &cFieldSet, g_strInstrText);
   }
   else
      FormatInstruction("undefined instruction", &cFieldSet, g_strInstrText);
   return 1;
}

tInstructionInfo g_arrInstructionInfo[] = 
{
   { "adc (immediate)",        "11110i01010snnnn", "0iiiddddiiiiiiii", true,  1, AdcImm },
   { "adc (register)",         "0100000101mmmddd", "xxxxxxxxxxxxxxxx", false, 1, AdcReg },
   { "adc (register)",         "11101011010snnnn", "0iiiddddiittmmmm", true,  2, AdcReg },

   { "add (immediate)",        "0001110iiinnnddd", "xxxxxxxxxxxxxxxx", false, 1, AddImm },
   { "add (immediate)",        "00110dddiiiiiiii", "xxxxxxxxxxxxxxxx", false, 2, AddImm },
   { "add (immediate)",        "11110i01000snnnn", "0iiiddddiiiiiiii", true,  3, AddImm },
   { "addw (immediate)",       "11110i100000nnnn", "0iiiddddiiiiiiii", true,  4, AddImm },
   { "add (register)",         "0001100mmmnnnddd", "xxxxxxxxxxxxxxxx", false, 1, AddReg },
   { "add (register)",         "01000100dmmmmddd", "xxxxxxxxxxxxxxxx", false, 2, AddReg },
   { "add (register)",         "11101011000snnnn", "0iiiddddiittmmmm", true,  3, AddReg },
   { "add (sp immediate)",     "10101dddiiiiiiii", "xxxxxxxxxxxxxxxx", false, 1, AddSpImm },
   { "add (sp immediate)",     "101100000iiiiiii", "xxxxxxxxxxxxxxxx", false, 2, AddSpImm },

   { "adr",                    "10100dddiiiiiiii", "xxxxxxxxxxxxxxxx", false, 1, AdrImm },
   { "adr",                    "11110i1010101111", "0iiiddddiiiiiiii", true,  2, AdrImm },
   { "adr",                    "11110i1000001111", "0iiiddddiiiiiiii", true,  3, AdrImm },

   { "and (immediate)",        "11110i00000snnnn", "0iiiddddiiiiiiii", true,  1, AndImm },
   { "and (register)",         "0100000000mmmddd", "xxxxxxxxxxxxxxxx", false, 1, AndReg },
   { "and (register)",         "11101010000snnnn", "0iiiddddiittmmmm", true,  2, AndReg },

   { "asr (immediate)",        "00010iiiiimmmddd", "xxxxxxxxxxxxxxxx", false, 1, AsrImm },
   { "asr (immediate)",        "11101010010s1111", "0iiiddddii10mmmm", true,  2, AsrImm },
   { "asr (register)",         "0100000100mmmddd", "xxxxxxxxxxxxxxxx", false, 1, AsrReg },
   { "asr (register)",         "11111010010snnnn", "1111dddd0000mmmm", true,  2, AsrReg },

   { "b",                      "1101cccciiiiiiii", "xxxxxxxxxxxxxxxx", false, 1, Branch },
   { "b",                      "11100iiiiiiiiiii", "xxxxxxxxxxxxxxxx", false, 2, Branch },
   { "b",                      "11110scccciiiiii", "10j0kiiiiiiiiiii", true,  3, Branch },
   { "b",                      "11110siiiiiiiiii", "10j1kiiiiiiiiiii", true,  4, Branch },

   { "bfc",                    "1111001101101111", "0iiiddddii0mmmmm", true,  1, BfcBfi },
   { "bfi",                    "111100110110nnnn", "0iiiddddii0mmmmm", true,  2, BfcBfi },

   { "bic (immediate)",        "11110i00001snnnn", "0iiiddddiiiiiiii", true,  1, BicImm },
   { "bic (register)",         "0100001110mmmddd", "xxxxxxxxxxxxxxxx", false, 1, BicReg },
   { "bic (register)",         "11101010001snnnn", "0iiiddddiittmmmm", true,  2, BicReg },

   { "bkpt",                   "10111110iiiiiiii", "xxxxxxxxxxxxxxxx", false, 1, Bkpt },

   { "blx",                    "010001111mmmm000", "xxxxxxxxxxxxxxxx", false, 1, BxReg },
   { "bx",                     "010001110mmmmooo", "xxxxxxxxxxxxxxxx", false, 2, BxReg },
   { "bl",                     "11110siiiiiiiiii", "11j1kiiiiiiiiiii", true,  4, BxReg },

   { "cbnz, cbz",              "1011o0i1iiiiinnn", "xxxxxxxxxxxxxxxx", false, 1, CbnzCbz },

   { "cdp, cdp2",              "111t1110oooonnnn", "ddddccccppp0mmmm", true,  1, Cdp },

   { "clrex",                  "1111001110111111", "1000111100101111", true,  1, Clrex },

   { "clz",                    "111110101011mmmm", "1111dddd1000xxxx", true,  1, Clz },

   { "cmn (immediate)",        "11110i010001nnnn", "0iii1111iiiiiiii", true,  1, CmnImm },
   { "cmn (register)",         "0100001011mmmnnn", "xxxxxxxxxxxxxxxx", false, 1, CmnReg },
   { "cmn (register)",         "111010110001nnnn", "0iii1111iittmmmm", true,  2, CmnReg },

   { "cmp (immediate)",        "00101nnniiiiiiii", "xxxxxxxxxxxxxxxx", false, 1, CmpImm },
   { "cmp (immediate)",        "11110i011011nnnn", "0iii1111iiiiiiii", true,  2, CmpImm },
   { "cmp (register)",         "0100001010mmmnnn", "xxxxxxxxxxxxxxxx", false, 1, CmpReg },
   { "cmp (register)",         "01000101nmmmmnnn", "xxxxxxxxxxxxxxxx", false, 2, CmpReg },
   { "cmp (register)",         "111010111011nnnn", "0iii1111iittmmmm", true,  3, CmpReg },

   { "cps",                    "10110110011a0bif", "xxxxxxxxxxxxxxxx", false, 1, Cps },            // 'a' flag not in M

   { "dbg",                    "1111001110101111", "100000001111hhhh", true,  1, Dbg },

   { "dmb",                    "1111001110111111", "100011110101oooo", true,  1, Dmb },

   { "dsb",                    "1111001110111111", "100011110100oooo", true,  1, Dsb },

   { "eor (immediate)",        "11110i00100snnnn", "0iiiddddiiiiiiii", true,  1, EorImm },
   { "eor (register)",         "0100000001mmmddd", "xxxxxxxxxxxxxxxx", false, 1, EorReg },
   { "eor (register)",         "11101010100snnnn", "0iiiddddiittmmmm", true,  2, EorReg },

   { "isb",                    "1111001110111111", "100011110110oooo", true,  1, Isb },

   { "it and hints",           "10111111ccccmmmm", "xxxxxxxxxxxxxxxx", false, 1, ItHints },

   { "ldc, ldc2",              "111t110pulw1nnnn", "ddddcccciiiiiiii", true,  1, Ldc },

   { "ldm",                    "11001nnnrrrrrrrr", "xxxxxxxxxxxxxxxx", false, 1, Ldmia },
   { "ldm",                    "1110100010w1nnnn", "rrrrrrrrrrrrrrrr", true,  2, Ldmia },

   { "ldmdb, ldmea",           "1110100100w1nnnn", "rrrrrrrrrrrrrrrr", true,  1, LdmDb },

   { "ldr (immediate)",        "01101iiiiinnnttt", "xxxxxxxxxxxxxxxx", false, 1, LdrImm },
   { "ldr (immediate)",        "10011tttiiiiiiii", "xxxxxxxxxxxxxxxx", false, 2, LdrImm },
   { "ldr (immediate)",        "111110001101nnnn", "ttttiiiiiiiiiiii", true,  3, LdrImm },
   { "ldr (immediate)",        "111110000101nnnn", "tttt1puwiiiiiiii", true,  4, LdrImm },
   { "ldr (literal)",          "01001tttiiiiiiii", "xxxxxxxxxxxxxxxx", false, 1, LdrLiter },
   { "ldr (literal)",          "11111000u1011111", "ttttiiiiiiiiiiii", true,  2, LdrLiter },
   { "ldr (register)",         "0101100mmmnnnttt", "xxxxxxxxxxxxxxxx", false, 1, LdrReg },
   { "ldr (register)",         "111110000101nnnn", "tttt000000iimmmm", true,  2, LdrReg },

   { "ldrb (immediate)",       "01111iiiiinnnttt", "xxxxxxxxxxxxxxxx", false, 1, LdrbImm },
   { "ldrb (immediate)",       "111110001001nnnn", "ttttiiiiiiiiiiii", true,  2, LdrbImm },
   { "ldrb (immediate)",       "111110000001nnnn", "tttt1puwiiiiiiii", true,  3, LdrbImm },
   { "ldrb (literal)",         "11111000u0011111", "ttttiiiiiiiiiiii", true,  1, LdrbLiter },
   { "ldrb (register)",        "0101110mmmnnnttt", "xxxxxxxxxxxxxxxx", false, 1, LdrbReg },
   { "ldrb (register)",        "111110000001nnnn", "tttt000000iimmmm", true,  2, LdrbReg },
   { "ldrbt",                  "111110000001nnnn", "tttt1110iiiiiiii", true,  1, Ldrbt },

   { "ldrex",                  "111010000101nnnn", "tttt1111iiiiiiii", true,  1, Ldrex },
   { "ldrexb",                 "111010001101nnnn", "tttt111101001111", true,  2, Ldrex },
   { "ldrexh",                 "111010001101nnnn", "tttt111101011111", true,  4, Ldrex },
   { "ldrd (immediate)",       "1110100pu1w1nnnn", "ttttddddiiiiiiii", true,  1, LdrdImm },
   { "ldrd (literal)",         "1110100pu1w11111", "ttttddddiiiiiiii", true,  1, LdrdLiter },

   { "ldrh (immediate)",       "10001iiiiinnnttt", "xxxxxxxxxxxxxxxx", false, 1, LdrhImm },
   { "ldrh (immediate)",       "111110001011nnnn", "ttttiiiiiiiiiiii", true,  2, LdrhImm },
   { "ldrh (immediate)",       "111110000011nnnn", "tttt1puwiiiiiiii", true,  3, LdrhImm },
   { "ldrh (literal)",         "11111000u0111111", "ttttiiiiiiiiiiii", true,  1, LdrhLiter },
   { "ldrh (register)",        "0101101mmmnnnttt", "xxxxxxxxxxxxxxxx", false, 1, LdrhReg },
   { "ldrh (register)",        "111110000011nnnn", "tttt000000iimmmm", true,  2, LdrhReg },
   { "ldrht",                  "111110000011nnnn", "tttt1110iiiiiiii", true,  1, Ldrht },
   
   { "ldrsb (immediate)",      "111110011001nnnn", "ttttiiiiiiiiiiii", true,  1, LdrsbImm },
   { "ldrsb (immediate)",      "111110010001nnnn", "tttt1puwiiiiiiii", true,  2, LdrsbImm },
   { "ldrsb (literal)",        "11111001u0011111", "ttttiiiiiiiiiiii", true,  1, LdrsbLiter },
   { "ldrsb (register)",       "0101011mmmnnnttt", "xxxxxxxxxxxxxxxx", false, 1, LdrsbReg },
   { "ldrsb (register)",       "111110010001nnnn", "tttt000000iimmmm", true,  2, LdrsbReg },
   { "ldrsbt",                 "111110010001nnnn", "tttt1110iiiiiiii", true,  1, Ldrsbt },

   { "ldrsh (immediate)",      "111110011011nnnn", "ttttiiiiiiiiiiii", true,  1, LdrshImm },
   { "ldrsh (immediate)",      "111110010011nnnn", "tttt1puwiiiiiiii", true,  2, LdrshImm },
   { "ldrsh (literal)",        "11111001u0111111", "ttttiiiiiiiiiiii", true,  1, LdrshLiter },
   { "ldrsh (register)",       "0101111mmmnnnttt", "xxxxxxxxxxxxxxxx", false, 1, LdrshReg },
   { "ldrsh (register)",       "111110010011nnnn", "tttt000000iimmmm", true,  2, LdrshReg },
   { "ldrsht",                 "111110010011nnnn", "tttt1110iiiiiiii", true,  1, Ldrsht },

   { "ldrt",                   "111110000101nnnn", "tttt1110iiiiiiii", true,  1, Ldrt },

   { "lsl (immediate)",        "00000iiiiimmmddd", "xxxxxxxxxxxxxxxx", false, 1, LslImm },
   { "lsl (immediate)",        "11101010010s1111", "0iiiddddii00mmmm", true,  2, LslImm },
   { "lsl (register)",         "0100000010mmmddd", "xxxxxxxxxxxxxxxx", false, 1, LslReg },
   { "lsl (register)",         "11111010000snnnn", "1111dddd0000mmmm", true,  2, LslReg },

   { "lsr (immediate)",        "00001iiiiimmmddd", "xxxxxxxxxxxxxxxx", false, 1, LsrImm },
   { "lsr (immediate)",        "11101010010s1111", "0iiiddddii01mmmm", true,  2, LsrImm },
   { "lsr (register)",         "0100000011mmmddd", "xxxxxxxxxxxxxxxx", false, 1, LsrReg },
   { "lsr (register)",         "11111010001snnnn", "1111dddd0000mmmm", true,  2, LsrReg },

   { "mcr, mcr2",              "111l1110ooo0nnnn", "ttttccccppp1mmmm", true,  1, Mcr },

   { "mcrr, mcrr2",            "111l11000100uuuu", "ttttccccoooommmm", true,  1, Mcrr },

   { "mla",                    "111110110000nnnn", "aaaadddd0000mmmm", true,  1, MlaMls },
   { "mls",                    "111110110000nnnn", "aaaadddd0001mmmm", true,  2, MlaMls },

   { "mov (immediate)",        "00100dddiiiiiiii", "xxxxxxxxxxxxxxxx", false, 1, MovImm },
   { "mov (immediate)",        "11110i00010s1111", "0iiiddddiiiiiiii", true,  2, MovImm },
   { "movw (immediate)",       "11110i100100kkkk", "0iiiddddiiiiiiii", true,  3, MovImm },
   { "mov (register)",         "01000110dmmmmddd", "xxxxxxxxxxxxxxxx", false, 1, MovReg },
   { "mov (register)",         "11101010010s1111", "0000dddd0000mmmm", true,  3, MovReg },

   { "movt",                   "11110i101100kkkk", "0iiiddddiiiiiiii", true,  1, MovT },

   { "mrc, mrc2",              "111l1110ooo1nnnn", "ttttccccppp1mmmm", true,  1, Mrc },

   { "mrrc, mrrc2",            "111l11000101uuuu", "ttttccccoooommmm", true,  1, Mrrc },

   { "mrs",                    "1111001111101111", "1000ddddssssssss", true,  1, Mrs },

   { "msr",                    "111100111000nnnn", "1000mm00ssssssss", true,  1, Msr },

   { "mul",                    "0100001101nnnmmm", "xxxxxxxxxxxxxxxx", false, 1, MulReg },
   { "mul",                    "111110110000nnnn", "1111dddd0000mmmm", true,  2, MulReg },

   { "mvn (immediate)",        "11110i00011s1111", "0iiiddddiiiiiiii", true,  1, MvnImm },
   { "mvn (register)",         "0100001111mmmddd", "xxxxxxxxxxxxxxxx", false, 1, MvnReg },
   { "mvn (register)",         "11101010011s1111", "0iiiddddiittmmmm", true,  2, MvnReg },

   { "nop and hints",          "1111001110101111", "10000000hhhhhhhh", true,  1, Nop },

   { "orn (immediate)",        "11110i00011snnnn", "0iiiddddiiiiiiii", true,  1, OrnImm },
   { "orn (register)",         "11101010011snnnn", "0iiiddddiittmmmm", true,  1, OrnReg },

   { "orr (immediate)",        "11110i00010snnnn", "0iiiddddiiiiiiii", true,  1, OrrImm },
   { "orr (register)",         "0100001100mmmddd", "xxxxxxxxxxxxxxxx", false, 1, OrrReg },
   { "orr (register)",         "11101010010snnnn", "0iiiddddiittmmmm", true,  2, OrrReg },

   { "pld (immediate)",        "111110001001nnnn", "1111iiiiiiiiiiii", true,  1, PldImm },
   { "pld (immediate)",        "111110000001nnnn", "11111100iiiiiiii", true,  2, PldImm },
   { "pld (literal)",          "11111000u0011111", "1111iiiiiiiiiiii", true,  1, PldLiter },
   { "pld (register)",         "111110000001nnnn", "1111000000ssmmmm", true,  1, PldReg },

   { "pli (immediate)",        "111110011001nnnn", "1111iiiiiiiiiiii", true,  1, PliImm },
   { "pli (immediate)",        "111110010001nnnn", "11111100iiiiiiii", true,  2, PliImm },
   { "pli (literal)",          "11111001u0011111", "1111iiiiiiiiiiii", true,  3, PliImm },
   { "pli (register)",         "111110010001nnnn", "1111000000ssmmmm", true,  1, PliReg },

   { "pop",                    "1011110prrrrrrrr", "xxxxxxxxxxxxxxxx", false, 1, Pop },
   { "pop",                    "1110100010111101", "rrrrrrrrrrrrrrrr", true,  2, Pop },
   { "pop",                    "1111100001011101", "tttt101100000100", true,  3, Pop },

   { "push",                   "1011010mrrrrrrrr", "xxxxxxxxxxxxxxxx", false, 1, Push },
   { "push",                   "1110100100101101", "rrrrrrrrrrrrrrrr", true,  2, Push },
   { "push",                   "1111100001001101", "tttt110100000100", true,  3, Push },

   { "rbit",                   "111110101001mmmm", "1111dddd1010xxxx", true,  1, Rbit },

   { "rev",                    "1011101000mmmddd", "xxxxxxxxxxxxxxxx", false, 1, Rev },
   { "rev",                    "111110101001mmmm", "1111dddd1000xxxx", true,  2, Rev },
   { "rev16",                  "1011101001mmmddd", "xxxxxxxxxxxxxxxx", false, 1, Rev16 },
   { "rev16",                  "111110101001mmmm", "1111dddd1001xxxx", true,  2, Rev16 },
   { "revsh",                  "1011101011mmmddd", "xxxxxxxxxxxxxxxx", false, 1, RevSh },
   { "revsh",                  "111110101001mmmm", "1111dddd1011xxxx", true,  2, RevSh },

   { "ror (immediate)",        "11101010010s1111", "0iiiddddii11mmmm", true,  1, RorImm },
   { "ror (register)",         "0100000111mmmddd", "xxxxxxxxxxxxxxxx", false, 1, RorReg },
   { "ror (register)",         "11111010011snnnn", "1111dddd0000mmmm", true,  2, RorReg },

   { "rrx",                    "11101010010s1111", "0000dddd0011mmmm", true,  1, Rrx },

   { "rsb (immediate)",        "0100001001nnnddd", "xxxxxxxxxxxxxxxx", false, 1, RsbImm },
   { "rsb (immediate)",        "11110i01110snnnn", "0iiiddddiiiiiiii", true,  2, RsbImm },
   { "rsb (register)",         "11101011110snnnn", "0iiiddddiittmmmm", true,  1, RsbReg },

   { "sbc (immediate)",        "11110i01011snnnn", "0iiiddddiiiiiiii", true,  1, SbcImm },
   { "sbc (register)",         "0100000110mmmddd", "xxxxxxxxxxxxxxxx", false, 1, SbcReg },
   { "sbc (register)",         "11101011011snnnn", "0iiiddddiittmmmm", true,  2, SbcReg },

   { "sbfx",                   "111100110100nnnn", "0iiiddddii0wwwww", true,  1, Sbfx },

   { "sdiv",                   "111110111001nnnn", "1111dddd1111mmmm", true,  1, Sdiv },

   { "sel",                    "111110101010nnnn", "1111dddd1000mmmm", true,  1, Sel },

   { "smlal",                  "111110111100nnnn", "llllhhhh0000mmmm", true,  1, Smlal },

   { "smull",                  "111110111000nnnn", "llllhhhh0000mmmm", true,  1, Smull },

   { "ssat",                   "1111001100s0nnnn", "0iiiddddii0kkkkk", true,  1, Ssat },

   { "stc, stc2",              "111t110pulw0nnnn", "ddddcccciiiiiiii", true,  1, Stc },

   { "stm",                    "11000nnnrrrrrrrr", "xxxxxxxxxxxxxxxx", false, 1, Stmia },
   { "stm",                    "1110100010w0nnnn", "rrrrrrrrrrrrrrrr", true,  2, Stmia },

   { "stmdb, stmfd",           "1110100100w0nnnn", "rrrrrrrrrrrrrrrr", true,  1, StmDb },

   { "str (immediate)",        "01100iiiiinnnttt", "xxxxxxxxxxxxxxxx", false, 1, StrImm },
   { "str (immediate)",        "10010tttiiiiiiii", "xxxxxxxxxxxxxxxx", false, 2, StrImm },
   { "str (immediate)",        "111110001100nnnn", "ttttiiiiiiiiiiii", true,  3, StrImm },
   { "str (immediate)",        "111110000100nnnn", "tttt1puwiiiiiiii", true,  4, StrImm },
   { "str (register)",         "0101000mmmnnnttt", "xxxxxxxxxxxxxxxx", false, 1, StrReg },
   { "str (register)",         "111110000100nnnn", "tttt000000iimmmm", true,  2, StrReg },

   { "strb (immediate)",       "01110iiiiinnnttt", "xxxxxxxxxxxxxxxx", false, 1, StrbImm },
   { "strb (immediate)",       "111110001000nnnn", "ttttiiiiiiiiiiii", true,  2, StrbImm },
   { "strb (immediate)",       "111110000000nnnn", "tttt1puwiiiiiiii", true,  3, StrbImm },
   { "strb (register)",        "0101010mmmnnnttt", "xxxxxxxxxxxxxxxx", false, 1, StrbReg },
   { "strb (register)",        "111110000000nnnn", "tttt000000iimmmm", true,  2, StrbReg },
   
   { "strbt",                  "111110000000nnnn", "tttt1110iiiiiiii", true,  1, Strbt },
   { "strex",                  "111010000100nnnn", "ttttddddiiiiiiii", true,  1, Strex },
   { "strexb",                 "111010001100nnnn", "tttt11110100dddd", true,  2, Strex },
   { "strexh",                 "111010001100nnnn", "tttt11110101dddd", true,  4, Strex },
   { "strd (immediate)",       "1110100pu1w0nnnn", "ttttddddiiiiiiii", true,  1, StrdImm },

   { "strh (immediate)",       "10000iiiiinnnttt", "xxxxxxxxxxxxxxxx", false, 1, StrhImm },
   { "strh (immediate)",       "111110001010nnnn", "ttttiiiiiiiiiiii", true,  2, StrhImm },
   { "strh (immediate)",       "111110000010nnnn", "tttt1puwiiiiiiii", true,  3, StrhImm },
   { "strh (register)",        "0101001mmmnnnttt", "xxxxxxxxxxxxxxxx", false, 1, StrhReg },
   { "strh (register)",        "111110000010nnnn", "tttt000000iimmmm", true,  2, StrhReg },

   { "strht",                  "111110000010nnnn", "tttt1110iiiiiiii", true,  1, Strht },
   { "strt",                   "111110000100nnnn", "tttt1110iiiiiiii", true,  1, Strt },

   { "sub (immediate)",        "0001111iiinnnddd", "xxxxxxxxxxxxxxxx", false, 1, SubImm },
   { "sub (immediate)",        "00111dddiiiiiiii", "xxxxxxxxxxxxxxxx", false, 2, SubImm },
   { "sub (immediate)",        "11110i01101snnnn", "0iiiddddiiiiiiii", true,  3, SubImm },
   { "subw (immediate)",       "11110i101010nnnn", "0iiiddddiiiiiiii", true,  4, SubImm },
   { "sub (register)",         "0001101mmmnnnddd", "xxxxxxxxxxxxxxxx", false, 1, SubReg },
   { "sub (register)",         "11101011101snnnn", "0iiiddddiittmmmm", true,  2, SubReg },
   { "sub (sp immediate)",     "101100001iiiiiii", "xxxxxxxxxxxxxxxx", false, 1, SubSpImm },

   { "svc",                    "11011111iiiiiiii", "xxxxxxxxxxxxxxxx", false, 1, Svc },

   { "sxtb",                   "1011001001mmmddd", "xxxxxxxxxxxxxxxx", false, 1, Sxtb },
   { "sxtb",                   "1111101001001111", "1111dddd10rrmmmm", true,  2, Sxtb },
   { "sxth",                   "1011001000mmmddd", "xxxxxxxxxxxxxxxx", false, 1, Sxth },
   { "sxth",                   "1111101000001111", "1111dddd10rrmmmm", true,  2, Sxth },

   { "teq (immediate)",        "11110i001001nnnn", "0iii1111iiiiiiii", true,  1, TeqImm },
   { "teq (register)",         "111010101001nnnn", "0iii1111iittmmmm", true,  1, TeqReg },

   { "tbb, tbh",               "111010001101nnnn", "11110000000hmmmm", true, 1, TbbTbh },

   { "tst (immediate)",        "11110i000001nnnn", "0iii1111iiiiiiii", true,  1, TstImm },
   { "tst (register)",         "0100001000mmmnnn", "xxxxxxxxxxxxxxxx", false, 1, TstReg },
   { "tst (register)",         "111010100001nnnn", "0iii1111iittmmmm", true,  2, TstReg },

   { "ubfx",                   "111100111100nnnn", "0iiiddddii0wwwww", true,  1, Ubfx },

   { "udiv",                   "111110111011nnnn", "1111dddd1111mmmm", true,  1, Udiv },

   { "umlal",                  "111110111110nnnn", "llllhhhh0000mmmm", true,  1, Umlal },

   { "umull",                  "111110111010nnnn", "llllhhhh0000mmmm", true,  1, Umull },

   { "usat",                   "1111001110s0nnnn", "0iiiddddii0kkkkk", true,  1, Usat },

   { "uxtb",                   "1011001011mmmddd", "xxxxxxxxxxxxxxxx", false, 1, Uxtb },
   { "uxtb",                   "1111101001011111", "1111dddd10rrmmmm", true,  2, Uxtb },
   { "uxth",                   "1011001010mmmddd", "xxxxxxxxxxxxxxxx", false, 1, Uxth },
   { "uxth",                   "1111101000011111", "1111dddd10rrmmmm", true,  2, Uxth },

//   { "blx",                    "11110siiiiiiiiii", "11j0kiiiiiiiiiii", true,  3, BxReg },     // Not in M
//   { "ldrexd",                 "111010001101nnnn", "ttttmmmm01111111", true,  3, Ldrex },     // Not in M
//   { "pkhbt, pkhtb",           "111010101100nnnn", "0iiiddddiit0mmmm", true,  1, Pkhtb},      // Not in M
//   { "setend",                 "101101100101a000", "xxxxxxxxxxxxxxxx", false, 1, SetEnd },    // Not in M
//   { "ssat16",                 "111100110010nnnn", "0000dddd000kkkkk", true,  2, Ssat },      // Not in M
//   { "strexd",                 "111010001100nnnn", "ttttmmmm0111dddd", true,  3, Strex },     // Not in M
//   { "usat16",                 "111100111010nnnn", "0000dddd000kkkkk", true,  2, Usat },      // Not in M

   { "undefined",              "aaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbb", true,  1, UndefinedOp },
   {NULL}
};

void FormatInstruction(const char *lpstrFormat, CFieldSet *lpcFieldSet, char *lpstrBuffer)
{
   // Clear buffer
   lpstrBuffer[0] = 0;

   while (0 != *lpstrFormat)
   {
      if ('<' == *lpstrFormat)
      { 
         const char *arrCond[] = { "eq", "ne", "cs", "cc", "mi", "pl", "vs", "vc", "hi", "ls", "ge", "lt", "gt", "le", "al", "<und>" };

         // Skip '<'
         lpstrFormat++;

         // Process token, first symbol is a type
         switch (*lpstrFormat++)
         {
         case '<': // Just copy
            {
               strcat(lpstrBuffer, "<");
               continue;
            }
            break;
         case 't': // Instruction space separation from arguments
            {
               int iSpaces = 10 - strlen(lpstrBuffer);
               if (0 < iSpaces)
                  strncat(lpstrBuffer, "            ", iSpaces);
            }
            break;
         case 'C': // Conditional string or set flags
            {
               if (16 <= g_bCurrentCond)
                  strcat(lpstrBuffer, "s");
               else
                  strcat(lpstrBuffer, arrCond[g_bCurrentCond]);
            }
            break;
         case 'c': // Conditional instruction
            {
               if (16 > g_bCurrentCond)
                  strcat(lpstrBuffer, arrCond[g_bCurrentCond]);
            }
            break;
         case 'F': // Flag set based on field bit
            {
               s32 iSet = lpcFieldSet->GetInt(*lpstrFormat++);

               if (iSet)
                  strcat(lpstrBuffer, "s");
            }
            break;
         case 'R': // Register name
            {
               const char *arrRegName[] = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "sp", "lr", "pc" };

               strcat(lpstrBuffer, arrRegName[lpcFieldSet->GetInt(*lpstrFormat++)]);
            }
            break;
         case 'Y': // Coproc register name
            {
               const char *arrRegName[] = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" };

               strcat(lpstrBuffer, arrRegName[lpcFieldSet->GetInt(*lpstrFormat++)]);
            }
            break;
         case 'y': // Special register name write
            {
               const char *arrRegName[] = { "APSR_", "IAPSR", "EAPSR", "PSR", "<unknown>", "IPSR", "EPSR", "IEPSR", "MSP", "PSP", 
                  "<unknown>", "<unknown>", "<unknown>", "<unknown>", "<unknown>", "<unknown>", "PRIMASK", "BASEPRI", "BASEPRI_MASK", "FAULTMASK",
                  "CONTROL" };

               s32 iReg = lpcFieldSet->GetInt(*lpstrFormat++);
               s32 iMask = lpcFieldSet->GetInt(*lpstrFormat++);

               if (iReg < 21)
               {
                  strcat(lpstrBuffer, arrRegName[iReg]);
                  if (0 == iReg)
                  {
                     if (iMask & 0x02)
                        strcat(lpstrBuffer, "nzcvq");
                     if (iMask & 0x01)
                        strcat(lpstrBuffer, "g");
                  }
               }
               else
                  strcat(lpstrBuffer, "<unknown>");
            }
            break;
         case 'z': // Special register name read
            {
               const char *arrRegName[] = { "APSR", "IAPSR", "EAPSR", "PSR", "<unknown>", "IPSR", "EPSR", "IEPSR", "MSP", "PSP", 
                  "<unknown>", "<unknown>", "<unknown>", "<unknown>", "<unknown>", "<unknown>", "PRIMASK", "BASEPRI", "BASEPRI_MASK", "FAULTMASK",
                  "CONTROL" };

               s32 iReg = lpcFieldSet->GetInt(*lpstrFormat++);

               if (iReg < 21)
                  strcat(lpstrBuffer, arrRegName[iReg]);
               else
                  strcat(lpstrBuffer, "<unknown>");
            }
            break;
         case 'I': // Immediate value
            {
               char strImm[16];

               s64 iImm = lpcFieldSet->GetLong(*lpstrFormat++);
               if (iImm >= 0)
                  sprintf(strImm, "#%I64d", iImm);
               else
                  sprintf(strImm, "#-%I64d", -iImm);
               strcat(lpstrBuffer, strImm);
            }
            break;
         case 'i': // Immediate value +/- i<addflag_field><value_field>
            {
               char strImm[16];

               s32 iAdd = lpcFieldSet->GetInt(*lpstrFormat++);
               s64 iImm = lpcFieldSet->GetLong(*lpstrFormat++);
               if (iAdd)
                  sprintf(strImm, "#%I64d", iImm);
               else
                  sprintf(strImm, "#-%I64d", iImm);
               strcat(lpstrBuffer, strImm);
            }
            break;
         case 'H': // Conditional string H<field><false_string>:<true_string>
            {
               s32 iSet = lpcFieldSet->GetInt(*lpstrFormat++);
               if (iSet)
               {
                  while (*lpstrFormat != ':')
                     lpstrFormat++;
                  lpstrFormat++;

                  while (*lpstrFormat != '>')
                     strncat(lpstrBuffer, lpstrFormat++, 1);
               }
               else
               {
                  while (*lpstrFormat != ':')
                     strncat(lpstrBuffer, lpstrFormat++, 1);            
               }

               // Find end
               while (*lpstrFormat != '>')
                  lpstrFormat++;
            }
            break;
         case 'D': // Simple digital number
            {
               char strNumber[16];

               sprintf(strNumber, "%d", lpcFieldSet->GetInt(*lpstrFormat++));
               strcat(lpstrBuffer, strNumber);
            }
            break;
         case 'd': // Simple digital number in hex
            {
               char strNumber[16];

               sprintf(strNumber, "0x%04x", lpcFieldSet->GetInt(*lpstrFormat++));
               strcat(lpstrBuffer, strNumber);
            }
            break;
         case 'L': // Label related to PC 
            {
               char strImm[16];

               sprintf(strImm, "l%08x", g_uiCurrentAddr + 4 + lpcFieldSet->GetInt(*lpstrFormat++));
               strcat(lpstrBuffer,strImm);
            }
            break;
         case 'l': // Label related to Align(PC, 4) 
            {
               char strImm[16];

               sprintf(strImm, "l%08x", ALIGN4(g_uiCurrentAddr + 4) + lpcFieldSet->GetInt(*lpstrFormat++));
               strcat(lpstrBuffer,strImm);
            }
            break;
         case 'A': // Label address from immediate A<align_flag><addflag_field><imm_field> 
            {
               char strImm[16];

               bool bAlign   = ((*lpstrFormat) == '1'); lpstrFormat++;
               char cAddFlag = *lpstrFormat++;
               s32  iAdd     = (cAddFlag == '1') ? 1 : lpcFieldSet->GetInt(cAddFlag);
               s32  iImm     = lpcFieldSet->GetInt(*lpstrFormat++);

               if (g_bShowLdrLabels)
               {
                  if (bAlign)
                  {
                     if (iAdd)
                        sprintf(strImm, "l%08x", ALIGN4(g_uiCurrentAddr + 4) + iImm);
                     else
                        sprintf(strImm, "l%08x", ALIGN4(g_uiCurrentAddr + 4) - iImm);
                  }
                  else
                  {
                     if (iAdd)
                        sprintf(strImm, "l%08x", g_uiCurrentAddr + 4 + iImm);
                     else
                        sprintf(strImm, "l%08x", g_uiCurrentAddr + 4 - iImm);
                  }

                  strcat(lpstrBuffer,strImm);
               }
               else
               {
                  if (iAdd)
                     sprintf(strImm, "[pc, #%d]", iImm);
                  else
                     sprintf(strImm, "[pc, #-%d]", iImm);
                  strcat(lpstrBuffer, strImm);
               }
            }
            break;
         case 'r': // Register list
            {
               const char *arrRegName[] = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "sp", "lr", "pc" };

               int iRegMask = lpcFieldSet->GetInt(*lpstrFormat++);
               bool bFirst  = true;

               for (int i = 0; i < 16; ++i)
               {
                  if (iRegMask & (1 << i))
                  {
                     if (!bFirst)
                        strcat(lpstrBuffer, ", ");
                     strcat(lpstrBuffer, arrRegName[i]);
                     bFirst = false;
                  }
               }
            }
            break;
         case 'T': // IT instr mask string representation
            {
               u8 bMask = lpcFieldSet->GetInt(*lpstrFormat++);
               u8 bCond = lpcFieldSet->GetInt(*lpstrFormat++);

               int iCondCount = 0;

               if (0 == bMask)
                  iCondCount = 4;
               else
               {
                  while (!(bMask & (1 << iCondCount)))
                     iCondCount++;
               }

               for (int i = 3; i >= iCondCount + 1; --i)
               {
                  if (bMask & (1 << i))
                     strcat(lpstrBuffer, (bCond & 0x01) ? "t" : "e");
                  else
                     strcat(lpstrBuffer, (bCond & 0x01) ? "e" : "t");
               }
            }
            break;
         case 'S': // Immediate shift decode S<type_field><imm_field>
            {
               u8    bType = lpcFieldSet->GetInt(*lpstrFormat++);
               u8    bImm = lpcFieldSet->GetInt(*lpstrFormat++);
               char  strNumber[16];

               if (0 != bType || 0 != bImm)
               {
                  switch (bType)
                  {
                  case 0: // lsl
                     strcat(lpstrBuffer, ", lsl #");
                     sprintf(strNumber, "%d", bImm);
                     strcat(lpstrBuffer, strNumber);
                     break;
                  case 1: // lsr
                     strcat(lpstrBuffer, ", lsr #");
                     sprintf(strNumber, "%d", bImm == 0 ? 32 : bImm);
                     strcat(lpstrBuffer, strNumber);
                     break;
                  case 2: // asr
                     strcat(lpstrBuffer, ", asr #");
                     sprintf(strNumber, "%d", bImm == 0 ? 32 : bImm);
                     strcat(lpstrBuffer, strNumber);
                     break;
                  case 3: // ror/rrx
                     if (bImm)
                     {
                        strcat(lpstrBuffer, ", ror #");
                        sprintf(strNumber, "%d", bImm);
                        strcat(lpstrBuffer, strNumber);
                     }
                     else
                        strcat(lpstrBuffer, ", rrx");
                     break;
                  }

               }
            }
            break;
         case 'X': //Rotate decode X<rot_field>
            {
               u8    bRot = lpcFieldSet->GetInt(*lpstrFormat++);
               char  strNumber[16];

               if (bRot)
               {
                  strcat(lpstrBuffer, ", ror #");
                  sprintf(strNumber, "%d", bRot * 8);
                  strcat(lpstrBuffer, strNumber);
               }
            }
            break;
         default:
            assert(false);
            break;
         }

         // Skip '>'
         lpstrFormat++;
      }
      else
      {
         strncat(lpstrBuffer, lpstrFormat, 1);
         lpstrFormat++;
      }
   }
}

int FindInstruction(u16 usInstr, u16 usInstr2)
{
   tInstructionInfo *lpcTable = g_arrInstructionInfo;

   while (1)
   {
      // Check end of the table
      if (NULL == (*lpcTable).lpstrName)
         PrintErrorExit("Error: Unknown instruction: 0x%04X\n", usInstr);

      // Process pattern
      const char *strPattern = (*lpcTable).lpstrPattern;
      bool        bMatch     = true;
      CFieldSet   cFieldSet;

      for (int i = 0; i < 16; ++i) 
      {
         switch (strPattern[i]) 
         {
         case '0':
            if (0 != (usInstr & (1 << (15 - i))))
               bMatch = false;
            break;
         case '1':
            if (0 == (usInstr & (1 << (15 - i))))
               bMatch = false;
            break;
         case 'x':
            // Unused bit
            break;
         default:
            cFieldSet.PushBit(strPattern[i], (usInstr & (1 << (15 - i))));
            break;
         }
      }

      // 32 bit instructions
      if ((*lpcTable).b32bit)
      {
         const char *strPattern2 = (*lpcTable).lpstrPattern2;

         for (int i = 0; i < 16; ++i) 
         {
            switch (strPattern2[i]) 
            {
            case '0':
               if (0 != (usInstr2 & (1 << (15 - i))))
                  bMatch = false;
               break;
            case '1':
               if (0 == (usInstr2 & (1 << (15 - i))))
                  bMatch = false;
               break;
            case 'x':
               // Unused bit
               break;
            default:
               cFieldSet.PushBit(strPattern2[i], (usInstr2 & (1 << (15 - i))));
               break;
            }
         }
      }

      if (bMatch)
      {
         // Process expressions
         if ((*lpcTable).lpfDecode)
         {
            int iSize = (*lpcTable).lpfDecode(cFieldSet, (*lpcTable).iT);
            if (iSize > 0)
               return iSize;
         }
      }

      lpcTable++;
   }

   return 1;
}