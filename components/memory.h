#include "../binary/binary.h"

#ifndef MEMORY_H
#define MEMORY_H

#define MAX_MEMORY_SIZE 1000
#define INSTRUCTIONS_ADDRESS 100

/**
 * Memória primária do computador IAS com capacidade
 * de 1000 palavras. As 100 primeiras palavras são
 * destinadas a dados, enquanto as outras 900 servem
 * para armazenar as instruções.
 */
typedef BinaryWord *Memory;

/**
 * Aloca uma memória de tamanho MAX_MEMORY_SIZE
 * 
 * @return Memória alocada.
 */
Memory alocate_memory();

/**
 * Le um arquivo em formato de texto contendo código
 * Assembly do IAS e salva as instruções na memória.
 * As instruções são salvas a partir do endereço 100.
 * 
 * @param file_name Nome do arquivo fonte.
 * @param memory Memória onde as instruções serão salvas.
 */
void read_code_file(char *file_name, Memory memory);

#endif