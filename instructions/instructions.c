#include "instructions.h"
#include "../components/memory.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>


static InstructionData instructions[] = {
    {"LOAD", 1ULL, 1, "M(", ")"},
    {"LOAD", 2ULL, 1, "-M(", ")"},
    {"LOAD", 3ULL, 1, "|M(", ")|"},
    {"LOAD", 4ULL, 1, "-|M(", ")|"},
    {"LOAD", 9ULL, 1, "MQ,M(", ")"},
    {"LOAD", 10ULL, 1, "MQ", NULL},
    {"STOR", 18ULL, 1, "M(", ",8:19)"},
    {"STOR", 19ULL, 1, "M(", ",20:39)"},
    {"STOR", 33ULL, 1, "M(", ")"},
    {"JUMP", 13ULL, 1, "M(", ",0:19)"},
    {"JUMP", 14ULL, 1, "M(", ",20:39)"},
    {"JUMP+", 15ULL, 1, "M(", ",0:19)"},
    {"JUMP+", 16ULL, 1, "M(", ",20:39)"},
    {"ADD", 5ULL, 1, "M(", ")"},
    {"ADD", 7ULL, 1, "|M(", ")|"},
    {"SUB", 6ULL, 1, "M(", ")"},
    {"SUB", 8ULL, 1, "|M(", ")|"},
    {"MUL", 11ULL, 1, "M(", ")"},
    {"DIV", 12ULL, 1, "M(", ")"},
    {"LSH", 20ULL, 0, NULL, NULL},
    {"RSH", 21ULL, 0 , NULL, NULL}
};

/**
 * Copia STRING para OUT até seu primeiro número.
 * Requer que OUT tenha espaço suficiente para a cópia.
 * Se STRING é NULL, OUT também será NULL.
 * O usuário fica responsável por dar free() em OUT.
 */
static void cpy_until_number(char *string, char **out) {
    size_t len;
    int finish, i;

    if (string == NULL) {
        *out = NULL;
    }
    else {
        *out = calloc(sizeof(char), sizeof(string));
        len = strlen(string);
        finish = 0; i = 0;

        while (i < len && !finish) {
            if (!isdigit(string[i])) {
                (*out)[i] = string[i];
            } else {
                finish = 1;
            }
            i++;
        }
    }
}

BinaryWord encode_instruction(char *instruction, char **err) {
    BinaryWord encoded, address;
    int tot_instructions, i, finish_enconding;
    char *instr_token, *addr_token, *mnem_token;
    char *read_buffer, *addr_sufix, *addr_prefix;

    tot_instructions = sizeof(instructions) / sizeof(InstructionData);

    instr_token = malloc(sizeof(instruction));
    strcpy(instr_token, instruction);
    mnem_token = strtok(instr_token, " ");
    addr_token = strtok(NULL, " ");

    encoded = EMPTY_WORD;
    finish_enconding = 0;
    *err = NULL;

    // Verifica mnemonico
    i = 0;
    while (i < tot_instructions && strcmp(mnem_token, instructions[i].mnemonic)) {
        i++;
    }

    if (i >= tot_instructions) {
        *err = "ERRO DE SINTAXE! Instrução desconhecida!";
    }

    // Verifica endereço
    while (i < tot_instructions && !strcmp(mnem_token, instructions[i].mnemonic) && !finish_enconding) {
        addr_prefix = instructions[i].address_prefix;
        addr_sufix = instructions[i].address_sufix;

        // Verifica instruções sem endereçamento
        if (addr_token == NULL) {
            if (!instructions[i].has_address) {
                encoded = instructions[i].opcode << ADDRESS_SIZE;

            } else {
                *err = "ERRO DE SINTAXE! Campo de endereço não encontrado!";
                finish_enconding = 1;
            }

        // Se o primeiro trecho da string for igual ao prefixo do endereço
        } else {
            cpy_until_number(addr_token, &read_buffer);

            if (!strcmp(read_buffer, addr_prefix)) {
                free(read_buffer);
                if (addr_sufix == NULL) {
                    encoded = instructions[i].opcode << ADDRESS_SIZE;
                    finish_enconding = 1;
                
                } else {
                    read_buffer = addr_token + strlen(addr_prefix);
                    address = strtoll(read_buffer, &read_buffer, 10);

                    if (address < 0 || address > MAX_MEMORY_SIZE - 1) {
                        *err = "ERRO DE ACESSO A MEMÓRIA! Acesso a indice inválido da memória!";
                        finish_enconding = 1;

                    } else if (strstr(read_buffer, addr_sufix) == read_buffer && *(read_buffer + strlen(addr_sufix)) == '\0') {
                        encoded = (instructions[i].opcode << ADDRESS_SIZE) | address;
                        finish_enconding = 1;
                    }
                }
            }
        }
        i++;
    }
    
    if (encoded == EMPTY_WORD && *err == NULL) {
        *err = "ERRO DE SINTAXE! Campo de endereço inválido para a instrução!";
    }
    
    free(instr_token);
    return encoded;
}
