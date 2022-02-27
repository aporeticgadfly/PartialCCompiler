#include <stdio.h>
#define MAXIDLEN 30

typedef enum {
    elsesym, ifsym, intsym, printsym, readsym, returnsym, whilesym, 
    semicolonsym, commasym, opencurlysym, closecurlysym, opensquaresym,
    closesquaresym, openbracketsym, closebracketsym, dividesym, 
    multiplysym, plussym, minussym, assignsym, eqsym, nesym, ltsym,
    lesym, gtsym, gesym, eofsym, constantsym, identifiersym, errorsym
} lextokens;

lextokens lex();

lextokens lextoken;

char identifier[MAXIDLEN+1];
char ch;

lextokens lex() {
    while (white(ch)) ch = getc(fp);

    switch (ch) {
    case ';': lextoken = semicolonsym; ch = getc(fp); return lextoken;
    case ',': lextoken = commasym; ch = getc(fp); return lextoken;
    case '+': lextoken = plussym; ch = getc(fp); return lextoken;
    case '-': lextoken = minussym; ch = getc(fp); return lextoken;
    case '*': lextoken = multiplysym; ch = getc(fp); return lextoken;
    case '(': lextoken = openbracketsym; ch = getc(fp); return lextoken;
    case ')': lextoken = closebracketsym; ch = getc(fp); return lextoken;
    case '{': lextoken = opencurlysym; ch = getc(fp); return lextoken;
    case '}': lextoken = closecurlysym; ch = getc(fp); return lextoken;
    case '[': lextoken = opensquaresym; ch = getc(fp); return lextoken;
    case ']': lextoken = closesquaresym; ch = getc(fp); return lextoken;
    case EOF: lextoken = eofsym; return lextoken;

    case'<':
        ch = getc(fp);
        if (ch == '=') {
            lextoken = lesym;
            ch = getc(fp);
            return lextoken;
        }
        else lextoken = ltsym;
        return lextoken;
    case'>':
        ch = getc(fp);
        if (ch == '=') {
            lextoken = gesym;
            return lextoken;
        }
        else lextoken = gtsym;
        return lextoken;
    case'=':
        ch = getc(fp);
        if (ch == '=') {
            lextoken = eqsym;
            ch = getc(fp);
            return lextoken;
        }
        else lextoken = assignsym;
        return lextoken;
    case'!':
        ch = getc(fp);
        if (ch != '=') {
            fprintf(stderr, "***Error - expected = after ! (%c)\n", ch);
            lextoken = errorsym;
            return lextoken;
        }
        else {
            ch = getc(fp);
            lextoken = nesym;
            return lextoken;
        }

    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm':
    case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
    {
        int i = 0;
        if (islower(ch)) {
            while (isalphanumeric(ch)) {
                if (i < MAXIDLEN) identifier[i++] = ch;
                else {
                    fprintf(stderr, "***Error - expected = after ! (%c)\n", ch);
                    lextoken = errorsym;
                    return lextoken;
                }
            }
            identifier[i] = '\0';

            if (strcmp(identifier, "else") == 0) {
                lextoken = elsesym;
                return lextoken;
            }
            else if (strcmp(identifier, "if") == 0) {
                lextoken = ifsym;
                return lextoken;
            }
            else if (strcmp(identifier, "int") == 0) {
                lextoken = intsym;
                return lextoken;
            }
            else if (strcmp(identifier, "print") == 0) {
                lextoken = printsym;
                return lextoken;
            }
            else if (strcmp(identifier, "read") == 0) {
                lextoken = readsym;
                return lextoken;
            }
            else if (strcmp(identifier, "return") == 0) {
                lextoken = returnsym;
                return lextoken;
            }
            else if (strcmp(identifier, "while") == 0) {
                lextoken = whilesym;
                return lextoken;
            }
            else {
                lextoken = identifiersym;
                return lextoken;
            }
        }
    }

    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    {
        int overflow = 0;
        ival = 0;
        while (isdigit(ch)) {
            if (ival > INT_MAX / 10) overflow = 1;
            else if (ival * 10 > (INT_MAX - ch + '0')) overflow = 1;
            else ival = ival * 10 + ch - '0';
            ch = getc(fp);
        }

        if (overflow) {
            lextoken = errorsym;
            ival = INT_MAX;
            fprintf(stderr, "integer constant overflow\n");
            return lextoken;
        }
        else {
            lextoken = constantsym;
            return lextoken;
        }

    }

    case '/':
        ch = getc(fp);
        if (ch == '*') {
            incomment = 1;
            ch = getc(fp);
            while (incomment) {
                if (ch == EOF) {
                    fprintf(stderr, "warning - end of file in comment\n");
                    lextoken = errorsym;
                    return lextoken;
                }
                else if (ch == '*') {
                    ch = getc(fp);
                    if (ch == '/') {
                        ch = getc(fp);
                        incomment = 0;
                    }
                }
                else ch = getc(fp);
            }
            lextoken = lex();
            return lextoken;
        }
        else {
            lextoken = dividesym;
            return lextoken;
        }
    default:
        fprintf(stderr, "***Unexpected character %c\n", ch);
        lextoken = errorsym;
        return lextoken;
    }
}

int main(int argc, char** argv) {

    FILE* fp = fopen(argv[1], "r+");
    if (fp == NULL) perror("Error opening file");
    else
    {
        while (ch != EOF) {
            ch = lex();
            printf("%c", ch);
        }
    }
    fclose(fp);
    return 0;
}