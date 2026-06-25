#include "./components/memory.h"
#include "./components/cpu/registrars.h"
#include "./io/read_file.h"
#include <stdio.h>

void main() {
    Memory mem;
    RegistrarsBank reg_bank;
    char *error_msg, *error_line;

    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("           MEG6: SIMULADOR DO IAS           \n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

    printf("Alocando memória virtual...\n");
    mem = alocate_memory();
    if (mem == NULL) {
        printf("ERRO DE ALOCAÇÃO DE MEMÓRIA! PROVAVELMENTE RAM INSUFICIENTE.\nEncerrando programa");
        return;
    }
    printf("Memória alocada com sucesso!\n\n");

    printf("Inicializando registradores...\n");
    reg_bank = initialize_registrars();
    if (reg_bank == NULL) {
        printf("ERRO DE ALOCAÇÃO DE MEMÓRIA! PROVAVELMENTE RAM INSUFICIENTE.\nEncerrando programa");
        return;
    }
    printf("Registradores inicializados com sucesso!\n\n");

    // TODO: ADICIONAR INSERÇÃO DO NOME DO ARQUIVO PELO USUÁRIO

    printf("Lendo código do arquivo...\n");
    read_code_file("teste.txt", mem, &error_msg, &error_line);
    if (error_msg != NULL) {
        printf("%s\n", error_msg);
        if (error_line != NULL) {
            printf("LINHA: %s\n", error_line);
            free(error_line);
            error_line = NULL;
        }
        putchar('\n');
        return;
    }
    printf("Arquivo de código lido com sucesso!\n\n");

    // TODO: REVISAR DINÂMICA DE ENCERRAMENTO DO CÓDIGO EM CASO DE FALHA
    free(mem);
    free(reg_bank);
}