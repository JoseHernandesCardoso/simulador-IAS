#include "./components/memory.h"
#include "./io/read_file.h"
#include <stdio.h>

void main() {
    char *error_msg, *error_line;

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
    
    printf("Lendo código do arquivo...\n");
    read_code_file("teste.txt", mem, &error_msg, &error_line);
    if (error_msg != NULL) {
        printf("%s\n", error_msg);
        if (error_line != NULL) printf("LINHA: %s\n", error_line);
        putchar('\n');
        return;
    }
    printf("Arquivo de código lido com sucesso!\n\n");
}