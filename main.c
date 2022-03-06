#include <stdio.h>
#include <stdlib.h>
#include "lexicalanalyzer.h"

int main(int argc, char** argv) {

    FILE* fp = fopen(argv[1], "r+");
    if (fp == NULL) perror("Error opening file");
    else
    {
        ch = getc(fp);
        while (ch != EOF && result != 89) {
            result = lex(fp);
            //printf("%c\n", ch);
            //printf("%d\n", result);
            printf("%s\n", tokens[result]);
            //printf("%s\n", tokens);
            //printf("%s", identifier);
            //printf("%c", charval);
            //printf("%d", ival);
            //printf("%f", fpval);
            //printf("%s", string);

        }
    }
    fclose(fp);
    return 0;
}