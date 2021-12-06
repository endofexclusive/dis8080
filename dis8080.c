/* Copyright (C) 2021 Martin Åberg. License: BSD-3-Clause. */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEP "\t"

/* This type represents one Intel 8080 instruction. */
struct instinfo {
  int opcode;
  const char *mnemonic;
  int size;
  enum {
    OPERAND_NONE,
    OPERAND_BYTE,
    OPERAND_WORD
  } operand;
};

/* This table describes all the Intel 8080 instructions. */
const struct instinfo INSTINFO[] = {
  /* Data Transfer Group */
  { 0x78, "mov"  SEP "a,b", 1},
  { 0x79, "mov"  SEP "a,c", 1},
  { 0x7a, "mov"  SEP "a,d", 1},
  { 0x7b, "mov"  SEP "a,e", 1},
  { 0x7c, "mov"  SEP "a,h", 1},
  { 0x7d, "mov"  SEP "a,l", 1},
  { 0x7e, "mov"  SEP "a,m", 1},
  { 0x7f, "mov"  SEP "a,a", 1},
  { 0x40, "mov"  SEP "b,b", 1},
  { 0x41, "mov"  SEP "b,c", 1},
  { 0x42, "mov"  SEP "b,d", 1},
  { 0x43, "mov"  SEP "b,e", 1},
  { 0x44, "mov"  SEP "b,h", 1},
  { 0x45, "mov"  SEP "b,l", 1},
  { 0x46, "mov"  SEP "b,m", 1},
  { 0x47, "mov"  SEP "b,a", 1},
  { 0x48, "mov"  SEP "c,b", 1},
  { 0x49, "mov"  SEP "c,c", 1},
  { 0x4a, "mov"  SEP "c,d", 1},
  { 0x4b, "mov"  SEP "c,e", 1},
  { 0x4c, "mov"  SEP "c,h", 1},
  { 0x4d, "mov"  SEP "c,l", 1},
  { 0x4e, "mov"  SEP "c,m", 1},
  { 0x4f, "mov"  SEP "c,a", 1},
  { 0x50, "mov"  SEP "d,b", 1},
  { 0x51, "mov"  SEP "d,c", 1},
  { 0x52, "mov"  SEP "d,d", 1},
  { 0x53, "mov"  SEP "d,e", 1},
  { 0x54, "mov"  SEP "d,h", 1},
  { 0x55, "mov"  SEP "d,l", 1},
  { 0x56, "mov"  SEP "d,m", 1},
  { 0x57, "mov"  SEP "d,a", 1},
  { 0x58, "mov"  SEP "e,b", 1},
  { 0x59, "mov"  SEP "e,c", 1},
  { 0x5a, "mov"  SEP "e,d", 1},
  { 0x5b, "mov"  SEP "e,e", 1},
  { 0x5c, "mov"  SEP "e,h", 1},
  { 0x5d, "mov"  SEP "e,l", 1},
  { 0x5e, "mov"  SEP "e,m", 1},
  { 0x5f, "mov"  SEP "e,a", 1},
  { 0x60, "mov"  SEP "h,b", 1},
  { 0x61, "mov"  SEP "h,c", 1},
  { 0x62, "mov"  SEP "h,d", 1},
  { 0x63, "mov"  SEP "h,e", 1},
  { 0x64, "mov"  SEP "h,h", 1},
  { 0x65, "mov"  SEP "h,l", 1},
  { 0x66, "mov"  SEP "h,m", 1},
  { 0x67, "mov"  SEP "h,a", 1},
  { 0x68, "mov"  SEP "l,b", 1},
  { 0x69, "mov"  SEP "l,c", 1},
  { 0x6a, "mov"  SEP "l,d", 1},
  { 0x6b, "mov"  SEP "l,e", 1},
  { 0x6c, "mov"  SEP "l,h", 1},
  { 0x6d, "mov"  SEP "l,l", 1},
  { 0x6e, "mov"  SEP "l,m", 1},
  { 0x6f, "mov"  SEP "l,a", 1},
  { 0x70, "mov"  SEP "m,b", 1},
  { 0x71, "mov"  SEP "m,c", 1},
  { 0x72, "mov"  SEP "m,d", 1},
  { 0x73, "mov"  SEP "m,e", 1},
  { 0x74, "mov"  SEP "m,h", 1},
  { 0x75, "mov"  SEP "m,l", 1},
  { 0x77, "mov"  SEP "m,a", 1},
  { 0x06, "mvi"  SEP "b,",  2, OPERAND_BYTE},
  { 0x16, "mvi"  SEP "d,",  2, OPERAND_BYTE},
  { 0x26, "mvi"  SEP "h,",  2, OPERAND_BYTE},
  { 0x36, "mvi"  SEP "m,",  2, OPERAND_BYTE},
  { 0x0e, "mvi"  SEP "c,",  2, OPERAND_BYTE},
  { 0x1e, "mvi"  SEP "e,",  2, OPERAND_BYTE},
  { 0x2e, "mvi"  SEP "l,",  2, OPERAND_BYTE},
  { 0x3e, "mvi"  SEP "a,",  2, OPERAND_BYTE},
  { 0x3a, "lda"  SEP,       3, OPERAND_WORD},
  { 0x32, "sta"  SEP,       3, OPERAND_WORD},
  { 0x2a, "lhld" SEP,       3, OPERAND_WORD},
  { 0x22, "shld" SEP,       3, OPERAND_WORD},
  { 0x01, "lxi"  SEP "b,",  3, OPERAND_WORD},
  { 0x11, "lxi"  SEP "d,",  3, OPERAND_WORD},
  { 0x21, "lxi"  SEP "h,",  3, OPERAND_WORD},
  { 0x31, "lxi"  SEP "sp,", 3, OPERAND_WORD},
  { 0x0a, "ldax" SEP "b",   1},
  { 0x1a, "ldax" SEP "d",   1},
  { 0x02, "stax" SEP "b",   1},
  { 0x12, "stax" SEP "d",   1},
  { 0xeb, "xchg",           1},

  /* Arithmetic Group */
  { 0x80, "add"  SEP "b",   1},
  { 0x81, "add"  SEP "c",   1},
  { 0x82, "add"  SEP "d",   1},
  { 0x83, "add"  SEP "e",   1},
  { 0x84, "add"  SEP "h",   1},
  { 0x85, "add"  SEP "l",   1},
  { 0x86, "add"  SEP "m",   1},
  { 0x87, "add"  SEP "a",   1},
  { 0xc6, "adi"  SEP,       2, OPERAND_BYTE},
  { 0x88, "adc"  SEP "b",   1},
  { 0x89, "adc"  SEP "c",   1},
  { 0x8a, "adc"  SEP "d",   1},
  { 0x8b, "adc"  SEP "e",   1},
  { 0x8c, "adc"  SEP "h",   1},
  { 0x8d, "adc"  SEP "l",   1},
  { 0x8e, "adc"  SEP "m",   1},
  { 0x8f, "adc"  SEP "a",   1},
  { 0xce, "aci"  SEP,       2, OPERAND_BYTE},
  { 0x90, "sub"  SEP "b",   1},
  { 0x91, "sub"  SEP "c",   1},
  { 0x92, "sub"  SEP "d",   1},
  { 0x93, "sub"  SEP "e",   1},
  { 0x94, "sub"  SEP "h",   1},
  { 0x95, "sub"  SEP "l",   1},
  { 0x96, "sub"  SEP "m",   1},
  { 0x97, "sub"  SEP "a",   1},
  { 0xd6, "sui"  SEP,       2, OPERAND_BYTE},
  { 0x98, "sbb"  SEP "b",   1},
  { 0x99, "sbb"  SEP "c",   1},
  { 0x9a, "sbb"  SEP "d",   1},
  { 0x9b, "sbb"  SEP "e",   1},
  { 0x9c, "sbb"  SEP "h",   1},
  { 0x9d, "sbb"  SEP "l",   1},
  { 0x9e, "sbb"  SEP "m",   1},
  { 0x9f, "sbb"  SEP "a",   1},
  { 0xde, "sbi"  SEP,       2, OPERAND_BYTE},
  { 0x04, "inr"  SEP "b",   1},
  { 0x14, "inr"  SEP "d",   1},
  { 0x24, "inr"  SEP "h",   1},
  { 0x34, "inr"  SEP "m",   1},
  { 0x0c, "inr"  SEP "c",   1},
  { 0x1c, "inr"  SEP "e",   1},
  { 0x2c, "inr"  SEP "l",   1},
  { 0x3c, "inr"  SEP "a",   1},
  { 0x05, "dcr"  SEP "b",   1},
  { 0x15, "dcr"  SEP "d",   1},
  { 0x25, "dcr"  SEP "h",   1},
  { 0x35, "dcr"  SEP "m",   1},
  { 0x0d, "dcr"  SEP "c",   1},
  { 0x1d, "dcr"  SEP "e",   1},
  { 0x2d, "dcr"  SEP "l",   1},
  { 0x3d, "dcr"  SEP "a",   1},
  { 0x03, "inx"  SEP "b",   1},
  { 0x13, "inx"  SEP "d",   1},
  { 0x23, "inx"  SEP "h",   1},
  { 0x33, "inx"  SEP "sp",  1},
  { 0x0b, "dcx"  SEP "b",   1},
  { 0x1b, "dcx"  SEP "d",   1},
  { 0x2b, "dcx"  SEP "h",   1},
  { 0x3b, "dcx"  SEP "sp",  1},
  { 0x09, "dad"  SEP "b",   1},
  { 0x19, "dad"  SEP "d",   1},
  { 0x29, "dad"  SEP "h",   1},
  { 0x39, "dad"  SEP "sp",  1},
  { 0x27, "daa",            1},

  /* Logical Group */
  { 0xa0, "ana"  SEP "b",   1},
  { 0xa1, "ana"  SEP "c",   1},
  { 0xa2, "ana"  SEP "d",   1},
  { 0xa3, "ana"  SEP "e",   1},
  { 0xa4, "ana"  SEP "h",   1},
  { 0xa5, "ana"  SEP "l",   1},
  { 0xa6, "ana"  SEP "m",   1},
  { 0xa7, "ana"  SEP "a",   1},
  { 0xe6, "ani"  SEP,       2, OPERAND_BYTE},
  { 0xb0, "ora"  SEP "b",   1},
  { 0xb1, "ora"  SEP "c",   1},
  { 0xb2, "ora"  SEP "d",   1},
  { 0xb3, "ora"  SEP "e",   1},
  { 0xb4, "ora"  SEP "h",   1},
  { 0xb5, "ora"  SEP "l",   1},
  { 0xb6, "ora"  SEP "m",   1},
  { 0xb7, "ora"  SEP "a",   1},
  { 0xf6, "ori"  SEP,       2, OPERAND_BYTE},
  { 0xa8, "xra"  SEP "b",   1},
  { 0xa9, "xra"  SEP "c",   1},
  { 0xaa, "xra"  SEP "d",   1},
  { 0xab, "xra"  SEP "e",   1},
  { 0xac, "xra"  SEP "h",   1},
  { 0xad, "xra"  SEP "l",   1},
  { 0xae, "xra"  SEP "m",   1},
  { 0xaf, "xra"  SEP "a",   1},
  { 0xee, "xri"  SEP,       2, OPERAND_BYTE},
  /* Compare instructions */
  { 0xb8, "cmp"  SEP "b",   1},
  { 0xb9, "cmp"  SEP "c",   1},
  { 0xba, "cmp"  SEP "d",   1},
  { 0xbb, "cmp"  SEP "e",   1},
  { 0xbc, "cmp"  SEP "h",   1},
  { 0xbd, "cmp"  SEP "l",   1},
  { 0xbe, "cmp"  SEP "m",   1},
  { 0xbf, "cmp"  SEP "a",   1},
  { 0xfe, "cpi"  SEP,       2, OPERAND_BYTE},
  /* Rotate instructions */
  { 0x07, "rlc",            1},
  { 0x0f, "rrc",            1},
  { 0x17, "ral",            1},
  { 0x1f, "rar",            1},
  /* Complement and carry flag instructions */
  { 0x2f, "cma",            1},
  { 0x3f, "cmc",            1},
  { 0x37, "stc",            1},

  /* Branch Group */
  /* Unconditional branching instructions */
  { 0xc3, "jmp"  SEP,       3, OPERAND_WORD},
  { 0xcd, "call" SEP,       3, OPERAND_WORD},
  { 0xc9, "ret",            1},
  { 0xe9, "pchl",           1},
  { 0xc7, "rst"  SEP "0",   1},
  { 0xd7, "rst"  SEP "2",   1},
  { 0xe7, "rst"  SEP "4",   1},
  { 0xf7, "rst"  SEP "6",   1},
  { 0xcf, "rst"  SEP "1",   1},
  { 0xdf, "rst"  SEP "3",   1},
  { 0xef, "rst"  SEP "5",   1},
  { 0xff, "rst"  SEP "7",   1},
  /* Conditional branching instructions */
  { 0xda, "jc"   SEP,       3, OPERAND_WORD},
  { 0xd2, "jnc"  SEP,       3, OPERAND_WORD},
  { 0xca, "jz"   SEP,       3, OPERAND_WORD},
  { 0xc2, "jnz"  SEP,       3, OPERAND_WORD},
  { 0xf2, "jp"   SEP,       3, OPERAND_WORD},
  { 0xfa, "jm"   SEP,       3, OPERAND_WORD},
  { 0xea, "jpe"  SEP,       3, OPERAND_WORD},
  { 0xe2, "jpo"  SEP,       3, OPERAND_WORD},
  { 0xdc, "cc"   SEP,       3, OPERAND_WORD},
  { 0xd4, "cnc"  SEP,       3, OPERAND_WORD},
  { 0xcc, "cz"   SEP,       3, OPERAND_WORD},
  { 0xc4, "cnz"  SEP,       3, OPERAND_WORD},
  { 0xf4, "cp"   SEP,       3, OPERAND_WORD},
  { 0xfc, "cm"   SEP,       3, OPERAND_WORD},
  { 0xec, "cpe"  SEP,       3, OPERAND_WORD},
  { 0xe4, "cpo"  SEP,       3, OPERAND_WORD},
  { 0xd8, "rc",             1},
  { 0xd0, "rnc",            1},
  { 0xc8, "rz",             1},
  { 0xc0, "rnz",            1},
  { 0xf0, "rp",             1},
  { 0xf8, "rm",             1},
  { 0xe8, "rpe",            1},
  { 0xe0, "rpo",            1},

  /* Stack, I/O, and Machine Control Instructions */
  { 0xc5, "push" SEP "b",   1},
  { 0xd5, "push" SEP "d",   1},
  { 0xe5, "push" SEP "h",   1},
  { 0xf5, "push" SEP "psw", 1},
  { 0xc1, "pop"  SEP "b",   1},
  { 0xd1, "pop"  SEP "d",   1},
  { 0xe1, "pop"  SEP "h",   1},
  { 0xf1, "pop"  SEP "psw", 1},
  { 0xe3, "xthl",           1},
  { 0xf9, "sphl",           1},
  { 0xdb, "in"   SEP,       2, OPERAND_BYTE},
  { 0xd3, "out"  SEP,       2, OPERAND_BYTE},
  { 0xfb, "ei",             1},
  { 0xf3, "di",             1},
  { 0x76, "hlt",            1},
  { 0x00, "nop",            1, OPERAND_NONE},

  { 0x00, "TERM",           0, }
};


/* This type represents one Intel 8080 memory location. */
struct state_per_location {
  char *disline;
  char linebuf[32];
  /* Location is referenced by an address operand. */
  int needlabel;
  /* A label was emitted during instruction print pass. */
  int gotlabel;
  int size;
  /* Do not disassemble this location. */
  int forcedata;
};

/* Disassembler run-time state for each 8080 memory location. */
static struct state_per_location state[0x10000];
static long pc = -1;

/* Get next character in data stream and maintain PC. */
static int getnext(int must_get_something)
{
  int c;

  if (pc == 0xffff) {
    if (must_get_something) {
      fprintf(stderr, "Too much input\n");
      exit(1);
    } else {
      return EOF;
    }
  }
  c = getchar();
  if (c == EOF && must_get_something) {
    fprintf(stderr, "unexpected EOF\n");
    exit(1);
  }
  pc++;

  return c;
}

int main(int argc, char **argv)
{
  long i;
  int c;

  /* Parse command line parameters. */
  i = 1;
  while (i < argc) {
    if (strcmp(argv[i], "-d") == 0) {
      unsigned long addr;
      unsigned long count;

      if (argc <= (i+2)) {
        fprintf(stderr, "-d ADDR COUNT: missing argument(s)\n");
        exit(1);
      }

      i++;
      addr = strtoul(argv[i], NULL, 0);
      i++;
      count = strtoul(argv[i], NULL, 0);
      if (0x10000 <= (addr+count-1)) {
        fprintf(stderr, "-d ADDR COUNT: invalid range\n");
        exit(1);
      }

      /* Force label at end of data chunk. */
      if ((addr+count) < 0x10000) {
        state[addr+count].needlabel = 1;
      }
      while (count) {
        state[addr+count-1].forcedata = 1;
        count--;
      }

      i++;  /* next option */
    } else {
      fprintf(stderr, "illegal option %s\n", argv[i]);
      exit(1);
    }
  }

  /* Read and decode instructions. */
  while ((c = getnext(0)) != EOF) {
    const struct instinfo *inst;
    char *disline;

    disline = state[pc].linebuf;
    state[pc].disline = disline;
    state[pc].size = 1;

    if (state[pc].forcedata) {
      inst = NULL;
    } else {
      inst = &INSTINFO[0];
      while (inst->size) {
        if (inst->opcode == c) {
          /* Found an instruction which matches the opcode. */
          state[pc].size = inst->size;
          break;
        }
        inst++;
      }
    }

    if (inst && inst->size) {
      int val[2];

      disline += sprintf(disline, "%s", inst->mnemonic);

      switch (inst->operand) {
        case OPERAND_BYTE:
          val[0] = getnext(1);
          disline += sprintf(disline, "$%02x", val[0]);
          break;
        case OPERAND_WORD:
          val[0] = getnext(1);
          val[1] = getnext(1);
          state[val[1] << 8 | val[0]].needlabel = 1;
          disline += sprintf(disline, "L%02X", val[1]);
          disline += sprintf(disline, "%02X", val[0]);
          break;
        default:
          break;
      }
    } else {
      disline += sprintf(disline, "db\t$%02x", c);
      if (isprint(c)) {
        sprintf(disline, "\t\t; '%c'", c);
      }
    }
  }

  /* Print all instructions. */
  i = 0;
  while (i < pc) {
    if (state[i].disline) {
      if (state[i].needlabel) {
        state[i].gotlabel = 1;
        printf("L%04X:\n", (unsigned) i);
      }
      printf("\t%s\n", state[i].disline);
      i += state[i].size;
    } else {
      i++;
    }
  }
  printf("\n");

  /* Print symbol definitions for locations without a label. */
  i = 0;
  while (i < 0x10000) {
    if (state[i].needlabel && !state[i].gotlabel) {
      printf("L%04X\t= $%04X\n", (unsigned) i, (unsigned) i);
    }
    i++;
  }

  printf("\n");
  printf("end\n");
  printf("\n");

  return 0;
}

