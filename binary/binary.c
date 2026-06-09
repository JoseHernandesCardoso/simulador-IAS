#include "binary.h"

BinaryWord slice(BinaryWord word, int start, int end) {
    BinaryWord sliced, isolation_mask;
    int isolation_size;

    isolation_size = end - start + 1;
    isolation_mask = (1ULL << (isolation_size)) - 1;
    sliced = word & WORD_MASK;
    sliced >>= 40 - (end + 1); // Remove final
    sliced &= isolation_mask; // Remove inicio

    return sliced;
}