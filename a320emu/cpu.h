#ifndef __CPU__
#define __CPU__

  #include <stdint.h>

  #define R0      0
  #define R1      1
  #define R2      2
  #define R3      3
  #define R4      4
  #define R5      5
  #define R6      6
  #define R7      7
  #define R8      8
  #define R9      9
  #define R10     10
  #define R11     11
  #define R12     12
  #define R13     13
  #define R14     14
  #define R15     15
  #define R16     16
  #define R17     17
  #define R18     18
  #define R19     19
  #define R20     20
  #define R21     21
  #define R22     22
  #define R23     23
  #define R24     24
  #define R25     25
  #define R26     26
  #define R27     27
  #define R28     28
  #define R29     29
  #define R30     30
  #define R31     31
  #define HI      32
  #define LO      33
  #define PC      34
  #define EPC     35

  #define ZERO    R0
  #define AT      R1
  #define V0      R2
  #define V1      R3
  #define A0      R4
  #define A1      R5
  #define A2      R6
  #define A3      R7
  #define T0      R8
  #define T1      R9
  #define T2      R10
  #define T3      R11
  #define T4      R12
  #define T5      R13
  #define T6      R14
  #define T7      R15
  #define S0      R16
  #define S1      R17
  #define S2      R18
  #define S3      R19
  #define S4      R20
  #define S5      R21
  #define S6      R22
  #define S7      R23
  #define T8      R24
  #define T9      R25
  #define K0      R26
  #define K1      R27
  #define GP      R28
  #define SP      R29
  #define S8      R30
  #define RA      R31

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
    reg_t R[36];
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

