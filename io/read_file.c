#include "../instructions/instructions.h"
#include "../components/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 64

/**
 * Lê a próxima linha do arquivo de instruções.
 */
static void read_next_line(char *output, FILE *file) {
    fgets(output, MAX_LINE_SIZE, file);
    output[strcspn(output, "\n")] = '\0';
}

/**
 * Lê o arquivo de instruções e salva elas na memória.
 */
void read_code_file(char *file_name, Memory memory) {
    FILE *file;
    char line[MAX_LINE_SIZE];
    BinaryWord inst1, inst2;
    int write_address = INSTRUCTIONS_ADDRESS;

    file = fopen(file_name, "r");
    while (!feof(file) && write_address < MAX_MEMORY_SIZE) {
        read_next_line(line, file);
        inst1 = encode_instruction(line);

        if (!feof(file)) {
            read_next_line(line, file);
            inst2 = encode_instruction(line);
        } else {
            inst2 = EMPTY_WORD;
        }

        memory[write_address] = (inst1 << INSTRUCTION_SIZE) | inst2;
        write_address++;
    }
}