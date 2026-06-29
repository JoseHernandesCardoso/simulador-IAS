#ifndef IO_STUFF_H
#define IO_STUFF_H

/**
 * Exibe uma linha na tela no padrão:
 * 
 *      -=-=-=-=-=-=-=-=-=-
 * 
 * @param size Tamanho da linha.
 */
void print_line(int size);


/**
 * Exibe uma mensagem centralizada em um dado tamanho de linha.
 * Requer que o tamanho da mensagem seja menor que o tamanho da linha.
 * 
 * @param msg Mensagem a ser exibida.
 * @param line_size Tamanho da linha.
 */
void centered_print(char *msg, int line_size);

#endif