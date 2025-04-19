#define KEY 'X';
#define CLEARTEXT 'A';

#include <stdio.h>

void printchar(char c, char *text) {
    printf("%s = '%c' (0x%x)\n", text, c, c);
}