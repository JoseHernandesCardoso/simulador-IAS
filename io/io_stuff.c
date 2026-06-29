#include "io_stuff.h"
#include <stdio.h>
#include <string.h>

void print_line(int size) {
    char *pattern = "-=";
    int i;

    for (i = 0; i < size; i++) {
        putchar(pattern[i%2]);
    }
    putchar('\n');
}

void centered_print(char *msg, int line_size) {
    int padding = (line_size - strlen(msg))/2;
    int i;

    for (i = 0; i < padding; i++) {
        putchar(' ');
    };
    printf("%s\n", msg);
}

void clear_buffer() {
    char c;
    while ((c = fgetc(stdin)) != '\n' && c != EOF);
}

void wait_user_response() {
    while (getchar() != '\n');
}