#include "registrars.h"
#include "../../binary/binary.h"
#include "../memory.h"
#include <stdlib.h>

RegistrarsBank initialize_registrars() {
    RegistrarsBank reg_bank = calloc(1, sizeof(struct RegBank));
    reg_bank->PC = INSTRUCTIONS_ADDRESS;
    return reg_bank;
}