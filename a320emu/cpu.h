#ifndef __CPU__
#define __CPU__

#include <stdint.h>
#include "mem.h"

typedef uint32_t reg;

typedef struct{
  uint32_t funct:6;
  uint32_t shamt:5;
  uint32_t rd:5;
  uint32_t rt:5;
  uint32_t rs:5;
  uint32_t opcode:6;
}rtype_inst;

typedef struct{
  uint32_t imm:16;
  uint32_t rt:5;
  uint32_t rs:5;
  uint32_t opcode:6;
}itype_inst;

typedef struct{
  uint32_t addr:26;
  uint32_t opcode:6;
}jtype_inst;

typedef union{
  rtype_inst rtype;
  itype_inst itype;
  jtype_inst jtype;
  int16_t chunks16[2];
  uint32_t bits;
}inst;

typedef struct{
  reg R[32];  
  reg RHI;
  reg RLO;
  reg pc;
}cpu;

void run_app(cpu*, int, int);
void mult(reg, reg, reg*, reg*);
void init_cpu(cpu*);
void print_string(cpu*);
void sys_call(cpu*);

#endif

