#include "./components/memory.h"
#include <stdio.h>

void main() {
    Memory mem = alocate_memory();
    
    read_code_file("teste.txt", mem);
    int i = INSTRUCTIONS_ADDRESS;

    for (int j=0; j < 1000; j++) printf("%lld ", mem[j]);
    putchar('\n');
    // printf("%lld\n", mem[i]);
    // while (mem[i]) {
    //     printf("%lld\n", mem[i]);
    //     i++;
    // }
}