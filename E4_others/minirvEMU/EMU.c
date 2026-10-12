#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define GET_BITS(v, hi, lo)  (((v) >> (lo)) & ((1u << ((hi) - (lo) + 1)) - 1))

#define OP_IMM  0b0010011u
#define JALR    0b1100111u

#define I_RD(i)      GET_BITS(i, 11, 7)
#define I_FUNCT3(i)  GET_BITS(i, 14, 12)
#define I_RS1(i)     GET_BITS(i, 19, 15)
#define I_IMM(i)     ((int32_t)(i) >> 20)

#define R_RD(i)      GET_BITS(i, 11, 7)
#define R_FUNCT3(i)  GET_BITS(i, 14, 12)
#define R_RS1(i)     GET_BITS(i, 19, 15)
#define R_RS2(i)     GET_BITS(i, 24, 20)
#define R_FUNCT7(i)  GET_BITS(i, 31, 25)

uint32_t PC = 0;
uint32_t GPR[32] = {0};
uint32_t M[1u << 24] = {0};

void inst_cycle(void){
	uint32_t inst    = M[PC >> 2];
	uint32_t opcode  = GET_BITS(inst, 6, 0);
	uint32_t next_pc = PC + 4;

	switch (opcode) {

	case OP_IMM: {
		uint32_t rd  = I_RD(inst);
		uint32_t rs1 = I_RS1(inst);
		int32_t  imm = I_IMM(inst);

		switch (I_FUNCT3(inst)) {
		case 0b000:
			GPR[rd] = GPR[rs1] + (uint32_t)imm;
			break;
		default:
			break;
		}
		break;
	}

	case JALR: {
		uint32_t rd  = I_RD(inst);
		uint32_t rs1 = I_RS1(inst);
		int32_t  imm = I_IMM(inst);

		if (I_FUNCT3(inst) == 0b000) {
			uint32_t target = (GPR[rs1] + (uint32_t)imm) & ~1u;
			GPR[rd] = next_pc;
			next_pc = target;
		}
		break;
	}

	default:
		break;
	}

	GPR[0] = 0;
	PC = next_pc;
}