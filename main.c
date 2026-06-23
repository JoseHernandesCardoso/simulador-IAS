#include "./components/memory.h"
#include "./io/read_file.h"
#include <stdio.h>

void main() {
    
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("           MEG6: SIMULADOR DO IAS           \n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

    printf("Alocando memória virtual...\n");
    Memory mem = alocate_memory();
    if (mem == NULL) {
        printf("ERRO DE ALOCAÇÃO DE MEMÓRIA! PROVAVELMENTE RAM INSUFICIENTE.\nEncerrando programa");
        return;
    }
    printf("Memória alocada com sucesso!\n\n");
    

    
    read_code_file("teste.txt", mem);
    int i = INSTRUCTIONS_ADDRESS;

    for (int j=DATA_ADDRESS; j < 150; j++) printf("%lld ", mem[j]);
    putchar('\n');
}