#include "controll_unit.h"
#include <stdio.h>

// bit de controle
int next_instruction_IBR = 0;

void fetch_cycle(RegistrarsBank reg_bank, Memory mem) {
    // Próxima instrução no IBR?
    if (next_instruction_IBR) {
        printf(" IR <- IBR(0:7)\n");
        reg_bank->IR = slice(reg_bank->IBR, 0, 7, 20);
        printf("MAR <- IBR(8:19)\n");
        reg_bank->MAR = slice(reg_bank->IBR, 8, 19, 20);
        next_instruction_IBR = 0;
        printf(" PC <- PC + 1\n");
        reg_bank->PC++;

    } else {
        // Fim da memória
        if (reg_bank->PC >= MAX_MEMORY_SIZE) {
            reg_bank->IR = EMPTY_WORD;
        
        } else {
            printf("MAR <- PC\n");
            reg_bank->MAR = reg_bank->PC;
            printf("MBR <- M(MAR)\n");
            reg_bank->MBR = mem[reg_bank->MAR];

            // Instrução a esquerda é necessária? --> Instrução em IR NÃO é JUMP a direita?
            if (reg_bank->IR == 14ULL || reg_bank->IR == 16ULL) {
                printf(" IR <- MBR(20:27)\n");
                reg_bank->IR = slice(reg_bank->MBR, 20, 27, 40);
                printf("MAR <- MBR(28:39)\n");
                reg_bank->MAR = slice(reg_bank->MBR, 28, 39, 40);
                printf(" PC <- PC + 1\n");
                reg_bank->PC++;

            } else {
                printf("IBR <- MBR(20:39)\n");
                reg_bank->IBR = slice(reg_bank->MBR, 20, 39, 40);
                next_instruction_IBR = 1;
                printf(" IR <- MBR(0:7)\n");
                reg_bank->IR = slice(reg_bank->MBR, 0, 7, 40);
                printf("MAR <- MBR(8:19)\n");
                reg_bank->MAR = slice(reg_bank->MBR, 8, 19, 40);
            }
        }
    }
} 


void execute_cycle(RegistrarsBank reg_bank, Memory mem) {

}