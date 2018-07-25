#ifndef __CPU__
#define __CPU__

  #include <stdint.h>

  typedef uint32_t reg_t;

  typedef struct{
    uint32_t funct:6;
    uint32_t shamt:5;
    uint32_t rd:5;
    uint32_t rt:5;
    uint32_t rs:5;
    uint32_t opcode:6;
  }rtype_inst_t;

  typedef struct{
    uint32_t imm:16;
    uint32_t rt:5;
    uint32_t rs:5;
    uint32_t opcode:6;
  }itype_inst_t;

  typedef struct{
    uint32_t addr:26;
    uint32_t opcode:6;
  }jtype_inst_t;

  typedef union{
    rtype_inst_t rtype;
    itype_inst_t itype;
    jtype_inst_t jtype;
    int16_t chunks16[2];
    uint32_t bits;
  }inst_t;

  typedef struct{
    reg_t R[32];  
    reg_t RHI;
    reg_t RLO;
    reg_t pc;
  }cpu_t;

  void run_app(cpu_t*, int, int);
  void mult(reg_t, reg_t, reg_t*, reg_t*);
  void init_cpu(cpu_t*);
  void print_string(cpu_t*);
  void sys_call(cpu_t*);

#endif

