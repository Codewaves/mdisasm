/*
 *  types.h
 *  cortex_disasm
 *
 *  Created by Sergej Kravcenko on 12/1/10.
 *  Copyright 2010 Codewaves. All rights reserved.
 *
 */

#ifndef TYPES_H
#define TYPES_H

typedef char                  s8;
typedef unsigned char	      u8;
typedef signed short          s16;
typedef unsigned short	      u16;
typedef signed int		      s32;
typedef unsigned int 	      u32;
typedef signed long long      s64;
typedef unsigned long long    u64;

#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE false
#endif

#ifndef TRUE
#define TRUE true
#endif

// Binary conversion macros
#define HEX__(n) 0x##n##LU 

#define B8__(x) ((x&0x0000000FLU)?1:0)      \
               +((x&0x000000F0LU)?2:0)      \
               +((x&0x00000F00LU)?4:0)      \
               +((x&0x0000F000LU)?8:0)      \
               +((x&0x000F0000LU)?16:0)     \
               +((x&0x00F00000LU)?32:0)     \
               +((x&0x0F000000LU)?64:0)     \
               +((x&0xF0000000LU)?128:0) 

#define B8(d) ((unsigned char)B8__(HEX__(d)))

#define B16(dmsb,dlsb) (((unsigned short)B8(dmsb)<<8) \
                        + B8(dlsb)) 

#define B32(dmsb,db2,db3,dlsb) (((unsigned long)B8(dmsb)<<24)  \
                                + ((unsigned long)B8(db2)<<16) \
                                + ((unsigned long)B8(db3)<<8)  \
                                + B8(dlsb))

#define ALIGN4(x) ((x) & 0xFFFFFFFC)
#define ALIGN2(x) ((x) & 0xFFFFFFFE)

#define PrintErrorExit(...) { printf(__VA_ARGS__); exit(1); }

#endif