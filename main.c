#define MAIN

#include <time.h>
#include "header.h"

#define OP_STOP     0xff
#define OP_DIV      0x71
#define OP_MUL      0x70
#define OP_SUB      0x61
#define OP_ADD      0x60
#define OP_SHR      0x51
#define OP_SHL      0x50
#define OP_LT       0x45
#define OP_LE       0x44
#define OP_GT       0x43
#define OP_GE       0x42
#define OP_NE       0x41
#define OP_EQ       0x40
#define OP_XOR      0x32
#define OP_OR       0x31
#define OP_AND      0x30
#define OP_LAND     0x20
#define OP_LOR      0x10
#define OP_OP       0x09
#define OP_CP       0x08
#define OP_END      0x01

typedef union {
  float f;
  unsigned int i;
  } FTOI;

void addOpcode(char* op, char* trans) {
  strcpy(opcodes[numOpcodes], op);
  strcpy(translations[numOpcodes], trans);
  numOpcodes++;
  if (numOpcodes > 767) {
    printf("Opcode table full\n");
    exit(1);
    }
  }

char* get32(char* line) {
  evalErrors = 0;
  args[argCount++] = 0x1234;
  args[argCount++] = 0x5678;
  while (*line != 0) line++;
  return line;
  }

void initOpcodes() {
  numOpcodes = 0;

  addOpcode("ADDA,R0 {W}",       "8C [H] [L]");
  addOpcode("ADDA,R1 {W}",       "8D [H] [L]");
  addOpcode("ADDA,R2 {W}",       "8E [H] [L]");
  addOpcode("ADDA,R3 {W}",       "8F [H] [L]");
  addOpcode("ADDA,R0 {W},X",     "8C 60[H] [L]");
  addOpcode("ADDA,R1 {W},X",     "8D 60[H] [L]");
  addOpcode("ADDA,R2 {W},X",     "8E 60[H] [L]");
  addOpcode("ADDA,R3 {W},X",     "8F 60[H] [L]");
  addOpcode("ADDA,R0 {W},X,+",   "8C 20[H] [L]");
  addOpcode("ADDA,R1 {W},X,+",   "8D 20[H] [L]");
  addOpcode("ADDA,R2 {W},X,+",   "8E 20[H] [L]");
  addOpcode("ADDA,R3 {W},X,+",   "8F 20[H] [L]");
  addOpcode("ADDA,R0 {W},X,-",   "8C 40[H] [L]");
  addOpcode("ADDA,R1 {W},X,-",   "8D 40[H] [L]");
  addOpcode("ADDA,R2 {W},X,-",   "8E 40[H] [L]");
  addOpcode("ADDA,R3 {W},X,-",   "8F 40[H] [L]");

  addOpcode("ADDA,R0 *{W}",      "8C 80[H] [L]");
  addOpcode("ADDA,R1 *{W}",      "8D 80[H] [L]");
  addOpcode("ADDA,R2 *{W}",      "8E 80[H] [L]");
  addOpcode("ADDA,R3 *{W}",      "8F 80[H] [L]");
  addOpcode("ADDA,R0 *{W},X",    "8C E0[H] [L]");
  addOpcode("ADDA,R1 *{W},X",    "8D E0[H] [L]");
  addOpcode("ADDA,R2 *{W},X",    "8E E0[H] [L]");
  addOpcode("ADDA,R3 *{W},X",    "8F E0[H] [L]");
  addOpcode("ADDA,R0 *{W},X,+",  "8C A0[H] [L]");
  addOpcode("ADDA,R1 *{W},X,+",  "8D A0[H] [L]");
  addOpcode("ADDA,R2 *{W},X,+",  "8E A0[H] [L]");
  addOpcode("ADDA,R3 *{W},X,+",  "8F A0[H] [L]");
  addOpcode("ADDA,R0 *{W},X,-",  "8C C0[H] [L]");
  addOpcode("ADDA,R1 *{W},X,-",  "8D C0[H] [L]");
  addOpcode("ADDA,R2 *{W},X,-",  "8E C0[H] [L]");
  addOpcode("ADDA,R3 *{W},X,-",  "8F C0[H] [L]");

  addOpcode("ADDI,R0 {B}",       "84 [L]");
  addOpcode("ADDI,R1 {B}",       "85 [L]");
  addOpcode("ADDI,R2 {B}",       "86 [L]");
  addOpcode("ADDI,R3 {B}",       "87 [L]");

  addOpcode("ADDR,R0 {W}",       "88 [D]");
  addOpcode("ADDR,R1 {W}",       "89 [D]");
  addOpcode("ADDR,R2 {W}",       "8A [D]");
  addOpcode("ADDR,R3 {W}",       "8B [D]");

  addOpcode("ADDR,R0 *{W}",      "88 80[D]");
  addOpcode("ADDR,R1 *{W}",      "89 80[D]");
  addOpcode("ADDR,R2 *{W}",      "8A 80[D]");
  addOpcode("ADDR,R3 *{W}",      "8B 80[D]");

  addOpcode("ADDZ R0",           "80");
  addOpcode("ADDZ R1",           "81");
  addOpcode("ADDZ R2",           "82");
  addOpcode("ADDZ R3",           "83");

  addOpcode("ANDA,R0 {W}",       "4C [H] [L]");
  addOpcode("ANDA,R1 {W}",       "4D [H] [L]");
  addOpcode("ANDA,R2 {W}",       "4E [H] [L]");
  addOpcode("ANDA,R3 {W}",       "4F [H] [L]");
  addOpcode("ANDA,R0 {W},X",     "4C 60[H] [L]");
  addOpcode("ANDA,R1 {W},X",     "4D 60[H] [L]");
  addOpcode("ANDA,R2 {W},X",     "4E 60[H] [L]");
  addOpcode("ANDA,R3 {W},X",     "4F 60[H] [L]");
  addOpcode("ANDA,R0 {W},X,+",   "4C 20[H] [L]");
  addOpcode("ANDA,R1 {W},X,+",   "4D 20[H] [L]");
  addOpcode("ANDA,R2 {W},X,+",   "4E 20[H] [L]");
  addOpcode("ANDA,R3 {W},X,+",   "4F 20[H] [L]");
  addOpcode("ANDA,R0 {W},X,-",   "4C 40[H] [L]");
  addOpcode("ANDA,R1 {W},X,-",   "4D 40[H] [L]");
  addOpcode("ANDA,R2 {W},X,-",   "4E 40[H] [L]");
  addOpcode("ANDA,R3 {W},X,-",   "4F 40[H] [L]");

  addOpcode("ANDA,R0 *{W}",      "4C 80[H] [L]");
  addOpcode("ANDA,R1 *{W}",      "4D 80[H] [L]");
  addOpcode("ANDA,R2 *{W}",      "4E 80[H] [L]");
  addOpcode("ANDA,R3 *{W}",      "4F 80[H] [L]");
  addOpcode("ANDA,R0 *{W},X",    "4C E0[H] [L]");
  addOpcode("ANDA,R1 *{W},X",    "4D E0[H] [L]");
  addOpcode("ANDA,R2 *{W},X",    "4E E0[H] [L]");
  addOpcode("ANDA,R3 *{W},X",    "4F E0[H] [L]");
  addOpcode("ANDA,R0 *{W},X,+",  "4C A0[H] [L]");
  addOpcode("ANDA,R1 *{W},X,+",  "4D A0[H] [L]");
  addOpcode("ANDA,R2 *{W},X,+",  "4E A0[H] [L]");
  addOpcode("ANDA,R3 *{W},X,+",  "4F A0[H] [L]");
  addOpcode("ANDA,R0 *{W},X,-",  "4C C0[H] [L]");
  addOpcode("ANDA,R1 *{W},X,-",  "4D C0[H] [L]");
  addOpcode("ANDA,R2 *{W},X,-",  "4E C0[H] [L]");
  addOpcode("ANDA,R3 *{W},X,-",  "4F C0[H] [L]");

  addOpcode("ANDI,R0 {B}",       "44 [L]");
  addOpcode("ANDI,R1 {B}",       "45 [L]");
  addOpcode("ANDI,R2 {B}",       "46 [L]");
  addOpcode("ANDI,R3 {B}",       "47 [L]");

  addOpcode("ANDR,R0 {W}",       "48 [D]");
  addOpcode("ANDR,R1 {W}",       "49 [D]");
  addOpcode("ANDR,R2 {W}",       "4A [D]");
  addOpcode("ANDR,R3 {W}",       "4B [D]");

  addOpcode("ANDR,R0 *{W}",      "48 80[D]");
  addOpcode("ANDR,R1 *{W}",      "49 80[D]");
  addOpcode("ANDR,R2 *{W}",      "4A 80[D]");
  addOpcode("ANDR,R3 *{W}",      "4B 80[D]");

  addOpcode("ANDZ R1",           "41");
  addOpcode("ANDZ R2",           "42");
  addOpcode("ANDZ R3",           "43");

  addOpcode("BCFA,0 {W}",        "9C [H] [L]");
  addOpcode("BCFA,1 {W}",        "9D [H] [L]");
  addOpcode("BCFA,2 {W}",        "9E [H] [L]");

  addOpcode("BCFA,0 *{W}",       "9C 80[H] [L]");
  addOpcode("BCFA,1 *{W}",       "9D 80[H] [L]");
  addOpcode("BCFA,2 *{W}",       "9E 80[H] [L]");

  addOpcode("BCFR,0 {W}",        "98 [D]");
  addOpcode("BCFR,1 {W}",        "99 [D]");
  addOpcode("BCFR,2 {W}",        "9A [D]");

  addOpcode("BCFR,0 *{W}",       "98 80[D]");
  addOpcode("BCFR,1 *{W}",       "99 80[D]");
  addOpcode("BCFR,2 *{W}",       "9A 80[D]");

  addOpcode("BCTA,0 {W}",        "1C [H] [L]");
  addOpcode("BCTA,1 {W}",        "1D [H] [L]");
  addOpcode("BCTA,2 {W}",        "1E [H] [L]");
  addOpcode("BCTA,3 {W}",        "1F [H] [L]");

  addOpcode("BCTA,0 *{W}",       "1C 80[H] [L]");
  addOpcode("BCTA,1 *{W}",       "1D 80[H] [L]");
  addOpcode("BCTA,2 *{W}",       "1E 80[H] [L]");
  addOpcode("BCTA,3 *{W}",       "1F 80[H] [L]");

  addOpcode("BCTR,0 {W}",        "18 [D]");
  addOpcode("BCTR,1 {W}",        "19 [D]");
  addOpcode("BCTR,2 {W}",        "1A [D]");
  addOpcode("BCTR,3 {W}",        "1B [D]");

  addOpcode("BCTR,0 *{W}",       "18 80[D]");
  addOpcode("BCTR,1 *{W}",       "19 80[D]");
  addOpcode("BCTR,2 *{W}",       "1A 80[D]");
  addOpcode("BCTR,3 *{W}",       "1B 80[D]");

  addOpcode("BRNA,R0 {W}",       "5C [H] [L]");
  addOpcode("BRNA,R1 {W}",       "5D [H] [L]");
  addOpcode("BRNA,R2 {W}",       "5E [H] [L]");
  addOpcode("BRNA,R3 {W}",       "5F [H] [L]");

  addOpcode("BRNA,R0 *{W}",       "5C 80[H] [L]");
  addOpcode("BRNA,R1 *{W}",       "5D 80[H] [L]");
  addOpcode("BRNA,R2 *{W}",       "5E 80[H] [L]");
  addOpcode("BRNA,R3 *{W}",       "5F 80[H] [L]");

  addOpcode("BRNR,R0 {W}",       "58 [D]");
  addOpcode("BRNR,R1 {W}",       "59 [D]");
  addOpcode("BRNR,R2 {W}",       "5A [D]");
  addOpcode("BRNR,R3 {W}",       "5B [D]");

  addOpcode("BRNR,R0 *{W}",      "58 80[D]");
  addOpcode("BRNR,R1 *{W}",      "59 80[D]");
  addOpcode("BRNR,R2 *{W}",      "5A 80[D]");
  addOpcode("BRNR,R3 *{W}",      "5B 80[D]");

  addOpcode("BDRA,R0 {W}",       "FC [H] [L]");
  addOpcode("BDRA,R1 {W}",       "FD [H] [L]");
  addOpcode("BDRA,R2 {W}",       "FE [H] [L]");
  addOpcode("BDRA,R3 {W}",       "FF [H] [L]");

  addOpcode("BDRA,R0 *{W}",      "FC 80[H] [L]");
  addOpcode("BDRA,R1 *{W}",      "FD 80[H] [L]");
  addOpcode("BDRA,R2 *{W}",      "FE 80[H] [L]");
  addOpcode("BDRA,R3 *{W}",      "FF 80[H] [L]");

  addOpcode("BDRR,R0 {W}",       "F8 [D]");
  addOpcode("BDRR,R1 {W}",       "F9 [D]");
  addOpcode("BDRR,R2 {W}",       "FA [D]");
  addOpcode("BDRR,R3 {W}",       "FB [D]");

  addOpcode("BDRR,R0 *{W}",      "F8 80[D]");
  addOpcode("BDRR,R1 *{W}",      "F9 80[D]");
  addOpcode("BDRR,R2 *{W}",      "FA 80[D]");
  addOpcode("BDRR,R3 *{W}",      "FB 80[D]");

  addOpcode("BIRA,R0 {W}",       "DC [H] [L]");
  addOpcode("BIRA,R1 {W}",       "DD [H] [L]");
  addOpcode("BIRA,R2 {W}",       "DE [H] [L]");
  addOpcode("BIRA,R3 {W}",       "DF [H] [L]");

  addOpcode("BIRA,R0 *{W}",      "DC 80[H] [L]");
  addOpcode("BIRA,R1 *{W}",      "DD 80[H] [L]");
  addOpcode("BIRA,R2 *{W}",      "DE 80[H] [L]");
  addOpcode("BIRA,R3 *{W}",      "DF 80[H] [L]");

  addOpcode("BIRR,R0 {W}",       "D8 [D]");
  addOpcode("BIRR,R1 {W}",       "D9 [D]");
  addOpcode("BIRR,R2 {W}",       "DA [D]");
  addOpcode("BIRR,R3 {W}",       "DB [D]");

  addOpcode("BIRR,R0 *{W}",      "D8 80[D]");
  addOpcode("BIRR,R1 *{W}",      "D9 80[D]");
  addOpcode("BIRR,R2 *{W}",      "DA 80[D]");
  addOpcode("BIRR,R3 *{W}",      "DB 80[D]");

  addOpcode("BSFA,0 {W}",        "BC [D]");
  addOpcode("BSFA,1 {W}",        "BD [D]");
  addOpcode("BSFA,2 {W}",        "BE [D]");

  addOpcode("BSFA,0 *{W}",       "BC 80[D]");
  addOpcode("BSFA,1 *{W}",       "BD 80[D]");
  addOpcode("BSFA,2 *{W}",       "BE 80[D]");

  addOpcode("BSFR,0 {W}",        "B8 [D]");
  addOpcode("BSFR,1 {W}",        "B9 [D]");
  addOpcode("BSFR,2 {W}",        "BA [D]");

  addOpcode("BSFR,0 *{W}",       "B8 80[D]");
  addOpcode("BSFR,1 *{W}",       "B9 80[D]");
  addOpcode("BSFR,2 *{W}",       "BA 80[D]");

  addOpcode("BSNA,R0 {W}",       "7C [D]");
  addOpcode("BSNA,R1 {W}",       "7D [D]");
  addOpcode("BSNA,R2 {W}",       "7E [D]");
  addOpcode("BSNA,R3 {W}",       "7F [D]");

  addOpcode("BSNA,R0 *{W}",      "7C 80[D]");
  addOpcode("BSNA,R1 *{W}",      "7D 80[D]");
  addOpcode("BSNA,R2 *{W}",      "7E 80[D]");
  addOpcode("BSNA,R3 *{W}",      "7F 80[D]");

  addOpcode("BSNR,R0 {W}",       "78 [D]");
  addOpcode("BSNR,R1 {W}",       "79 [D]");
  addOpcode("BSNR,R2 {W}",       "7A [D]");
  addOpcode("BSNR,R3 {W}",       "7B [D]");

  addOpcode("BSNR,R0 *{W}",      "78 80[D]");
  addOpcode("BSNR,R1 *{W}",      "79 80[D]");
  addOpcode("BSNR,R2 *{W}",      "7A 80[D]");
  addOpcode("BSNR,R3 *{W}",      "7B 80[D]");

  addOpcode("BSTA,0 {W}",        "3C [H] [L]");
  addOpcode("BSTA,1 {W}",        "3D [H] [L]");
  addOpcode("BSTA,2 {W}",        "3E [H] [L]");
  addOpcode("BSTA,3 {W}",        "3F [H] [L]");

  addOpcode("BSTA,0 *{W}",        "3C 80[H] [L]");
  addOpcode("BSTA,1 *{W}",        "3D 80[H] [L]");
  addOpcode("BSTA,2 *{W}",        "3E 80[H] [L]");
  addOpcode("BSTA,3 *{W}",        "3F 80[H] [L]");

  addOpcode("BSTR,0 {W}",        "38 [D]");
  addOpcode("BSTR,1 {W}",        "39 [D]");
  addOpcode("BSTR,2 {W}",        "3A [D]");
  addOpcode("BSTR,3 {W}",        "3B [D]");

  addOpcode("BSTR,0 *{W}",       "38 80[D]");
  addOpcode("BSTR,1 *{W}",       "39 80[D]");
  addOpcode("BSTR,2 *{W}",       "3A 80[D]");
  addOpcode("BSTR,3 *{W}",       "3B 80[D]");

  addOpcode("BSXA {W},X",        "BF [H] [L]");
  addOpcode("BSXA *{W},X",       "BF 80[H] [L]");

  addOpcode("BXA {W},X",         "9F [H] [L]");
  addOpcode("BXA *{W},X",        "9F 80[H] [L]");

  addOpcode("COMA,R0 {W}",       "EC [H] [L]");
  addOpcode("COMA,R1 {W}",       "ED [H] [L]");
  addOpcode("COMA,R2 {W}",       "EE [H] [L]");
  addOpcode("COMA,R3 {W}",       "EF [H] [L]");
  addOpcode("COMA,R0 {W},X",     "EC 60[H] [L]");
  addOpcode("COMA,R1 {W},X",     "ED 60[H] [L]");
  addOpcode("COMA,R2 {W},X",     "EE 60[H] [L]");
  addOpcode("COMA,R3 {W},X",     "EF 60[H] [L]");
  addOpcode("COMA,R0 {W},X,+",   "EC 20[H] [L]");
  addOpcode("COMA,R1 {W},X,+",   "ED 20[H] [L]");
  addOpcode("COMA,R2 {W},X,+",   "EE 20[H] [L]");
  addOpcode("COMA,R3 {W},X,+",   "EF 20[H] [L]");
  addOpcode("COMA,R0 {W},X,-",   "EC 40[H] [L]");
  addOpcode("COMA,R1 {W},X,-",   "ED 40[H] [L]");
  addOpcode("COMA,R2 {W},X,-",   "EE 40[H] [L]");
  addOpcode("COMA,R3 {W},X,-",   "EF 40[H] [L]");

  addOpcode("COMA,R0 *{W}",      "EC 80[H] [L]");
  addOpcode("COMA,R1 *{W}",      "ED 80[H] [L]");
  addOpcode("COMA,R2 *{W}",      "EE 80[H] [L]");
  addOpcode("COMA,R3 *{W}",      "EF 80[H] [L]");
  addOpcode("COMA,R0 *{W},X",    "EC E0[H] [L]");
  addOpcode("COMA,R1 *{W},X",    "ED E0[H] [L]");
  addOpcode("COMA,R2 *{W},X",    "EE E0[H] [L]");
  addOpcode("COMA,R3 *{W},X",    "EF E0[H] [L]");
  addOpcode("COMA,R0 *{W},X,+",  "EC A0[H] [L]");
  addOpcode("COMA,R1 *{W},X,+",  "ED A0[H] [L]");
  addOpcode("COMA,R2 *{W},X,+",  "EE A0[H] [L]");
  addOpcode("COMA,R3 *{W},X,+",  "EF A0[H] [L]");
  addOpcode("COMA,R0 *{W},X,-",  "EC C0[H] [L]");
  addOpcode("COMA,R1 *{W},X,-",  "ED C0[H] [L]");
  addOpcode("COMA,R2 *{W},X,-",  "EE C0[H] [L]");
  addOpcode("COMA,R3 *{W},X,-",  "EF C0[H] [L]");

  addOpcode("COMI,R0 {B}",       "E4 [L]");
  addOpcode("COMI,R1 {B}",       "E5 [L]");
  addOpcode("COMI,R2 {B}",       "E6 [L]");
  addOpcode("COMI,R3 {B}",       "E7 [L]");

  addOpcode("COMR,R0 {W}",       "E8 [D]");
  addOpcode("COMR,R1 {W}",       "E9 [D]");
  addOpcode("COMR,R2 {W}",       "EA [D]");
  addOpcode("COMR,R3 {W}",       "EB [D]");

  addOpcode("COMR,R0 *{W}",      "E8 80[D]");
  addOpcode("COMR,R1 *{W}",      "E9 80[D]");
  addOpcode("COMR,R2 *{W}",      "EA 80[D]");
  addOpcode("COMR,R3 *{W}",      "EB 80[D]");

  addOpcode("COMZ R0",           "E0");
  addOpcode("COMZ R1",           "E1");
  addOpcode("COMZ R2",           "E2");
  addOpcode("COMZ R3",           "E3");

  addOpcode("CPSL {B}",          "75 [L]");
  addOpcode("CPSU {B}",          "74 [L]");

  addOpcode("DAR,R0",            "94");
  addOpcode("DAR,R1",            "95");
  addOpcode("DAR,R2",            "96");
  addOpcode("DAR,R3",            "97");

  addOpcode("EORA,R0 {W}",       "2C [H] [L]");
  addOpcode("EORA,R1 {W}",       "2D [H] [L]");
  addOpcode("EORA,R2 {W}",       "2E [H] [L]");
  addOpcode("EORA,R3 {W}",       "2F [H] [L]");
  addOpcode("EORA,R0 {W},X",     "2C 60[H] [L]");
  addOpcode("EORA,R1 {W},X",     "2D 60[H] [L]");
  addOpcode("EORA,R2 {W},X",     "2E 60[H] [L]");
  addOpcode("EORA,R3 {W},X",     "2F 60[H] [L]");
  addOpcode("EORA,R0 {W},X,+",   "2C 20[H] [L]");
  addOpcode("EORA,R1 {W},X,+",   "2D 20[H] [L]");
  addOpcode("EORA,R2 {W},X,+",   "2E 20[H] [L]");
  addOpcode("EORA,R3 {W},X,+",   "2F 20[H] [L]");
  addOpcode("EORA,R0 {W},X,-",   "2C 40[H] [L]");
  addOpcode("EORA,R1 {W},X,-",   "2D 40[H] [L]");
  addOpcode("EORA,R2 {W},X,-",   "2E 40[H] [L]");
  addOpcode("EORA,R3 {W},X,-",   "2F 40[H] [L]");

  addOpcode("EORA,R0 *{W}",      "2C 80[H] [L]");
  addOpcode("EORA,R1 *{W}",      "2D 80[H] [L]");
  addOpcode("EORA,R2 *{W}",      "2E 80[H] [L]");
  addOpcode("EORA,R3 *{W}",      "2F 80[H] [L]");
  addOpcode("EORA,R0 *{W},X",    "2C E0[H] [L]");
  addOpcode("EORA,R1 *{W},X",    "2D E0[H] [L]");
  addOpcode("EORA,R2 *{W},X",    "2E E0[H] [L]");
  addOpcode("EORA,R3 *{W},X",    "2F E0[H] [L]");
  addOpcode("EORA,R0 *{W},X,+",  "2C A0[H] [L]");
  addOpcode("EORA,R1 *{W},X,+",  "2D A0[H] [L]");
  addOpcode("EORA,R2 *{W},X,+",  "2E A0[H] [L]");
  addOpcode("EORA,R3 *{W},X,+",  "2F A0[H] [L]");
  addOpcode("EORA,R0 *{W},X,-",  "2C C0[H] [L]");
  addOpcode("EORA,R1 *{W},X,-",  "2D C0[H] [L]");
  addOpcode("EORA,R2 *{W},X,-",  "2E C0[H] [L]");
  addOpcode("EORA,R3 *{W},X,-",  "2F C0[H] [L]");

  addOpcode("EORI,R0 {B}",       "24 [L]");
  addOpcode("EORI,R1 {B}",       "25 [L]");
  addOpcode("EORI,R2 {B}",       "26 [L]");
  addOpcode("EORI,R3 {B}",       "27 [L]");

  addOpcode("EORR,R0 {W}",       "28 [D]");
  addOpcode("EORR,R1 {W}",       "29 [D]");
  addOpcode("EORR,R2 {W}",       "2A [D]");
  addOpcode("EORR,R3 {W}",       "2B [D]");

  addOpcode("EORR,R0 *{W}",      "28 80[D]");
  addOpcode("EORR,R1 *{W}",      "29 80[D]");
  addOpcode("EORR,R2 *{W}",      "2A 80[D]");
  addOpcode("EORR,R3 *{W}",      "2B 80[D]");

  addOpcode("EORZ R0",           "20");
  addOpcode("EORZ R1",           "21");
  addOpcode("EORZ R2",           "22");
  addOpcode("EORZ R3",           "23");

  addOpcode("HALT",              "40");

  addOpcode("IORA,R0 {W}",       "6C [H] [L]");
  addOpcode("IORA,R1 {W}",       "6D [H] [L]");
  addOpcode("IORA,R2 {W}",       "6E [H] [L]");
  addOpcode("IORA,R3 {W}",       "6F [H] [L]");
  addOpcode("IORA,R0 {W},X",     "6C 60[H] [L]");
  addOpcode("IORA,R1 {W},X",     "6D 60[H] [L]");
  addOpcode("IORA,R2 {W},X",     "6E 60[H] [L]");
  addOpcode("IORA,R3 {W},X",     "6F 60[H] [L]");
  addOpcode("IORA,R0 {W},X,+",   "6C 20[H] [L]");
  addOpcode("IORA,R1 {W},X,+",   "6D 20[H] [L]");
  addOpcode("IORA,R2 {W},X,+",   "6E 20[H] [L]");
  addOpcode("IORA,R3 {W},X,+",   "6F 20[H] [L]");
  addOpcode("IORA,R0 {W},X,-",   "6C 40[H] [L]");
  addOpcode("IORA,R1 {W},X,-",   "6D 40[H] [L]");
  addOpcode("IORA,R2 {W},X,-",   "6E 40[H] [L]");
  addOpcode("IORA,R3 {W},X,-",   "6F 40[H] [L]");

  addOpcode("IORA,R0 *{W}",      "6C 80[H] [L]");
  addOpcode("IORA,R1 *{W}",      "6D 80[H] [L]");
  addOpcode("IORA,R2 *{W}",      "6E 80[H] [L]");
  addOpcode("IORA,R3 *{W}",      "6F 80[H] [L]");
  addOpcode("IORA,R0 *{W},X",    "6C E0[H] [L]");
  addOpcode("IORA,R1 *{W},X",    "6D E0[H] [L]");
  addOpcode("IORA,R2 *{W},X",    "6E E0[H] [L]");
  addOpcode("IORA,R3 *{W},X",    "6F E0[H] [L]");
  addOpcode("IORA,R0 *{W},X,+",  "6C A0[H] [L]");
  addOpcode("IORA,R1 *{W},X,+",  "6D A0[H] [L]");
  addOpcode("IORA,R2 *{W},X,+",  "6E A0[H] [L]");
  addOpcode("IORA,R3 *{W},X,+",  "6F A0[H] [L]");
  addOpcode("IORA,R0 *{W},X,-",  "6C C0[H] [L]");
  addOpcode("IORA,R1 *{W},X,-",  "6D C0[H] [L]");
  addOpcode("IORA,R2 *{W},X,-",  "6E C0[H] [L]");
  addOpcode("IORA,R3 *{W},X,-",  "6F C0[H] [L]");

  addOpcode("IORI,R0 {B}",       "64 [L]");
  addOpcode("IORI,R1 {B}",       "65 [L]");
  addOpcode("IORI,R2 {B}",       "66 [L]");
  addOpcode("IORI,R3 {B}",       "67 [L]");

  addOpcode("IORR,R0 {W}",       "68 [D]");
  addOpcode("IORR,R1 {W}",       "69 [D]");
  addOpcode("IORR,R2 {W}",       "6A [D]");
  addOpcode("IORR,R3 {W}",       "6B [D]");

  addOpcode("IORR,R0 *{W}",      "68 80[D]");
  addOpcode("IORR,R1 *{W}",      "69 80[D]");
  addOpcode("IORR,R2 *{W}",      "6A 80[D]");
  addOpcode("IORR,R3 *{W}",      "6B 80[D]");

  addOpcode("IORZ R0",           "60");
  addOpcode("IORZ R1",           "61");
  addOpcode("IORZ R2",           "62");
  addOpcode("IORZ R3",           "63");

  addOpcode("LODA,R0 {W}",       "0C [H] [L]");
  addOpcode("LODA,R1 {W}",       "0D [H] [L]");
  addOpcode("LODA,R2 {W}",       "0E [H] [L]");
  addOpcode("LODA,R3 {W}",       "0F [H] [L]");
  addOpcode("LODA,R0 {W},X",     "0C 60[H] [L]");
  addOpcode("LODA,R1 {W},X",     "0D 60[H] [L]");
  addOpcode("LODA,R2 {W},X",     "0E 60[H] [L]");
  addOpcode("LODA,R3 {W},X",     "0F 60[H] [L]");
  addOpcode("LODA,R0 {W},X,+",   "0C 20[H] [L]");
  addOpcode("LODA,R1 {W},X,+",   "0D 20[H] [L]");
  addOpcode("LODA,R2 {W},X,+",   "0E 20[H] [L]");
  addOpcode("LODA,R3 {W},X,+",   "0F 20[H] [L]");
  addOpcode("LODA,R0 {W},X,-",   "0C 40[H] [L]");
  addOpcode("LODA,R1 {W},X,-",   "0D 40[H] [L]");
  addOpcode("LODA,R2 {W},X,-",   "0E 40[H] [L]");
  addOpcode("LODA,R3 {W},X,-",   "0F 40[H] [L]");

  addOpcode("LODA,R0 *{W}",      "0C 80[H] [L]");
  addOpcode("LODA,R1 *{W}",      "0D 80[H] [L]");
  addOpcode("LODA,R2 *{W}",      "0E 80[H] [L]");
  addOpcode("LODA,R3 *{W}",      "0F 80[H] [L]");
  addOpcode("LODA,R0 *{W},X",    "0C E0[H] [L]");
  addOpcode("LODA,R1 *{W},X",    "0D E0[H] [L]");
  addOpcode("LODA,R2 *{W},X",    "0E E0[H] [L]");
  addOpcode("LODA,R3 *{W},X",    "0F E0[H] [L]");
  addOpcode("LODA,R0 *{W},X,+",  "0C A0[H] [L]");
  addOpcode("LODA,R1 *{W},X,+",  "0D A0[H] [L]");
  addOpcode("LODA,R2 *{W},X,+",  "0E A0[H] [L]");
  addOpcode("LODA,R3 *{W},X,+",  "0F A0[H] [L]");
  addOpcode("LODA,R0 *{W},X,-",  "0C C0[H] [L]");
  addOpcode("LODA,R1 *{W},X,-",  "0D C0[H] [L]");
  addOpcode("LODA,R2 *{W},X,-",  "0E C0[H] [L]");
  addOpcode("LODA,R3 *{W},X,-",  "0F C0[H] [L]");

  addOpcode("LODI,R0 {B}",       "04 [L]");
  addOpcode("LODI,R1 {B}",       "05 [L]");
  addOpcode("LODI,R2 {B}",       "06 [L]");
  addOpcode("LODI,R3 {B}",       "07 [L]");

  addOpcode("LODR,R0 {W}",       "08 [D]");
  addOpcode("LODR,R1 {W}",       "09 [D]");
  addOpcode("LODR,R2 {W}",       "0A [D]");
  addOpcode("LODR,R3 {W}",       "0B [D]");
  addOpcode("LODR,R0 *{W}",      "08 80[D]");
  addOpcode("LODR,R1 *{W}",      "09 80[D]");
  addOpcode("LODR,R2 *{W}",      "0A 80[D]");
  addOpcode("LODR,R3 *{W}",      "0B 80[D]");

  addOpcode("LODZ R1",           "01");
  addOpcode("LODZ R2",           "02");
  addOpcode("LODZ R3",           "03");

  addOpcode("LPSL",              "93");
  addOpcode("LPSU",              "92");

  addOpcode("NOP",               "C0");

  addOpcode("PPSL {B}",          "77 [L]");
  addOpcode("PPSU {B}",          "76 [L]");

  addOpcode("REDC,R0",           "30");
  addOpcode("REDC,R1",           "31");
  addOpcode("REDC,R2",           "32");
  addOpcode("REDC,R3",           "33");

  addOpcode("REDD,R0",           "70");
  addOpcode("REDD,R1",           "71");
  addOpcode("REDD,R2",           "72");
  addOpcode("REDD,R3",           "73");

  addOpcode("REDE,R0 {B}",       "54 [L]");
  addOpcode("REDE,R1 {B}",       "55 [L]");
  addOpcode("REDE,R2 {B}",       "56 [L]");
  addOpcode("REDE,R3 {B}",       "57 [L]");

  addOpcode("RETC,0",            "14 [D]");
  addOpcode("RETC,1",            "15 [D]");
  addOpcode("RETC,2",            "16 [D]");
  addOpcode("RETC,3",            "17 [D]");

  addOpcode("RETE,0",            "34 [D]");
  addOpcode("RETE,1",            "35 [D]");
  addOpcode("RETE,2",            "36 [D]");
  addOpcode("RETE,3",            "37 [D]");

  addOpcode("RRL,R0",            "D0");
  addOpcode("RRL,R1",            "D1");
  addOpcode("RRL,R2",            "D2");
  addOpcode("RRL,R3",            "D3");

  addOpcode("RRR,R0",            "50");
  addOpcode("RRR,R1",            "51");
  addOpcode("RRR,R2",            "52");
  addOpcode("RRR,R3",            "53");

  addOpcode("SPSL",              "13");
  addOpcode("SPSU",              "12");

  addOpcode("STRA,R0 {W}",       "CC [H] [L]");
  addOpcode("STRA,R1 {W}",       "CD [H] [L]");
  addOpcode("STRA,R2 {W}",       "CE [H] [L]");
  addOpcode("STRA,R3 {W}",       "CF [H] [L]");
  addOpcode("STRA,R0 {W},X",     "CC 60[H] [L]");
  addOpcode("STRA,R1 {W},X",     "CD 60[H] [L]");
  addOpcode("STRA,R2 {W},X",     "CE 60[H] [L]");
  addOpcode("STRA,R3 {W},X",     "CF 60[H] [L]");
  addOpcode("STRA,R0 {W},X,+",   "CC 20[H] [L]");
  addOpcode("STRA,R1 {W},X,+",   "CD 20[H] [L]");
  addOpcode("STRA,R2 {W},X,+",   "CE 20[H] [L]");
  addOpcode("STRA,R3 {W},X,+",   "CF 20[H] [L]");
  addOpcode("STRA,R0 {W},X,-",   "CC 40[H] [L]");
  addOpcode("STRA,R1 {W},X,-",   "CD 40[H] [L]");
  addOpcode("STRA,R2 {W},X,-",   "CE 40[H] [L]");
  addOpcode("STRA,R3 {W},X,-",   "CF 40[H] [L]");

  addOpcode("STRA,R0 *{W}",      "CC 80[H] [L]");
  addOpcode("STRA,R1 *{W}",      "CD 80[H] [L]");
  addOpcode("STRA,R2 *{W}",      "CE 80[H] [L]");
  addOpcode("STRA,R3 *{W}",      "CF 80[H] [L]");
  addOpcode("STRA,R0 *{W},X",    "CC E0[H] [L]");
  addOpcode("STRA,R1 *{W},X",    "CD E0[H] [L]");
  addOpcode("STRA,R2 *{W},X",    "CE E0[H] [L]");
  addOpcode("STRA,R3 *{W},X",    "CF E0[H] [L]");
  addOpcode("STRA,R0 *{W},X,+",  "CC A0[H] [L]");
  addOpcode("STRA,R1 *{W},X,+",  "CD A0[H] [L]");
  addOpcode("STRA,R2 *{W},X,+",  "CE A0[H] [L]");
  addOpcode("STRA,R3 *{W},X,+",  "CF A0[H] [L]");
  addOpcode("STRA,R0 *{W},X,-",  "CC C0[H] [L]");
  addOpcode("STRA,R1 *{W},X,-",  "CD C0[H] [L]");
  addOpcode("STRA,R2 *{W},X,-",  "CE C0[H] [L]");
  addOpcode("STRA,R3 *{W},X,-",  "CF C0[H] [L]");

  addOpcode("STRR,R0 {W}",       "C8 [D]");
  addOpcode("STRR,R1 {W}",       "C9 [D]");
  addOpcode("STRR,R2 {W}",       "CA [D]");
  addOpcode("STRR,R3 {W}",       "CB [D]");

  addOpcode("STRR,R0 *{W}",      "C8 80[D]");
  addOpcode("STRR,R1 *{W}",      "C9 80[D]");
  addOpcode("STRR,R2 *{W}",      "CA 80[D]");
  addOpcode("STRR,R3 *{W}",      "CB 80[D]");

  addOpcode("STRZ R1",           "C1");
  addOpcode("STRZ R2",           "C2");
  addOpcode("STRZ R3",           "C3");

  addOpcode("SUBA,R0 {W}",       "AC [H] [L]");
  addOpcode("SUBA,R1 {W}",       "AD [H] [L]");
  addOpcode("SUBA,R2 {W}",       "AE [H] [L]");
  addOpcode("SUBA,R3 {W}",       "AF [H] [L]");
  addOpcode("SUBA,R0 {W},X",     "AC 60[H] [L]");
  addOpcode("SUBA,R1 {W},X",     "AD 60[H] [L]");
  addOpcode("SUBA,R2 {W},X",     "AE 60[H] [L]");
  addOpcode("SUBA,R3 {W},X",     "AF 60[H] [L]");
  addOpcode("SUBA,R0 {W},X,+",   "AC 20[H] [L]");
  addOpcode("SUBA,R1 {W},X,+",   "AD 20[H] [L]");
  addOpcode("SUBA,R2 {W},X,+",   "AE 20[H] [L]");
  addOpcode("SUBA,R3 {W},X,+",   "AF 20[H] [L]");
  addOpcode("SUBA,R0 {W},X,-",   "AC 40[H] [L]");
  addOpcode("SUBA,R1 {W},X,-",   "AD 40[H] [L]");
  addOpcode("SUBA,R2 {W},X,-",   "AE 40[H] [L]");
  addOpcode("SUBA,R3 {W},X,-",   "AF 40[H] [L]");

  addOpcode("SUBA,R0 *{W}",      "AC 80[H] [L]");
  addOpcode("SUBA,R1 *{W}",      "AD 80[H] [L]");
  addOpcode("SUBA,R2 *{W}",      "AE 80[H] [L]");
  addOpcode("SUBA,R3 *{W}",      "AF 80[H] [L]");
  addOpcode("SUBA,R0 *{W},X",    "AC E0[H] [L]");
  addOpcode("SUBA,R1 *{W},X",    "AD E0[H] [L]");
  addOpcode("SUBA,R2 *{W},X",    "AE E0[H] [L]");
  addOpcode("SUBA,R3 *{W},X",    "AF E0[H] [L]");
  addOpcode("SUBA,R0 *{W},X,+",  "AC A0[H] [L]");
  addOpcode("SUBA,R1 *{W},X,+",  "AD A0[H] [L]");
  addOpcode("SUBA,R2 *{W},X,+",  "AE A0[H] [L]");
  addOpcode("SUBA,R3 *{W},X,+",  "AF A0[H] [L]");
  addOpcode("SUBA,R0 *{W},X,-",  "AC C0[H] [L]");
  addOpcode("SUBA,R1 *{W},X,-",  "AD C0[H] [L]");
  addOpcode("SUBA,R2 *{W},X,-",  "AE C0[H] [L]");
  addOpcode("SUBA,R3 *{W},X,-",  "AF C0[H] [L]");

  addOpcode("SUBI,R0 {B}",       "A4 [L]");
  addOpcode("SUBI,R1 {B}",       "A5 [L]");
  addOpcode("SUBI,R2 {B}",       "A6 [L]");
  addOpcode("SUBI,R3 {B}",       "A7 [L]");

  addOpcode("SUBR,R0 {W}",       "A8 [D]");
  addOpcode("SUBR,R1 {W}",       "A9 [D]");
  addOpcode("SUBR,R2 {W}",       "AA [D]");
  addOpcode("SUBR,R3 {W}",       "AB [D]");

  addOpcode("SUBR,R0 *{W}",      "A8 80[D]");
  addOpcode("SUBR,R1 *{W}",      "A9 80[D]");
  addOpcode("SUBR,R2 *{W}",      "AA 80[D]");
  addOpcode("SUBR,R3 *{W}",      "AB 80[D]");

  addOpcode("SUBZ R0",           "A0");
  addOpcode("SUBZ R1",           "A1");
  addOpcode("SUBZ R2",           "A2");
  addOpcode("SUBZ R3",           "A3");

  addOpcode("TMI,R0 {B}",        "F4 [L]");
  addOpcode("TMI,R1 {B}",        "F5 [L]");
  addOpcode("TMI,R2 {B}",        "F6 [L]");
  addOpcode("TMI,R3 {B}",        "F7 [L]");

  addOpcode("TPSL {B}",          "B5 [L]");
  addOpcode("TPSU {B}",          "B4 [L]");

  addOpcode("WRTC,R0",           "B0");
  addOpcode("WRTC,R1",           "B1");
  addOpcode("WRTC,R2",           "B2");
  addOpcode("WRTC,R3",           "B3");

  addOpcode("WRTD,R0",           "F0");
  addOpcode("WRTD,R1",           "F1");
  addOpcode("WRTD,R2",           "F2");
  addOpcode("WRTD,R3",           "F3");

  addOpcode("WRTE,R0 {B}",       "D4 [L]");
  addOpcode("WRTE,R1 {B}",       "D5 [L]");
  addOpcode("WRTE,R2 {B}",       "D6 [L]");
  addOpcode("WRTE,R3 {B}",       "D7 [L]");

  addOpcode("ZBRR {B}",          "9B [Z]");
  addOpcode("ZBRR *{B}",         "9B 80[Z]");
  addOpcode("ZBSR {B}",          "BB [Z]");
  addOpcode("ZBSR *{B}",         "BB 80[Z]");

  }

char* trim(char* buffer) {
  while (*buffer == ' ' || *buffer == '\t') buffer++;
  return buffer;
  }

char* nextWord(char*buffer) {
  while (*buffer != 0 && *buffer != ' ' && *buffer != '\t') buffer++;
  return trim(buffer);
  }

void writeOutput() {
  int  i;
  char buffer[256];
  char tmp[4];
  sprintf(buffer,":%04x",outAddress);
  for (i=0; i<outCount; i++) {
    sprintf(tmp," %02x",outBytes[i]);
    strcat(buffer,tmp);
    }
  fprintf(outFile,"%s\n",buffer);
  outCount = 0;
  outAddress = address;
  }

void output(byte value) {
  int  i;
  char tmp[4];
  codeGenerated++;
  address++;
  instructionBytes++;
  sprintf(tmp," %02x",value);
  strcat(listLine,tmp);
  if (instructionBytes == 4) {
    strcat(listLine,"  ");
    strcat(listLine, sourceLine);
    }
  if ((instructionBytes % 4) == 0) {
    if (pass == 2) {
      if (showList != 0) printf("%s\n",listLine);
      if (createListFile != 0) fprintf(listFile,"%s\n",listLine);
      }
    strcpy(listLine,"             ");
    }
  if (pass == 2) {
    outBytes[outCount++] = value;
    if (outCount == 16) {
      writeOutput();
      }
    }
  }

int findLabelNumber(char* name) {
  int i;
  int j;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(labelNames[i], name) == 0 &&
        strcasecmp(labelProcs[i], module) == 0)
      return i;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(labelNames[i], name) == 0 &&
        strcasecmp(labelProcs[i], "*") == 0)
      return i;
  return -1;
  }

word findLabel(char* name, char* err) {
  int i;
  int j;
  *err = 0;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(labelNames[i], name) == 0 &&
        strcasecmp(labelProcs[i], module) == 0) {
      usedLocal = -1;
      for (j=0; j<numExternals; j++)
        if (externals[j] == i) {
          usedExternal = j;
          }
      return labelValues[i];
      }
  for (i=0; i<numLabels; i++)
    if (strcasecmp(labelNames[i], name) == 0 &&
        strcasecmp(labelProcs[i], "*") == 0) {
      for (j=0; j<numExternals; j++)
        if (externals[j] == i) {
          usedExternal = j;
          }
      return labelValues[i];
      }
  if (pass == 1) return 0x0000;
  *err = 0xff;
  printf("****ERROR: Label not found: %s\n",name);
  errors++;
  return 0;
  }

int addLabel(char* name, word value) {
  int i;
  if (pass == 2) return 0;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(labelNames[i], name) == 0 &&
        strcasecmp(labelProcs[i], module) == 0) {
      printf("****ERROR: Duplicate label: %s\n",name);
      errors++;
      return -1;
      }
  numLabels++;
  if (numLabels == 1) {
    labelNames = (char**)malloc(sizeof(char*));
    labelValues = (word*)malloc(sizeof(word));
    labelProcs = (char**)malloc(sizeof(char*));
    labelLine = (int*)malloc(sizeof(int));
    }
  else {
    labelNames = (char**)realloc(labelNames,sizeof(char*)*numLabels);
    labelValues = (word*)realloc(labelValues,sizeof(word)*numLabels);
    labelProcs = (char**)realloc(labelProcs,sizeof(char*)*numLabels);
    labelLine = (int*)realloc(labelLine,sizeof(int)*numLabels);
    }
  labelNames[numLabels-1] = (char*)malloc(strlen(name)+1);
  labelProcs[numLabels-1] = (char*)malloc(strlen(module)+1);
  strcpy(labelNames[numLabels-1], name);
  strcpy(labelProcs[numLabels-1], module);
  labelValues[numLabels-1] = value;
  labelLine[numLabels-1] = lineCount;
  return 0;
  }

void setLabel(char* name, word value) {
  int i;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(labelNames[i], name) == 0) {
      labelValues[i] = value;
      return;
      }
  numLabels++;
  if (numLabels == 1) {
    labelNames = (char**)malloc(sizeof(char*));
    labelValues = (word*)malloc(sizeof(word));
    labelLine = (int*)malloc(sizeof(int));
    }
  else {
    labelNames = (char**)realloc(labelNames,sizeof(char*)*numLabels);
    labelValues = (word*)realloc(labelValues,sizeof(word)*numLabels);
    labelLine = (int*)realloc(labelLine,sizeof(int)*numLabels);
    }
  labelNames[numLabels-1] = (char*)malloc(strlen(name)+1);
  strcpy(labelNames[numLabels-1], name);
  labelValues[numLabels-1] = value;
  labelLine[numLabels-1] = lineCount;
  }

void addExternal(char* name) {
  int i;
  if (pass == 2) return;
  addLabel(name, 0);
  numExternals++;
  if (numExternals == 1)
    externals = (int*)malloc(sizeof(int));
  else
    externals = (int*)realloc(externals,sizeof(int)*numExternals);
  externals[numExternals-1] = findLabelNumber(name);
  }

void addDefine(char *def, char* value) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcmp(defines[i], def) == 0) {
      printf("****ERROR: %s is defined more than once\n");
      errors++;
      return;
      }
  numDefines++;
  if (numDefines == 1) {
    defines = (char**)malloc(sizeof(char*));
    defineValues = (char**)malloc(sizeof(char*));
    }
  else {
    defines = (char**)realloc(defines,sizeof(char*)*numDefines);
    defineValues = (char**)realloc(defineValues,sizeof(char*)*numDefines);
    }
  defines[numDefines-1] = (char*)malloc(strlen(def) + 1);
  defineValues[numDefines-1] = (char*)malloc(strlen(value) + 1);
  strcpy(defines[numDefines-1], def);
  strcpy(defineValues[numDefines-1], value);
  }

char* findDefine(char*def) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcmp(defines[i], def) == 0) {
      return defineValues[i];
      }
  return NULL;
  }

char* evaluate(char* expr, word* ret) {
  int  i;
  word nstack[256];
  int  nsp;
  byte ostack[256];
  int  osp;
  int  flag;
  char err;
  char token[128];
  int  pos;
  char isHex;
  char hexChar;
  word dec;
  word hex;
  word value;
  byte op;
  char ntype;
  *ret = 0;
  evalErrors = 0;
  usedExternal = -1;
  usedLocal = -1;
  extType = 'W';
  osp = 0;
  nsp = 0;
  flag = 0;
  if (*expr == '-') {
    nstack[nsp++] = 0;
    ostack[osp++] = OP_SUB;
    expr++;
    }
  while (flag == 0) {
    hexChar = 'N';
    isHex = 'N';
    ntype = 'W';
    dec = 0;
    hex = 0;
    while (*expr == ' ') expr++;
    while (*expr == '(') {
      ostack[osp++] = OP_OP;
      expr++;
      }
    while (*expr == ' ') expr++;
    if (*expr == '<') {
      ntype = 'L';
      expr++;
      extType = 'L';
      }
    if (*expr == '>') {
      ntype = 'H';
      expr++;
      extType = 'H';
      }
    if (*expr == '$' && 
        ((*(expr+1) >= '0' && *(expr+1) <= '9') ||
         (*(expr+1) >= 'a' && *(expr+1) <= 'f') ||
         (*(expr+1) >= 'A' && *(expr+1) <= 'F')
        )) {
      isHex = 'Y';
      expr++;
      }
    if (strncmp(expr, "[month]", 7) == 0) {
      value = buildMonth;
      expr += 7;
      }
    else if (strncmp(expr, "[day]", 5) == 0) {
      value = buildDay;
      expr += 5;
      }
    else if (strncmp(expr, "[year]", 6) == 0) {
      value = buildYear;
      expr += 6;
      }
    else if (strncmp(expr, "[hour]", 6) == 0) {
      value = buildHour;
      expr += 6;
      }
    else if (strncmp(expr, "[minute]", 8) == 0) {
      value = buildMinute;
      expr += 8;
      }
    else if (strncmp(expr, "[second]", 8) == 0) {
      value = buildSecond;
      expr += 8;
      }
    else if (strncmp(expr, "[build]", 7) == 0) {
      value = buildNumber;
      expr += 7;
      }
    else if (*expr == '$') {
      value = address;
      expr++;
      }
    else if (*expr == '%') {
      expr++;
      isHex = 'N';
      value = 0;
      while (*expr == '0' || *expr == '1' || *expr == '_') {
        if (*expr == '0') value <<= 1;
        if (*expr == '1') value = (value << 1) | 1;
        expr++;
        }
      }
    else if ((*expr >= '0' && *expr <= '9') || isHex == 'Y') {
      while ((*expr >= '0' && *expr <= '9') ||
             (*expr >= 'a' && *expr <= 'f') ||
             (*expr >= 'A' && *expr <= 'F')) {
        if (*expr >= '0' && *expr <= '9') {
          dec = (dec * 10) + (*expr - '0');
          hex = (hex * 16) + (*expr - '0');
          }
        if (*expr >= 'a' && *expr <= 'f') {
          hexChar = 'Y';
          hex = (hex * 16) + (*expr - 87);
          }
        if (*expr >= 'A' && *expr <= 'F') {
          hexChar = 'Y';
          hex = (hex * 16) + (*expr - 55);
          }
        expr++;
        }
      if (*expr == 'h' || *expr == 'H') {
        isHex = 'Y';
        expr++;
        }
      if (isHex == 'Y') {
        value = hex;
        }
      else if (hexChar == 'N') {
        value = dec;
        }
      else {
        printf("****ERROR: Expression error\n");
        *ret = 0;
        evalErrors = 1;
        return expr;
        }
      }
    else if ((*expr >= 'a' && *expr <= 'z') ||
             (*expr >= 'A' && *expr <= 'Z') ||
             *expr == '_') {
      pos = 0;
      while ((*expr >= 'a' && *expr <= 'z') ||
             (*expr >= 'A' && *expr <= 'Z') ||
             (*expr >= '0' && *expr <= '9') ||
             *expr == '_') token[pos++] = *expr++;
      token[pos] = 0;
      value = findLabel(token, &err);
      if (err != 0) evalErrors = 1;
      }
    else if (*expr == '\'') {
      expr++;
      value = *expr++;
      while (*expr != 0 && *expr != '\'') expr++;
      if (*expr == '\'') expr++;
      }
    else {
      evalErrors = 1;
      return expr;
      }
    if (ntype == 'W') nstack[nsp++] = value;
    if (ntype == 'H') nstack[nsp++] = (value >> 8) & 0xff;
    if (ntype == 'L') nstack[nsp++] = value & 0xff;
    while (*expr == ' ' || *expr == '\t') expr++;
    op = OP_CP;
    while (op == OP_CP) {
      if (*expr == 0) op = OP_END;
      else if (*expr == '+') op = OP_ADD;
      else if (*expr == '-') op = OP_SUB;
      else if (*expr == '*') op = OP_MUL;
      else if (*expr == '/') op = OP_DIV;
      else if (*expr == ')') op = OP_CP;
      else if (*expr == '<' && *(expr+1) == '<') { op = OP_SHL; expr++; }
      else if (*expr == '>' && *(expr+1) == '>') { op = OP_SHR; expr++; }
      else if (*expr == '<' && *(expr+1) == '>') { op = OP_NE; expr++; }
      else if (*expr == '<' && *(expr+1) == '=') { op = OP_LE; expr++; }
      else if (*expr == '>' && *(expr+1) == '=') { op = OP_GE; expr++; }
      else if (*expr == '&' && *(expr+1) == '&') { op = OP_LAND; expr++; }
      else if (*expr == '|' && *(expr+1) == '|') { op = OP_LOR; expr++; }
      else if (*expr == '>') op = OP_GT;
      else if (*expr == '<') op = OP_LT;
      else if (*expr == '=') op = OP_EQ;
      else if (*expr == '&') op = OP_AND;
      else if (*expr == '|') op = OP_OR;
      else if (*expr == '^') op = OP_XOR;
      else {
        op = OP_END;
        flag = 0xff;
        }
      if (*expr != 0 && op != OP_END) expr++;
      while (osp > 0 && (ostack[osp-1] & 0xf0) >= (op & 0xf0)) {
        if (ostack[osp-1] == OP_ADD) { nstack[nsp-2] += nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_SUB) { nstack[nsp-2] -= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_MUL) { nstack[nsp-2] *= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_DIV) { nstack[nsp-2] /= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_SHL) { nstack[nsp-2] <<= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_SHR) { nstack[nsp-2] >>= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_AND) { nstack[nsp-2] &= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_OR) { nstack[nsp-2] |= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_XOR) { nstack[nsp-2] ^= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_NE) { nstack[nsp-2] = nstack[nsp-2] != nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_EQ) { nstack[nsp-2] = nstack[nsp-2] == nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_GE) { nstack[nsp-2] = nstack[nsp-2] >= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_LE) { nstack[nsp-2] = nstack[nsp-2] <= nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_GT) { nstack[nsp-2] = nstack[nsp-2] > nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_LT) { nstack[nsp-2] = nstack[nsp-2] < nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_LAND) { nstack[nsp-2] = nstack[nsp-2] && nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_LOR) { nstack[nsp-2] = nstack[nsp-2] || nstack[nsp-1]; nsp--; osp--; }
        else if (ostack[osp-1] == OP_OP) {
          osp--;
          op = OP_STOP;
          }
        }
      if (op == OP_STOP) op = OP_CP;
      while (*expr == ' ' || *expr == '\t') expr++;
      }
    ostack[osp++] = op;
    if (*expr == 0) flag = 0xff;
    }
  if (nsp != 1) {
    printf("****ERROR: Expression did not reduce to single term\n");
    evalErrors = 1;
    }
  *ret = nstack[0];
  return expr;
  }

char upcase(char in) {
  if (in >= 'a' && in <= 'z') in -= 32;
  return in;
  }

int match(char* pattern, char* input) {
  int i;
  word value;
  char *temp;
  while (*pattern == ' ' || *pattern == '\t') pattern++;
  while (*input == ' ' || *input == '\t') input++;
  while (*pattern != 0) {
    while (*pattern == ' ' || *pattern == '\t') pattern++;
    while (*input == ' ' || *input == '\t') input++;
    if (strncasecmp(pattern,"{3}",3) == 0) {
      temp = evaluate(input, &value);
      if (evalErrors != 0) return 0;
      if (value >= 8) return 0;
      args[argCount++] = value;
      input = temp;
      pattern += 3;
      }
    if (strncasecmp(pattern,"{12}",4) == 0) {
      temp = evaluate(input, &value);
      if (evalErrors != 0) return 0;
      if (value >= 4096) return 0;
      args[argCount++] = value;
      input = temp;
      pattern += 4;
      }
    else if (strncasecmp(pattern,"{B}",3) == 0) {
      temp = evaluate(input, &value);
      if (evalErrors != 0) return 0;
      if (value >= 256) return 0;
      args[argCount++] = value;
      input = temp;
      pattern += 3;
      }
    else if (strncasecmp(pattern,"{N}",3) == 0) {
      temp = evaluate(input, &value);
      if (evalErrors != 0) return 0;
      if (value >= 16) return 0;
      args[argCount++] = value;
      input = temp;
      pattern += 3;
      }
    else if (strncasecmp(pattern,"{W}",3) == 0) {
      temp = evaluate(input, &value);
      if (evalErrors != 0) return 0;
      args[argCount++] = value;
      input = temp;
      pattern += 3;
      }
    else if (strncasecmp(pattern,"{5}",3) == 0) {
      temp = evaluate(input, &value);
      if (evalErrors != 0) return 0;
      if (value == 0x10) return 0;
      if ((value & 0xffe0) != 0xffe0 &&
          (value & 0xffe0) != 0x0000) return 0;
      args[argCount++] = value;
      input = temp;
      pattern += 3;
      }
    else {
      if (upcase(*pattern) != upcase(*input)) return 0;
      pattern++;
      input++;
      if (*pattern == ' ' && *input != ' ' && *input != '\t') return 0;
      }
    }
  while (*input == ' ' || *input == '\t') input++;
  if (*input == 0 || *input == ';') return -1;
  return 0;
  }

int lookupInstruction(char* input) {
  int i;
  usedExternal = -1;
  for (i=0; i<numOpcodes; i++) {
    argCount = 0;
    if (match(opcodes[i], input) != 0) return i;
    }
  return -1;
  }

void translateInstruction(char* trans) {
  int valid;
  byte b;
  word a;
  valid = 0;
  b = 0;
  while (*trans != 0) {
    if (strncasecmp(trans, "[L]", 3) == 0) {
      if (valid) output(b);
      if (usedExternal >= 0 && pass == 2) {
        if (pass == 2) fprintf(outFile,"\\%s %04x\n",labelNames[externals[usedExternal]],address);
        }
      output(args[argNumber] & 0xff);
      valid = 0;
      b = 0;
      trans += 3;
      }
    if (strncasecmp(trans, "[S]", 3) == 0) {
      if (valid) output(b);
      if (usedExternal >= 0 && pass == 2) {
        if (pass == 2) fprintf(outFile,"\\%s %04x\n",labelNames[externals[usedExternal]],address);
        }
      if ((args[argNumber] & 0xff00) != (address & 0xff00) && pass == 2) {
        printf("****ERROR: Branch out of page\n");
        errors++;
        }
      output(args[argNumber] & 0xff);
      valid = 0;
      b = 0;
      trans += 3;
      }
    else if (strncasecmp(trans, "[H]", 3) == 0) {
      if (usedExternal >= 0 && pass == 2) {
        if (pass == 2) fprintf(outFile,"/%s %04x %02x\n",labelNames[externals[usedExternal]],address,args[argNumber] & 0xff);
        }
      b |= (args[argNumber] >> 8);
      valid = -1;
      trans += 3;
      }
    else if (strncasecmp(trans, "<N", 2) == 0) {
      b |= (args[argNumber] << 1);
      valid = -1;
      trans += 2;
      }
    else if (strncasecmp(trans, "|H", 2) == 0) {
      b |= (args[argNumber] & 0xf00) >> 8;
      valid = -1;
      trans += 2;
      }
    else if (strncasecmp(trans, "|N", 2) == 0) {
      b |= (args[argNumber] & 0xf);
      valid = -1;
      trans += 2;
      }
    else if (strncasecmp(trans, "[Q]", 3) == 0) {
      if (valid) output(b);
      output(args[argNumber] >> 8);
      output(args[argNumber] & 0xff);
      output(args[argNumber+1] >> 8);
      output(args[argNumber+1] & 0xff);
      valid = 0;
      trans += 3;
      }
    else if (strncasecmp(trans, "[BT]", 4) == 0) {
      b |= ((args[argNumber] & 0x7) << 3) | (args[argNumber+1] & 0x7);
      valid = -1;
      trans += 4;
      }
    else if (strncasecmp(trans, "[TF]", 4) == 0) {
      if (valid) output(b);
      b |= (args[argNumber] << 4) | args[argNumber+1];
      valid = -1;
      trans += 4;
      }
    else if (strncasecmp(trans, "[DW]", 4) == 0) {
      if (valid) output(b);
      if (usedExternal >= 0 && pass == 2) {
        fprintf(outFile,"?%s %04x\n",labelNames[externals[usedExternal]],address);
        printf("???WARNING: Using relative addresses as EXTRN will likely not produce the expected result\n");
        }
      a = args[argNumber] - (address+2);
      output(a >> 8);
      output(a & 0xff);
      valid = 0;
      b = 0;
      trans += 4;
      }
    else if (strncasecmp(trans, "[D]", 3) == 0) {
      if (usedExternal >= 0 && pass == 2) {
        fprintf(outFile,"\\%s %04x\n",labelNames[externals[usedExternal]],address);
        printf("???WARNING: Using relative addresses as EXTRN will likely not produce the expected result\n");
        }
      a = args[argNumber] - (address+1);
      a = a & 0x7f;
      valid = -1;
      b |= a;
      trans += 3;
      }
    else if (strncasecmp(trans, "[Z]", 3) == 0) {
      if (usedExternal >= 0 && pass == 2) {
        fprintf(outFile,"\\%s %04x\n",labelNames[externals[usedExternal]],address);
        printf("???WARNING: Using relative addresses as EXTRN will likely not produce the expected result\n");
        }
      a = args[argNumber] - 0;
      a = a & 0x7f;
      valid = -1;
      b |= a;
      trans += 3;
      }
    else if (strncasecmp(trans, "[W]", 3) == 0) {
      if (valid) output(b);
      if (usedExternal >= 0 && pass == 2) {
        if (pass == 2) fprintf(outFile,"?%s %04x\n",labelNames[externals[usedExternal]],address);
        }
      if (usedLocal >= 0 && pass == 2) {
        fixups[numFixups] = address;
        fixupTypes[numFixups] = 'W';
        fixupLowOffset[numFixups] = 0;
        numFixups++;
        }
      output(args[argNumber] >> 8);
      output(args[argNumber] & 0xff);
      valid = 0;
      b = 0;
      trans += 3;
      }
    else if (strncasecmp(trans, "[5]", 3) == 0) {
      if (valid) b <<= 4;
      b |= (args[argNumber] & 0x1f);
      output(b);
      valid = 0;
      b = 0;
      trans += 3;
      }
    else if (*trans >= '0' && *trans <= '9') {
      b = (b << 4) | (*trans - '0');
      valid = -1;
      trans++;
      }
    else if (*trans >= 'a' && *trans <= 'f') {
      b = (b << 4) | (*trans - 87);
      valid = -1;
      trans++;
      }
    else if (*trans >= 'A' && *trans <= 'F') {
      b = (b << 4) | (*trans - 55);
      valid = -1;
      trans++;
      }
    else if (*trans == '+') {
      if (valid) output(b);
      b = 0;
      valid = 0;
      argNumber++;
      trans++;
      }
    else if (*trans == ' ') {
      if (valid) output(b);
      b = 0;
      valid = 0;
      trans++;
      }
    }
  if (valid) output(b);
  }

void defReplace(char* line) {
  char  buffer[1024];
  char *pchar;
  int i;
  for (i=0; i<numDefines; i++) {
    while ((pchar = strstr(line, defines[i])) != NULL) {
      strncpy(buffer,line,pchar-line);
      buffer[pchar-line] = 0;
      strcat(buffer,defineValues[i]);
      strcat(buffer,pchar+strlen(defines[i]));
      strcpy(line,buffer);
      }
    }
  }

char* nextLine(char* line) {
  int   i;
  char* ret;
  int   flag;
  char  buffer[1024];
  int   pos;
  char *pchar;
  word  value;
  flag = -1;
  while (flag) {
    ret = fgets(line, 1024, sourceFile[fileNumber]);
    lineCount++;
    lineNumber[fileNumber]++;
    if (ret != NULL) {
      while (strlen(ret) > 0 && line[strlen(ret)-1] <= ' ')
        line[strlen(ret)-1] = 0;
      flag = 0;
      if (*ret == '#') {
        if (fileNumber == 0)
          sprintf(listLine,"[%05d] ",lineNumber[fileNumber]);
        else
          sprintf(listLine,"<%05d> ",lineNumber[fileNumber]);
        while (strlen(listLine) < 25) strcat(listLine," ");
        strcat(listLine,"  ");
        strcat(listLine,ret);
        if (pass == 2) {
          if (showList != 0) printf("%s\n",listLine);
          if (createListFile != 0) fprintf(listFile,"%s\n",listLine);
          }
        flag = -1;
        if (strncmp(ret,"#include ",9) == 0) {
          ret += 9;
          while (*ret == ' ' || *ret == '\t') ret++;
          pos = 0;
          while (*ret != 0 && *ret > ' ')
            buffer[pos++] = *ret++;
          buffer[pos] = 0;
          fileNumber++;
          lineNumber[fileNumber] = 0;
          sourceFile[fileNumber] = fopen(buffer,"r");
          if (sourceFile[fileNumber] == NULL) {
            }
          }
        if (strncmp(ret,"#define ",8) == 0) {
          ret += 8;
          while (*ret == ' ' || *ret == '\t') ret++;
          pos = 0;
          while (*ret != 0 && *ret > ' ')
            buffer[pos++] = *ret++;
          buffer[pos] = 0;
          while (*ret == ' ' || *ret == '\t') ret++;
          if (*ret == 0) addDefine(buffer,"1");
            else addDefine(buffer, ret);
          }
        if (strncmp(ret,"#ifdef ",7) == 0) {
          ret += 7;
          while (*ret == ' ' || *ret == '\t') ret++;
          pos = 0;
          while (*ret != 0 && *ret > ' ')
            buffer[pos++] = *ret++;
          buffer[pos] = 0;
          pchar = findDefine(buffer);
          if (pchar != NULL) {
            numNests++;
            nests[numNests] = 'Y';
            }
          else {
            numNests++;
            nests[numNests] = 'N';
            }
          }
        if (strncmp(ret,"#ifndef ",8) == 0) {
          ret += 8;
          while (*ret == ' ' || *ret == '\t') ret++;
          pos = 0;
          while (*ret != 0 && *ret > ' ')
            buffer[pos++] = *ret++;
          buffer[pos] = 0;
          pchar = findDefine(buffer);
          if (pchar != NULL) {
            numNests++;
            nests[numNests] = 'N';
            }
          else {
            numNests++;
            nests[numNests] = 'Y';
            }
          }
        if (strncmp(ret,"#if ",4) == 0) {
          ret += 4;
          while (*ret == ' ' || *ret == '\t') ret++;
          defReplace(ret);
          evaluate(ret, &value);
          if (value != 0) {
            numNests++;
            nests[numNests] = 'Y';
            }
          else {
            numNests++;
            nests[numNests] = 'N';
            }
          }
        if (strncmp(ret,"#endif",6) == 0) {
          if (numNests > 0) numNests--;
          else {
            printf("Error: Unmatched #endif\n");
            errors++;
            }
          }
        if (strncmp(ret,"#else",5) == 0) {
          if (numNests > 0)
            nests[numNests] = (nests[numNests] == 'Y') ? 'N' : 'Y';
          else {
            printf("Error: Unmatched #else\n");
            errors++;
            }
          }
        }
      else if (nests[numNests] != 'Y') {
        flag = -1;
        }
      else {
        defReplace(ret);
        }
      }
    else {
      if (fileNumber == 0) flag = 0;
      else {
        fclose(sourceFile[fileNumber]);
        fileNumber--;
        flag = -1;
        }
      }
    }
  return ret;
  }

int assemblyPass(char* sourceName) {
  int  o;
  int  i;
  word value;
  char *pchar;
  char *pline;
  char  err;
  FTOI ftoi;
  char line[1024];
  sourceFile[0] = fopen(sourceName, "r");
  if (sourceFile[0] == NULL) {
    printf("Error: Could not open: %s\n",sourceName);
    return -1;
    }
  lineNumber[0] = 0;
  fileNumber = 0;
  lineCount = 0;
  address = 0;
  outCount = 0;
  outAddress = 0;
  codeGenerated = 0;
  numDefines = 0;
  nests[0] = 'Y';
  numNests = 0;
  strcpy(module,"*");
  inProc = 0;
  while (nextLine(line)) {
    strcpy(sourceLine, line);
    if (strncmp(line,".list",5) == 0) showList = -1;
    if (strncmp(line,".sym",4) == 0) showSymbols = -1;
    if (strncmp(line,".link ",6) == 0) {
      if (pass == 2) {
        fprintf(outFile,"%s\n",line+6);
        }
      }
    if (strncmp(line,".sym",4) == 0) showSymbols = -1;
    if (strncmp(line,".align word", 11) == 0) {
      if (outCount != 0) writeOutput();
      address = (address + 1) & 0xfffe;
      outAddress = address;
      }
    if (strncmp(line,".align dword", 12) == 0) {
      if (outCount != 0) writeOutput();
      address = (address + 3) & 0xfffc;
      outAddress = address;
      }
    if (strncmp(line,".align qword", 12) == 0) {
      if (outCount != 0) writeOutput();
      address = (address + 7) & 0xfff8;
      outAddress = address;
      }
    if (strncmp(line,".align para", 11) == 0) {
      if (outCount != 0) writeOutput();
      address = (address + 15) & 0xfff0;
      outAddress = address;
      }
    if (strncmp(line,".align 32", 9) == 0) {
      if (outCount != 0) writeOutput();
      address = (address + 31) & 0xffe0;
      outAddress = address;
      }
    if (strncmp(line,".align 64", 9) == 0) {
      if (outCount != 0) writeOutput();
      address = (address + 63) & 0xffc0;
      outAddress = address;
      }
    if (strncmp(line,".align 128", 10) == 0) {
      if (outCount != 0) writeOutput();
      address = (address + 127) & 0xff80;
      outAddress = address;
      }
    if (strncmp(line,".align page", 11) == 0) {
      if (outCount != 0) writeOutput();
      address = (address + 255) & 0xff00;
      outAddress = address;
      }
    if (line[0] == '.') strcpy(line,"");
    pchar = strchr(line, ';');
    if (pchar != NULL) {
      *pchar = 0;
      while (strlen(line) > 0 && line[strlen(line)-1] <= ' ')
        line[strlen(line)-1] = 0;
      }
    pline = line;
    if (*pline != 0 && *pline != ' ' && *pline != '\t') {
      i = 0;
      while (*pline != ' ' && *pline != '\t' && *pline != ':' && *pline != 0)
        label[i++] = *pline++;
      label[i] = 0;
      }
    else strcpy(label, "");
    if (*pline == ':') pline++;
    while (*pline != 0 && *pline <= ' ') pline++;
    if (strlen(label) > 0 || strlen(pline) > 0) {
      if (fileNumber == 0)
        sprintf(listLine,"[%05d] %04x:",lineNumber[fileNumber],address);
      else
        sprintf(listLine,"<%05d> %04x:",lineNumber[fileNumber],address);
      if (strlen(label) > 0) addLabel(label, address);

      instructionBytes = 0;
      if (strlen(pline) > 0) {
        if (strncasecmp(pline,"org",3) == 0) {
          if (outCount != 0) writeOutput();
          pline = nextWord(pline);
          evaluate(pline, &address);
          outAddress = address;
          }
        else if (strncasecmp(pline,"extrn",5) == 0) {
          pline = nextWord(pline);
          addExternal(pline);
          }
        else if (strncasecmp(pline,"proc",4) == 0) {
          if (inProc) {
            printf("***Error: PROC encountered inside of another PROC %s\n",pline);
            errors++;
            }
          else {
            pline = nextWord(pline);
            if (outCount != 0) writeOutput();
            address = 0;
            outAddress = 0;
            inProc = -1;
            strcpy(module, pline);
            if (pass == 1) addLabel(pline, 0);
            if (pass == 2) {
              fprintf(outFile,"{%s\n",pline);
              }
            numFixups = 0;
            }
          }
        else if (strcasecmp(pline,"endp") == 0) {
          if (inProc == 0) {
            printf("***ERROR: ENDP encountered outside PROC\n");
            errors++;
            }
          inProc = 0;
          if (outCount != 0) writeOutput();
          if (pass == 2) {
            for (i=0; i<numFixups; i++) {
              if (fixupTypes[i] == 'W')
                fprintf(outFile,"+%04x\n",fixups[i]);
              if (fixupTypes[i] == 'H') {
                if (fixupLowOffset[i] != 0)
                  fprintf(outFile,"^%04x %02x\n",fixups[i],fixupLowOffset[i]);
                else
                  fprintf(outFile,"^%04x\n",fixups[i]);
                }
              if (fixupTypes[i] == 'L')
                fprintf(outFile,"v%04x\n",fixups[i]);
              }
            fprintf(outFile,"}\n");
            }
          }
        else if (strncasecmp(pline,"public",6) == 0) {
          if (pass == 2) {
            pline = nextWord(pline);
            i = findLabelNumber(pline);
            if (i < 0) {
              printf("****ERROR: Symbol not found: %s\n",pline);
              errors++;
              }
            else {
              numPublics++;
              if (numPublics == 1)
                publics = (int*)malloc(sizeof(int));
              else
                publics = (int*)realloc(publics,sizeof(int)*numPublics);
              publics[numPublics-1] = i;
              }
            }
          }
        else if (strncasecmp(pline,"ds",2) == 0) {
          if (outCount != 0) writeOutput();
          pline = nextWord(pline);
          evaluate(pline, &value);
          address += value;
          outAddress = address;
          }
        else if (strncasecmp(pline,"db",2) == 0 ||
                 strncasecmp(pline,".byte",5) == 0 ||
                 strncasecmp(pline,"byte",4) == 0) {
          pline = nextWord(pline);
          pchar = pline;
          while (*pchar != 0) {
            if (*pchar == '"') {
              pchar++;
              while (*pchar != 0 && *pchar != '"') {
                output(*pchar);
                pchar++;
                }
              if (*pchar == '"') pchar++;
              }
            else {
              pchar = evaluate(pchar, &value);
              output(value & 0xff);
              }
            while (*pchar == ' ') pchar++;
            if (*pchar == ',') pchar++;
            while (*pchar == ' ') pchar++;
            }
          }
        else if (strncasecmp(pline,"dw",2) == 0 ||
                 strncasecmp(pline,"word",4) == 0 ||
                 strncasecmp(pline,".word",5) == 0) {
          pline = nextWord(pline);
          pchar = pline;
          while (*pchar != 0) {
            pchar = evaluate(pchar, &value);
            output((value >> 8) & 0xff);
            output(value & 0xff);
            while (*pchar == ' ') pchar++;
            if (*pchar == ',') pchar++;
            while (*pchar == ' ') pchar++;
            }
          }
        else if (strncasecmp(pline,"df",2) == 0) {
          pline = nextWord(pline);
          ftoi.f = atof(pline);
          output((ftoi.i >> 24) & 0xff);
          output((ftoi.i >> 16) & 0xff);
          output((ftoi.i >> 8) & 0xff);
          output(ftoi.i & 0xff);
          }
        else if (strncasecmp(pline,"end",3) == 0) {
          if (outCount != 0) writeOutput();
          pline = nextWord(pline);
          evaluate(pline, &startAddress);
          }
        else if (strncasecmp(pline,"equ",3) == 0 ||
                 strncasecmp(pline,".equ",4) == 0) {
          pline = nextWord(pline);
          evaluate(pline, &value);
          if (strlen(label) > 0) setLabel(label, value);
          }
        else {
          indexNumber = 0xffff;
          o = lookupInstruction(pline);
          if (o >= 0) {
            argNumber = 0;
            translateInstruction(translations[o]);
            }
          else {
            printf("****ERROR: Invalid instruction\n");
            printf("   [%05d] %s\n",lineCount,sourceLine);
            errors++;
            }
          }
        }
      if (instructionBytes < 4) {
        while (strlen(listLine) < 25) strcat(listLine," ");
        strcat(listLine,"  ");
        strcat(listLine,sourceLine);
        }
      if (instructionBytes < 4 || ((instructionBytes % 4) != 0) && instructionBytes != 4)
        if (pass == 2) {
          if (showList != 0) printf("%s\n",listLine);
          if (createListFile != 0) fprintf(listFile,"%s\n",listLine);
          }
      }
    else {
      if (fileNumber == 0)
        sprintf(listLine,"[%05d] ",lineNumber[fileNumber]);
      else
        sprintf(listLine,"<%05d> ",lineNumber[fileNumber]);
      while (strlen(listLine) < 27) strcat(listLine," ");
      strcat(listLine, sourceLine);
      if (pass == 2) {
        if (showList != 0) printf("%s\n",listLine);
        if (createListFile != 0) fprintf(listFile,"%s\n",listLine);
        }
      }
    }
  while (fileNumber > 0) {
    fclose(sourceFile[fileNumber--]);
    }
  fclose(sourceFile[0]);
  for (i=0; i<numDefines; i++) {
    free(defines[i]);
    free(defineValues[i]);
    }
  if (numDefines > 0) {
    free(defines);
    free(defineValues);
    }
  return errors;
  }

void assembleFile(char* sourceName) {
  int   i;
  char *pchar;
  char buffer[1024];
  char tmp[1024];
  FILE *buildFile;
  strcpy(baseName, sourceName);
  pchar = strchr(baseName,'.');
  if (pchar != NULL) *pchar = 0;
  strcpy(listName, baseName);
  strcat(listName, ".lst");
  strcpy(outName, baseName);
  strcat(outName, ".prg");

  printf("Source file: %s\n",sourceName);
  errors = 0;
  numLabels = 0;
  numExternals = 0;
  numReferences = 0;
  numPublics = 0;
  startAddress = 0xffff;

  strcpy(tmp, baseName);
  strcat(tmp,".build");
  buildFile = fopen(tmp, "r");
  if (buildFile == NULL) {
    buildNumber = 1;
    }
  else {
    fgets(buffer, 32, buildFile);
    buildNumber = atoi(buffer) + 1;
    fclose(buildFile);
    }
  buildFile = fopen(tmp,"w");
  fprintf(buildFile,"%d\n",buildNumber);
  fclose(buildFile);

  pass = 1;
  if (assemblyPass(sourceName) != 0) {
    printf("Errors encountered. Assembly aborted\n");
    }
  else {
    pass = 2;
    outFile = fopen(outName, "w");
    fprintf(outFile,".big\n");
    if (createListFile != 0) listFile = fopen(listName, "w");
    assemblyPass(sourceName);
    if (outBytes > 0) writeOutput();
    if (startAddress != 0xffff)
      fprintf(outFile,"@%04x\n",startAddress);
    if (numReferences > 0) {
      for (i=0; i<numReferences; i++) {
        fprintf(outFile,"?%s %04x\n",externals[references[i]],referenceAddress[i]);
        }
      }
    if (numPublics > 0) {
      for (i=0; i<numPublics; i++) {
        fprintf(outFile,"=%s %04x\n",labelNames[publics[i]],labelValues[publics[i]]);
        }
      }
    fclose(outFile);
    if (showSymbols != 0) {
      printf("\n");
      if (createListFile) fprintf(listFile,"\n");
      for (i=0; i<numLabels; i++) {
        sprintf(buffer,"%-16s %-16s %04x <%05d> \n",labelNames[i],labelProcs[i],labelValues[i],labelLine[i]);
        printf("%s",buffer);
        if (createListFile) fprintf(listFile,"%s",buffer);
        }
      printf("\n");
      if (createListFile) fprintf(listFile,"\n");
      }
    }
  printf("Lines assembled: %d\n",lineCount);
  printf("Errors         : %d\n",errors);
  printf("Code generated : %d\n",codeGenerated);
  if (createListFile != 0 && pass == 2) {
    fprintf(listFile,"Lines assembled: %d\n",lineCount);
    fprintf(listFile,"Errors         : %d\n",errors);
    fprintf(listFile,"Code generated : %d\n",codeGenerated);
    }
  if (createListFile != 0 && pass == 2) fclose(listFile);
  printf("\n");
  for (i=0; i<numLabels; i++) {
    free(labelNames[i]);
    }
  if (numExternals > 0) free(externals);
  if (numPublics > 0) free(publics);
  if (numReferences > 0) {
    free(references);
    free(referenceAddress);
    }
  if (numLabels > 0) {
    free(labelNames);
    free(labelValues);
    free(labelLine);
    }
  }

int main(int argc, char **argv) {
  int i;
  time_t tv;
  struct tm dt;
  printf("Asm/2650 1.0 by Michael H. Riley\n\n");
  initOpcodes();
  showList = 0;
  showSymbols = 0;
  createListFile = 0;
  numSourceFiles = 0;
  tv = time(NULL);
  localtime_r(&tv, &dt);
  buildMonth = dt.tm_mon + 1;
  buildDay = dt.tm_mday;
  buildYear = dt.tm_year + 1900;
  buildHour = dt.tm_hour;
  buildMinute = dt.tm_min;
  buildSecond = dt.tm_sec;
  for (i=1; i<argc; i++) {
    if (strcmp(argv[i],"-l") == 0) showList = -1;
    else if (strcmp(argv[i],"-L") == 0) createListFile = -1;
    else if (strcmp(argv[i],"-s") == 0) showSymbols = -1;
    else {
      numSourceFiles++;
      if (numSourceFiles == 1)
        sourceNames = (char**)malloc(sizeof(char*));
      else
        sourceNames = (char**)realloc(sourceNames,sizeof(char*) * numSourceFiles);
      sourceNames[numSourceFiles-1] = (char*)malloc(strlen(argv[i])+1);
      strcpy(sourceNames[numSourceFiles-1], argv[i]);
      }
    }
  if (numSourceFiles == 0) {
    printf("No source file specified\n");
    exit(1);
    }
  for (i=0; i<numSourceFiles; i++)
    assembleFile(sourceNames[i]);
  return 0;
  }

