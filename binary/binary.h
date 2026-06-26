#ifndef BINARY_H
#define BINARY_H

#define EMPTY_WORD 0ULL

#define WORD_MASK ((1ULL << 40) - 1)
#define WORD_SIZE 40

#define INST_ADDR_MASK ((1ULL << 12) - 1)


/**
 * Uma palavra binária com até 40 bits de tamanho.
 */
typedef unsigned long long BinaryWord;

/**
 * Faz o fatiamento de uma palavra binária e retorna
 * apenas os bits do intervalo dado.
 * 
 * A contagem das posições dos bits é da esquerda para
 * direita.
 * 
 * @param word Palavra que será fatiada
 * @param start Inicio do intervalo
 * @param end Fim do intervalo
 */
BinaryWord slice(BinaryWord word, int start, int end, int word_size);

#endif