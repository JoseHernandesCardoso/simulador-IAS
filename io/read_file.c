#include "../instructions/instructions.h"
#include "../components/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 64

/**
 * Lê a próxima linha do arquivo de instruções.
 * Texto precedido por "#" é ignorado.
 * Retorna 1 se a linha for copiada com sucesso e possui conteúdo.
 * Caso contrário, retorna 0.
 */
static int read_next_line(char *output, FILE *file) {
    int success;
    if (fgets(output, MAX_LINE_SIZE, file) != NULL) {
        output[strcspn(output, "\n")] = '\0';
        output[strcspn(output, "#")] = '\0';
        success = 1;
    }

    if (success && output[0] != '\0') return 1;
    else return 0;
}

/**
 * Lê o arquivo de instruções e salva elas na memória.
 * Conteúdo precedido por "#" é considerado comentário e é ignorado.
 */
void read_code_file(char *file_name, Memory memory) {
    FILE *file;
    char line[MAX_LINE_SIZE];
    BinaryWord inst1, inst2;
    int valid_line, write_address = INSTRUCTIONS_ADDRESS;

    file = fopen(file_name, "r");
    while (!feof(file) && write_address < MAX_MEMORY_SIZE) {
        valid_line = 0;
        while (!feof(file) && !valid_line) {
            if (read_next_line(line, file)) {
                valid_line = 1;
            }
        };

        if (valid_line) {
            inst1 = encode_instruction(line);
        }

        valid_line = 0;
        while (!feof(file) && !valid_line) {
            if (read_next_line(line, file)) {
                valid_line = 1;
            }
        };

        if (valid_line) {
            inst2 = encode_instruction(line);
        }       

        memory[write_address] = (inst1 << INSTRUCTION_SIZE) | inst2;
        write_address++;
    }
}