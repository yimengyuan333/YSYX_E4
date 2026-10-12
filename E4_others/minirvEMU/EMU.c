#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
//这是一个简单的宏拓展，相当于logisim的分线器（？用于从指令中取位
#define GET_BITS(v, hi, lo)  (((v) >> (lo)) & ((1u << ((hi) - (lo) + 1)) - 1))

//后面发现opcode和funct3的解析很麻烦。各自单独写成宏
#define ADDI	0b0010011u
#define JALR    0b1100111u
#define ADD		0b0110011u
#define LUI		0b0110111u
#define LW_LBU	0b0000011u
#define SW_SB	0b0100011u

//I型指令的操作对象解析出来
#define I_RD(i)      GET_BITS(i, 11, 7)
#define I_FUNCT3(i)  GET_BITS(i, 14, 12)
#define I_RS1(i)     GET_BITS(i, 19, 15)
#define I_IMM(i)     ((int32_t)(i) >> 20)

//R型指令的操作对象解析出来
#define R_RD(i)      GET_BITS(i, 11, 7)
#define R_FUNCT3(i)  GET_BITS(i, 14, 12)
#define R_RS1(i)     GET_BITS(i, 19, 15)
#define R_RS2(i)     GET_BITS(i, 24, 20)
#define R_FUNCT7(i)  GET_BITS(i, 31, 25)

//U型指令的操作对象解析出来
#define U_IMM(i)	 GET_BITS(i, 31, 12)
#define U_RD(i)	 GET_BITS(i, 11, 7)

//S型
#define S_IMM_HIGH(i)   GET_BITS(i, 31, 25)
#define S_RS2(i)    GET_BITS(i, 24, 20)
#define S_RS1(i)    GET_BITS(i, 19, 15)
#define S_FUNCT3(i)   GET_BITS(i, 14, 12)
#define S_IMM_LOW(i)   GET_BITS(i, 11, 7)

uint32_t PC = 0;
uint32_t GPR[16] = {0};
uint32_t ROM[1u << 24] = {0};
uint32_t RAM[1u << 24] = {0};

void inst_cycle(void){
	uint32_t inst    = ROM[PC >> 2];
	uint32_t opcode  = GET_BITS(inst, 6, 0);//opcode其实是唯一一个可以写在外层switch之外的部分
	uint32_t next_pc = PC + 4;

	switch (opcode) {
	
	//确定I型指令
	case ADDI: {
		//已经确定是I型了之后这些也可以确定下来
		uint32_t rd  = I_RD(inst);
		uint32_t rs1 = I_RS1(inst);
		int32_t  imm = I_IMM(inst);

		//下面开始解析funct3
		switch (I_FUNCT3(inst)) {
		//目前funct只涉及000
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

	case LUI: {
		uint32_t imm = U_IMM(inst);
		uint32_t rd = U_RD(inst);
		GPR[rd] = (imm << 12 & 0xfffff000);//掩码把imm推到高位，低位补零
		break;
	}

	case ADD: {
		uint32_t funct7 = R_FUNCT7(inst);
		uint32_t rs2 = R_RS2(inst);
		uint32_t rs1 = R_RS1(inst);
		uint32_t funct3 = R_FUNCT3(inst);
		uint32_t rd = R_RD(inst);
		GPR[rd] = GPR[rs1] + GPR[rs2];
		break;
	}

	case LW_LBU:{
        uint32_t imm = I_IMM(inst);
        uint32_t rs1 = I_RS1(inst);
		uint32_t funct3 = I_FUNCT3(inst);
        uint32_t rd = I_RD(inst);
		
		switch (funct3) {
			case 0b010:{
				GPR[rd] = RAM[rs1 + imm];
                break;
			}

            case 0b100:{
                uint32_t byte = RAM[rs1 + imm];
                GPR[rd] = 0xff & byte;
                break;
            }

            default:
                break;
		}
	}

    case SW_SB:{
        uint32_t imm_high = S_IMM_HIGH(inst);
        uint32_t rs2 = S_RS2(inst);
        uint32_t rs1 = S_RS1(inst);
        uint32_t funct3 = S_FUNCT3(inst);
        uint32_t imm_low = S_IMM_LOW(inst);

        switch (funct3) {
            case 0b010:{
                RAM[rs1 + ((imm_high << 5) | imm_low)] = GPR[rs2];
                break;
            }

            case 0b000:{
                RAM[rs1 + ((imm_high << 5) | imm_low)] = (GPR[rs2] & 0xff);
                break;
            }

            default:
                break;
        }

    }

	default:
		break;
	}

	GPR[0] = 0;
	PC = next_pc;
}