#ifndef READ_FILE_H
#define READ_FILE_H

#include "../components/memory.h"

#define TEXT_FLAG ".TEXT"

/**
 * Le um arquivo em formato de texto contendo código
 * Assembly do IAS e salva as instruções na memória.
 * As instruções são salvas a partir do endereço 100.
 * Conteúdo de linhas precedido por "#" são considerados comentários e ignorados.
 * 
 * 
 * @param file_name Nome do arquivo fonte.
 * @param memory Memória onde as instruções serão salvas.
 * @param err Saida da mensagem de erro. Se não houver, é definido como NULL.
 * @param err_line Saida da linha que resultou no erro. Se não houver, é definido como NULL.
 *                 Deve ser liberado com free().
 */
void read_code_file(char *file_name, Memory memory, char **err, char **err_line);

#endif
