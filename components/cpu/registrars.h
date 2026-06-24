#include "../../binary/binary.h"

#ifndef REGISTRARS_H
#define REGISTRARS_H

typedef BinaryWord Registrar;

typedef struct {
    Registrar MBR, AC, MQ; // 40 bits
    Registrar IBR;         // 20 bits
    Registrar MAR, PC;     // 12 bits
    Registrar IR;          // 8 bits
} RegistrarsBank;

#endif