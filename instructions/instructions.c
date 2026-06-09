#include "instructions.h"
#include <stdlib.h>
#include <string.h>


static InstructionData instructions[] = {
    {"LOAD", 1ULL, 1, "M(", ")"},
    {"LOAD", 2ULL, 1, "-M(", ")"},
    {"LOAD", 3ULL, 1, "|M(", ")|"},
    {"LOAD", 4ULL, 1, "-|M(", ")|"},
    {"LOAD", 9ULL, 1, "MQ,M(", ")"},
    {"LOAD", 10ULL, 1, "MQ", NULL},
    {"STOR", 18ULL, 1, "M(", ",8:19)"},
    {"STOR", 19ULL, 1, "M(", ",28:39)"},
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

BinaryWord encode_instruction(char *instruction) {
    BinaryWord encoded, address;
    int tot_instructions, i, finish_enconding;
    char *read_buffer, *addr_token, *mnem_token;

    tot_instructions = sizeof(instructions) / sizeof(InstructionData);
    mnem_token = strtok(instruction, " ");
    addr_token = strtok(NULL, " ");
    encoded = EMPTY_WORD;
    finish_enconding = 0;

    // Verifica mnemonico
    i = 0;
    while (i < tot_instructions && strcmp(mnem_token, instructions[i].mnemonic)) {
        i++;
    }

    // Verifica endereço
    while (i < tot_instructions && !strcmp(mnem_token, instructions[i].mnemonic) && !finish_enconding) {
        read_buffer = addr_token;
        if (read_buffer == NULL) {
            if (!instructions[i].has_address) encoded = instructions[i].opcode << ADDRESS_SIZE;
            finish_enconding = 1;

        // Se o primeiro trecho da string for igual ao prefixo
        } else if (strstr(read_buffer, instructions[i].address_prefix) == read_buffer) {
            if (instructions[i].address_sufix == NULL) {
                encoded = instructions[i].opcode << ADDRESS_SIZE;
                finish_enconding = 1;

            } else {
                read_buffer += strlen(instructions[i].address_prefix);
                address = strtoll(read_buffer, &read_buffer, 10);
                if (strstr(read_buffer, instructions[i].address_sufix) == read_buffer) {
                    if (address != 0) encoded = (instructions[i].opcode << ADDRESS_SIZE) | address;
                    finish_enconding = 1;
                }
            }
        }
        i++;
        }

    return encoded;
}
