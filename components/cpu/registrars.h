#include "../../binary/binary.h"

#ifndef REGISTRARS_H
#define REGISTRARS_H

typedef BinaryWord Registrar;
typedef SignedBinaryWord DataRegistrar;

typedef struct RegBank{
    Registrar MBR;         // 40 bits
    DataRegistrar AC, MQ;  // 40 bits
    Registrar IBR;         // 20 bits
    Registrar MAR, PC;     // 12 bits
    Registrar IR;          // 8 bits
} *RegistrarsBank;

/**
 * Aloca e retorna um novo banco de registradores.
 * PC já é inicializado apontando para a o inicio das instruções de uma memória.
 */
RegistrarsBank initialize_registrars();

#endif