#ifndef READ_FILE_H
#define READ_FILE_H

#include "../components/memory.h"

#define TEXT_FLAG ".TEXT"

/**
 * Le um arquivo em formato de texto contendo código
 * Assembly do IAS e salva as instruções na memória.
 * As instruções são salvas a partir do endereço 100.
 * Conteúdo de linhas precedido por "#" são considerados comentários e ignorados.
 * Retorna mensagem de erro em ERR se falhar ou NULL se tiver sucesso
 * 
 * @param file_name Nome do arquivo fonte.
 * @param memory Memória onde as instruções serão salvas.
 */
void read_code_file(char *file_name, Memory memory, char **err);

#endif
