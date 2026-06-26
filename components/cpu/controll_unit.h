#include "registrars.h"
#include "../memory.h"

#ifndef CONTROLL_UNIT_H
#define CONTROLL_UNIT_H

/**
 * Realiza o ciclo de busca da próxima instrução a ser executada.
 * Se não houverem mais instruções, o IR do banco de registradores
 * recebe EMPTY_WORD.
 * 
 * Exibe na tela as movimentações de dados.
 * 
 * @param reg_bank Banco de registradores do sistema.
 * @param mem Memória principal do sistema com instruções carregadas.
 */
void fetch_cycle(RegistrarsBank reg_bank, Memory mem);


/**
 * Realiza o ciclo de execução da instrução no IR do banco de registradores.
 * 
 * Exibe na tela a instrução executada e as movimentações de dados.
 * 
 * @param reg_bank Banco de registradores do sistema.
 * @param mem Memória principal do sistema.
 */
void execute_cycle(RegistrarsBank reg_bank, Memory mem);

#endif