#include "read_file.h"
#include "../instructions/instructions.h"
#include "../components/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
 * Verifica se a string é toda numérica.
 * Retorna 1 se verdadeiro e 0 caso falso.
 */
static int is_numeric(char *string) {
    int i, is_num;

    is_num = 0;
    if (string[0] == '-' || string[0] == '+' || isdigit(string[0])) {
        is_num = 1;
        i = 1;
        while (is_num && string[i] != '\0') {
            if (!isdigit(string[i])) is_num = 0;
            i++;
        }
    }

    return is_num;
}

/**
 * Retorna 1 se a string está em branco, ou seja, é vazia
 * ou contém apensa caracteres em branco.
 */
static int blank_str(char *string) {
    int i, is_blank, end_string;

    i = 0;
    end_string = 0;
    is_blank = 1;
    while (is_blank && !end_string) {
        if (string[i] == '\0') {
            end_string = 1;
        } else if (string[i] != ' ') {
            is_blank = 0;
        }
    }
    return is_blank;
    
}

/**
 * Lê o arquivo de instruções e salva elas na memória.
 * Conteúdo precedido por "#" é considerado comentário e é ignorado.
 */
void read_code_file(char *file_name, Memory memory) {
    FILE *file;
    char line[MAX_LINE_SIZE];
    BinaryWord inst1, inst2;
    int valid_line, reading_data;
    int reading_error = 0;
    int write_address = DATA_ADDRESS;

    file = fopen(file_name, "r");

    // Lê Dados
    reading_data = 1;
    valid_line = read_next_line(line, file);
    while (!feof(file) && reading_data && !reading_error) {
        if (is_numeric(line)) {
            if (valid_line) {
                memory[write_address] = strtoll(line, NULL, 10);
                write_address++;
            }
        } else if (!strcmp(line, TEXT_FLAG)) {
            reading_data = 0;
        } else if (!blank_str(line)) {
            printf("ERRO DE DADOS! Apenas dados são permitidos na seção de dados!\n");
            reading_error = 1;
        }

        if (write_address >= INSTRUCTIONS_ADDRESS) {
            printf("ERRO DE DADOS! Limite de dados de entrada excedido!\n");
            reading_error = 1;
        }

        valid_line = read_next_line(line, file);
    }

    // Lê instruções
    write_address = INSTRUCTIONS_ADDRESS;
    while (!feof(file) && write_address < MAX_MEMORY_SIZE && !reading_error) {
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