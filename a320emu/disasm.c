#include <stdio.h>
#include <stdlib.h>
#include "disasm.h"

void disasm(inst inst)
{
	switch(inst.rtype.opcode){
	case 0x0:
		switch(inst.rtype.funct){
		case 0x0:
			printf("sll\t$%d,$%d,%u\n", inst.rtype.rd, inst.rtype.rt, inst.rtype.shamt);
			break;

		case 0x2:
			printf("srl\t$%d,$%d,%u\n", inst.rtype.rd, inst.rtype.rt, inst.rtype.shamt);
			break;

		case 0x3:
			printf("sra\t$%d,$%d,%u\n", inst.rtype.rd, inst.rtype.rt, inst.rtype.shamt);
			break;

		case 0x4:
			printf("sllv\t$%d,$%d,$%d\n", inst.rtype.rd, inst.rtype.rt, inst.rtype.rs);
			break;

		case 0x6:
			printf("srlv\t$%d,$%d,$%d\n", inst.rtype.rd, inst.rtype.rt, inst.rtype.rs);
			break;

		case 0x8:
			printf("jr\t$%d\n", inst.rtype.rs);
			break;

		case 0x9:
			printf("jalr\t$%d,$%d\n",inst.rtype.rd, inst.rtype.rs);
			break;

		case 0x10:
			printf("mfhi\t$%d\n", inst.rtype.rd);
			break;

		case 0x12:
			printf("mflo\t$%d\n", inst.rtype.rd);
			break;

		case 0x18:
			printf("mult\t$%d,$%d\n", inst.rtype.rs, inst.rtype.rt);
			break;

		case 0x21:
			printf("addu\t$%d,$%d,$%d\n",inst.rtype.rd, inst.rtype.rs, inst.rtype.rt);
			break;

		case 0x23:
			printf("subu\t$%d,$%d,$%d\n",inst.rtype.rd, inst.rtype.rs, inst.rtype.rt);
			break;

		case 0x24:
			printf("and\t$%d,$%d,$%d\n",inst.rtype.rd, inst.rtype.rs, inst.rtype.rt);
			break;

		case 0x26:
			printf("xor\t$%d,$%d,$%d\n",inst.rtype.rd, inst.rtype.rs, inst.rtype.rt);
			break;

		case 0x27:
			printf("nor\t$%d,$%d,$%d\n",inst.rtype.rd, inst.rtype.rs, inst.rtype.rt);
			break;

		case 0x2a:
			printf("slt\t$%d,$%d,$%d\n",inst.rtype.rd, inst.rtype.rs, inst.rtype.rt);
			break;

		case 0x2b:
			printf("sltu\t$%d,$%d,$%d\n",inst.rtype.rd, inst.rtype.rs, inst.rtype.rt);
			break;

		case 0xc: // funct == 0xc (SYSCALL)
			printf("syscall\n");
			break;

		case 0x25: // funct == 0x25 (OR)
			printf("or\t$%d,$%d,$%d\n", inst.rtype.rd, inst.rtype.rs, inst.rtype.rt);
			break;

		default: // undefined funct
			printf("%s: illegal instruction(func): %08x\n", __func__, inst.rtype.funct);
			exit(-1);
			break;
		}
		break;

  case 0x1:
    switch(inst.itype.rt){
    case 0x00:
      printf("bltz\t$%d,%d\n", inst.itype.rs, (int16_t) inst.itype.imm*4);
      break;
    case 0x01:
      printf("bgez\t$%d,%d\n", inst.itype.rs, (int16_t) inst.itype.imm*4);
      break;
    case 0x11:
      printf("bgezal\t$%d,%d\n", inst.itype.rs, (int16_t) inst.itype.imm*4);
      break;
		default: // undefined branch
			printf("%s: illegal instruction(branch): %08x(%08x)\n", __func__, inst.bits, inst.itype.rt);
			exit(-1);
			break;
    }
    break;

  case 0x4:
    printf("beq\t$%d,$%d,%d\n", inst.itype.rs, inst.itype.rt, (int16_t) inst.itype.imm*4);
    break;

  case 0x5:
    printf("bne\t$%d,$%d,%d\n", inst.itype.rs, inst.itype.rt, (int16_t) inst.itype.imm*4);
    break;

  case 0x6:
    printf("blez\t$%d,%d\n", inst.itype.rs, (int16_t) inst.itype.imm*4);
    break;

  case 0x8:
    printf("addi\t$%d,$%d,%d\n", inst.itype.rt, inst.itype.rs, (int16_t) inst.itype.imm);
    break;

  case 0x9:
    printf("addiu\t$%d,$%d,%d\n", inst.itype.rt, inst.itype.rs, (int16_t) inst.itype.imm);
    break;

  case 0xa:
    printf("slti\t$%d.$%d,%d\n", inst.itype.rs, inst.itype.rt, (int16_t) inst.itype.imm);
    break;

  case 0xb:
    printf("sltiu\t$%d,$%d,%d\n", inst.itype.rs, inst.itype.rt, inst.itype.imm);
    break;

  case 0xc:
    printf("andi\t$%d,$%d,0x%x\n", inst.itype.rs, inst.itype.rt, inst.itype.imm);
    break;

  case 0xe:
    printf("xori\t$%d,$%d,0x%x\n", inst.itype.rt, inst.itype.rs, inst.itype.imm);
    break;

  case 0xf:
    printf("lui\t$%d,0x%x\n", inst.itype.rt, inst.itype.imm);
    break;

  case 0x20:
    printf("lb\t$%d,%d($%d)\n", inst.itype.rt, (int16_t) inst.itype.imm, inst.itype.rs);
    break;

  case 0x21:
    printf("lh\t$%d,%d($%d)\n", inst.itype.rt, (int16_t) inst.itype.imm, inst.itype.rs);
    break;

  case 0x23:
    printf("lw\t$%d,%d($%d)\n", inst.itype.rt, inst.itype.imm, inst.itype.rs);
    break;

  case 0x24:
    printf("lbu\t$%d,%u($%d)\n", inst.itype.rt, (int16_t) inst.itype.imm, inst.itype.rs);
    break;

  case 0x25:
    printf("lhu\t$%d,%u($%d)\n", inst.itype.rt, (int16_t) inst.itype.imm, inst.itype.rs);
    break;

  case 0x28:
    printf("sb\t$%d,%d($%d)\n", inst.itype.rt, (int16_t) inst.itype.imm, inst.itype.rs);
    break;

  case 0x29:
    printf("sh\t$%d,%d($%d)\n", inst.itype.rt, (int16_t) inst.itype.imm, inst.itype.rs);
    break;

  case 0x2b:
    printf("sw\t$%d,%d($%d)\n", inst.itype.rt, (int16_t) inst.itype.imm, inst.itype.rs);;
    break;

  case 0x3:
    printf("jal\t0x%x\n", inst.jtype.addr*4);
    break;

  case 0xd: // opcode == 0xd (ORI)
    printf("ori\t$%d,$%d,0x%x\n", inst.itype.rt, inst.itype.rs, inst.itype.imm);
    break;

  case 0x2: // opcode == 0x2 (J)
    printf("j\t0x%x\n", inst.jtype.addr*4);
    break;

  default: // undefined opcode
    printf("%s: illegal instruction(opcode): %08x(%08x)\n", __func__, inst.bits, inst.rtype.opcode);
    exit(-1);
    break;
	}
}

