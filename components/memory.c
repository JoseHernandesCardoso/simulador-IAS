#include "memory.h"

Memory alocate_memory() {
    return malloc(MAX_MEMORY_SIZE * sizeof(BinaryWord*));
}