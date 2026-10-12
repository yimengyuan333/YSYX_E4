#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define GET_BITS(v, hi, lo)  (((v) >> (lo)) & ((1u << ((hi) - (lo) + 1)) - 1))

uint8_t PC = 0;
uint8_t GPR[4] = {0b0};
uint8_t M[16] = {0b0};

void inst_cycle(void){

    uint8_t op = GET_BITS(M[PC], 7, 6);   // 高两位
    uint8_t rd = GET_BITS(M[PC], 5, 4);   // 次两位
    uint8_t rs1 = GET_BITS(M[PC], 3, 2);  // 次次两位
    uint8_t rs2 = GET_BITS(M[PC], 1, 0);  // 低两位
    uint8_t imm = M[PC] & 0x0F;           // 低四位
    uint8_t mid4 = GET_BITS(M[PC], 5, 2); // 中四位

    switch (op) {
        //is li
        case 0b10:
            GPR[rd] = imm;
            PC++;
            break;
        //is add
        case 0b00:
            GPR[rd] = GPR[rs1] + GPR[rs2];
            PC++;
            break;
        //is bner0
        case 0b11:
            if(GPR[0] != GPR[rs2]){
                PC = mid4;
            } else {
                PC++;
            }
            break;
        //is out
        case 0b01:
            printf("GPR[%d] is %08b in binary; %d in decimal\n", rd, GPR[rd], GPR[rd]);
            PC++;
            break;
    }

}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("only one arg plz.\n");
        return -1;
    }
    char *inputed_arg = argv[1];

    // strtol 把字符串 "10" 解析成数值 10
    long n = strtol(inputed_arg, NULL, 10);
    if (n < 0 || n > 15) {
        printf("n must be in [0, 15] because li imm is 4 bits\n");
        return -1;
    }

    M[0] = (0b10001010 & 0xF0) | ((uint8_t)n & 0x0F);
    M[1] = 0b10010000;
    M[2] = 0b10100000;
    M[3] = 0b10110001;
    M[4] = 0b00010111;
    M[5] = 0b00101001;
    M[6] = 0b11010001;
    M[7] = 0b01100000;

    while (PC != 8){                                                                                                                   
        inst_cycle();
    }

    return 0;
}