#include "../binary/binary.h"
#include <stdlib.h>

#ifndef MEMORY_H
#define MEMORY_H

#define MAX_MEMORY_SIZE 1000
#define DATA_ADDRESS 0
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

#endif