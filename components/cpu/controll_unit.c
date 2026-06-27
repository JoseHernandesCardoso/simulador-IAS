#include "controll_unit.h"
#include <stdio.h>

// bit de controle
int next_instruction_IBR = 0;

void fetch_cycle(RegistrarsBank reg_bank, Memory mem) {
    BinaryWord buffer;
    // Próxima instrução no IBR?
    if (next_instruction_IBR) {
        buffer = slice(reg_bank->IBR, 0, 7, 20);
        printf(" IR <- IBR(0:7) [%lld]\n", buffer);
        reg_bank->IR = buffer;

        buffer = slice(reg_bank->IBR, 8, 19, 20);
        printf("MAR <- IBR(8:19) [%lld]\n", buffer);
        reg_bank->MAR = buffer;
        next_instruction_IBR = 0;

        reg_bank->PC++;
        printf(" PC <- PC + 1 [%lld]\n", reg_bank->PC);

    } else {
        // Fim da memória
        if (reg_bank->PC >= MAX_MEMORY_SIZE) {
            reg_bank->IR = EMPTY_WORD;
        
        } else {
            printf("MAR <- PC [%lld]\n", reg_bank->PC);
            reg_bank->MAR = reg_bank->PC;
            printf("MBR <- M(MAR)\n");
            reg_bank->MBR = mem[reg_bank->MAR];

            // Instrução a esquerda é necessária? --> Instrução em IR NÃO é JUMP a direita?
            if (reg_bank->IR != 14ULL && reg_bank->IR != 16ULL) {
                printf("IBR <- MBR(20:39)\n");
                reg_bank->IBR = slice(reg_bank->MBR, 20, 39, 40);
                next_instruction_IBR = 1;

                buffer = slice(reg_bank->MBR, 0, 7, 40);
                printf(" IR <- MBR(0:7) [%lld]\n", buffer);
                reg_bank->IR = buffer;

                buffer = slice(reg_bank->MBR, 8, 19, 40);
                printf("MAR <- MBR(8:19) [%lld]\n", buffer);
                reg_bank->MAR = buffer;

            } else {
                buffer = slice(reg_bank->MBR, 20, 27, 40);
                printf(" IR <- MBR(20:27 [%lld])\n", buffer);
                reg_bank->IR = buffer;

                buffer = slice(reg_bank->MBR, 28, 39, 40);
                printf("MAR <- MBR(28:39) [%lld]\n", buffer);
                reg_bank->MAR = buffer;

                reg_bank->PC++;
                printf(" PC <- PC + 1 [%lld]\n", reg_bank->PC);
            }
        }
    }
}

void execute_cycle(RegistrarsBank reg_bank, Memory mem) {
    BinaryWord buffer;

    switch (reg_bank->IR) {
        case 1: // LOAD M(X)
            printf("LOAD M(%lld)\n", reg_bank->MAR);

            reg_bank->AC = mem[reg_bank->MAR];
            printf("AC <- M(%lld) [%lld]\n", reg_bank->MAR, reg_bank->AC);
            break;

        case 2: // LOAD -M(X)
            printf("LOAD -M(%lld)\n", reg_bank->MAR);

            reg_bank->AC = -mem[reg_bank->MAR];
            printf("AC <- -M(%lld) [%lld]\n", reg_bank->MAR, reg_bank->AC);
            break;

        case 3: // LOAD |M(X)|
            printf("LOAD |M(%lld)|\n", reg_bank->MAR);

            reg_bank->AC = abs(mem[reg_bank->MAR]);
            printf("AC <- |M(%lld)| [%lld]\n", reg_bank->MAR, reg_bank->AC);
            break;

        case 4: // LOAD -|M(X)|
            printf("LOAD -|M(%lld)|\n", reg_bank->MAR);

            reg_bank->AC = -abs(mem[reg_bank->MAR]);
            printf("AC <- -|M(%lld)| [%lld]\n", reg_bank->MAR, reg_bank->AC);
            break;

        case 9: // LOAD MQ,M(X)
            printf("LOAD MQ,M(%lld)\n", reg_bank->MAR);

            reg_bank->MQ = mem[reg_bank->MAR];
            printf("MQ <- M(%lld) [%lld]\n", reg_bank->MAR, reg_bank->MQ);
            break;

        case 10: // LOAD MQ
            printf("LOAD MQ\n");

            reg_bank->AC = reg_bank->MQ;
            printf("AC <- MQ [%lld]\n", reg_bank->AC);
            break;

        case 18: // STOR M(X,8:19)
            printf("STOR M(%lld,8:19)\n", reg_bank->MAR);

            buffer = slice(reg_bank->AC, 27, 39, 40);
            mem[reg_bank->MAR] &= ~(INST_ADDR_MASK << 20);
            mem[reg_bank->MAR] |= buffer << 20;
            printf("M(%lld)(8:19) <- PC(27:39) [%lld]\n", reg_bank->MAR, buffer);
            break;

        case 19: // STOR M(X,28:39)
            printf("STOR M(%lld,28:39)\n", reg_bank->MAR);

            buffer = slice(reg_bank->AC, 27, 39, 40);
            mem[reg_bank->MAR] &= ~INST_ADDR_MASK;
            mem[reg_bank->MAR] |= buffer;
            printf("M(%lld)(28:39) <- PC(27:39) [%lld]\n", reg_bank->MAR, buffer);
            break;

        case 33: // STOR M(X)
            printf("STOR M(%lld)\n", reg_bank->MAR);

            mem[reg_bank->MAR] = reg_bank->AC;
            printf("M(%lld) <- AC [%lld]\n", reg_bank->MAR, reg_bank->AC);
            break;

        case 13: // JUMP M(X,0:19)
            printf("JUMP M(%lld,0:19)\n", reg_bank->MAR);

            reg_bank->PC = reg_bank->MAR;
            next_instruction_IBR = 0;
            printf("PC <- MAR, [%lld]\n", reg_bank->PC);
            break;

        case 14: // JUMP M(X,20:39)
            printf("JUMP M(%lld,20:39)\n", reg_bank->MAR);

            reg_bank->PC = reg_bank->MAR;
            next_instruction_IBR = 0;
            printf("PC <- MAR [%lld]\n", reg_bank->PC);
            break;
    
        case 15: // JUMP+ M(X,0:19)
            printf("JUMP+ M(%lld,0:19)\n", reg_bank->MAR);

            if (reg_bank->AC >= 0) {
                reg_bank->PC = reg_bank->MAR;
                next_instruction_IBR = 0;
                printf("PC <- MAR [%lld]\n", reg_bank->PC);
            } else {
                printf("PC < 0, não salta!\n");
            }
            break;

        case 16: // JUMP+ M(X,20:39)
            printf("JUMP+ M(%lld,20:39)\n", reg_bank->MAR);

            if (reg_bank->AC >= 0) {
                reg_bank->PC = reg_bank->MAR;
                next_instruction_IBR = 0;
                printf("PC <- MAR [%lld]\n", reg_bank->PC);
            } else {
                printf("PC < 0, não salta!\n");
            }
            break;
        
        case 5: // ADD M(X)
            printf("ADD M(%lld)\n", reg_bank->MAR);

            reg_bank->AC += mem[reg_bank->MAR];
            printf("AC <- AC + M(%lld) [%lld]\n", reg_bank->MAR, reg_bank->AC);
            break;
        
        case 7: // ADD |M(X)|
            printf("|ADD M(%lld)|\n", reg_bank->MAR);

            reg_bank->AC += abs(mem[reg_bank->MAR]);
            printf("AC <- AC + |M(%lld)| [%lld]\n", reg_bank->MAR, reg_bank->AC);
            break;

        case 6: // SUB M(X)
            printf("SUB M(%lld)\n", reg_bank->MAR);

            reg_bank->AC -= mem[reg_bank->MAR];
            printf("AC <- AC - M(%lld) [%lld]\n", reg_bank->MAR, reg_bank->AC);
            break;

        case 8: // SUB |M(X)|
            printf("SUB |M(%lld)|\n", reg_bank->MAR);

            reg_bank->AC -= abs(mem[reg_bank->MAR]);
            printf("AC <- AC - |M(%lld)| [%lld]\n", reg_bank->MAR, reg_bank->AC);
            break;
        
        case 11: // MUL M(X)
            printf("MUL M(%lld)\n", reg_bank->MAR);

            // Algoritmo da multiplicação binária
            reg_bank->AC = 0ULL;
            for (int i=0; i < 40; i++) {
                if ((reg_bank->MQ & 1ULL) == 1) {
                    reg_bank->AC += mem[reg_bank->MAR];
                }
                // Deslocamento do par AC MQ para a direita
                reg_bank->MQ >>= 1;
                reg_bank->MQ |= (reg_bank->AC & 1ULL) << 39;
                reg_bank->AC >>= 1;
            }
            printf("AC,MQ <- MQ * M(%lld) [%lld | %lld]\n", reg_bank->MAR, reg_bank->AC, reg_bank->MQ);
            break;

        case 12: // DIV M(X)
            printf("DIV M(%lld)\n", reg_bank->MAR);

            reg_bank->MQ = reg_bank->AC / mem[reg_bank->MAR];
            reg_bank->AC = reg_bank->AC % mem[reg_bank->MAR];
            printf("MQ <- AC / M(%lld) [%lld]\n", reg_bank->MAR, reg_bank->MQ);
            printf("AC <- AC %% M(%lld) [%lld]\n", reg_bank->MAR, reg_bank->AC);
            break;

        case 20: // LSH
            printf("LSH\n");

            reg_bank->AC <<= 1;
            printf("AC <- AC << [%lld]\n", reg_bank->AC);
            break;

        case 21: // RSH
            printf("RSH\n");

            reg_bank->AC >>= 1;
            printf("AC <- AC >> [%lld]\n", reg_bank->AC);
            break;

        default:
            printf("*OPCODE DESCONHECIDO*\n");
            break;
    }
}