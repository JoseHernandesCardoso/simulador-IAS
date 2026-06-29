#include "./components/memory.h"
#include "./components/cpu/registrars.h"
#include "./components/cpu/controll_unit.h"
#include "./io/io_stuff.h"
#include "./io/read_file.h"
#include <stdio.h>

void main() {
    Memory mem;
    RegistrarsBank reg_bank;
    char *error_msg, *error_line;

    print_line(50);
    centered_print("MEG6: SIMULADOR DO IAS", 50);
    print_line(50);

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
        // Achar solução melhor para parada de emergência
        free(mem);
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
        }
        putchar('\n');
        // Achar solução melhor para parada de emergência
        free(mem);
        free(reg_bank);
        return;
    }
    printf("Arquivo de código lido com sucesso!\n\n");

    printf("INICIANDO EXECUÇÃO:\n");
    do {
        print_line(50);
        printf("BUSCANDO PRÓXIMA INSTRUÇÃO...\n");
        fetch_cycle(reg_bank, mem);
        putchar('\n');
        if (reg_bank->IR != EMPTY_WORD) {
            printf("EXECUTANDO ");
            execute_cycle(reg_bank, mem);
        } else {
            printf("NÃO HÁ MAIS INSTRUÇÕES!\n");
        }
    } while (reg_bank->IR != EMPTY_WORD);
    print_line(50);
    printf("Execução finalizada!\n\n");

    printf("DADOS NA MEMÓRIA:\n\n");
    for (int i=0; i < INSTRUCTIONS_ADDRESS; i++) {
        printf("%5lld ", mem[i]);
        if ((i+1) % 10 == 0) {
            putchar('\n');
        }
    }
    putchar('\n');

    // TODO: REVISAR DINÂMICA DE ENCERRAMENTO DO CÓDIGO EM CASO DE FALHA
    free(mem);
    free(reg_bank);
}