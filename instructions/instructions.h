#include "../binary/binary.h"

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#define INSTRUCTION_SIZE 20
#define OPCODE_SIZE 8
#define ADDRESS_SIZE 12

typedef struct {
    char *mnemonic;
    BinaryWord opcode;
    unsigned int has_address;
    char *address_prefix; 
    char *address_sufix;
} InstructionData;


/**
 * Retorna o a BinaryWord opcode + endereço da INSTRUCTION que deve estar no formato:
 * 
 *          <MNEMONIC> <ADDRESS>
 * 
 * Onde <ADDRESS> pode existir ou não dependendo de <MNEMONIC> e tem formato:
 * 
 *          <PREFIX><MEMORY_ADDRESS><SUFIX>
 * 
 * Onde <PREFIX> e <SUFIX> variam com o opcode da instrução.
 * Retorna EMPTY_WORD e retorna mensagem de erro em ERR se INSTRUCTION for inválido.
 * Caso contrário, ERR retorna NULL.
 * 
 * @param instruction String da instrução.
 * @param err Saida de erro.
 * @return Instrução codificada.
 */
BinaryWord encode_instruction(char *instruction, char **err);

#endif