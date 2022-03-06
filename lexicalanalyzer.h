#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>

#define MAXIDLEN 30

typedef enum {
    elsesym, ifsym, intsym, printsym, readsym, returnsym, whilesym, 
    semicolonsym, commasym, opencurlysym, closecurlysym, opensquaresym,
    closesquaresym, openbracketsym, closebracketsym, tildecomplsym, periodsym, 
    hashsym, dividesym, multiplyindirectsym, modulosym, plussym, minussym, assignsym, eqsym, 
    nesym, ltsym, lesym, gtsym, gesym, eofsym, autosym, doublesym, structsym, 
    breaksym, longsym, switchsym, casesym, enumsym, registersym, typedefsym, charsym, 
    externsym, unionsym, constsym, floatsym, shortsym, unsignedsym, continuesym,
    forsym, signedsym, voidsym, defaultsym, gotosym, sizeofsym, volatilesym, 
    dosym, staticsym, typesym, alignofsym, ternary1sym, colonsym, incrementsym, decrementsym,
    landsym, lorsym, lnotsym, borsym, xorsym, derefsym, bandaddrofsym,
    leftshiftsym, rightshiftsym, leftshiftasym, rightshiftasym, plusasym, minusasym, 
    multiplyasym, divideasym, moduloasym, andeqsym, oreqsym, xoreqsym,
    intliteralsym, stringliteralsym, charliteralsym, fpliteralsym, negsym, identifiersym, errorsym
} lextokens;

char tokens[90][20] = {
    "else ", "if ", "int ", "print ", "read ", "return ", "while ",
    "semicolon ", "comma ", "opencurly ", "closecurly ", "opensquare ",
    "closesquare ", "openbracket ", "closebracket ", "tildecompl ", "period ",
    "hash ", "divide ", "multiplyindirect ", "modulo ", "plus ", "minus ", "assign ", "eq ",
    "ne ", "lt ", "le ", "gt ", "ge ", "eof ", "auto ", "double ", "struct ",
    "break ", "long ", "switch ", "case ", "enum ", "register ", "typedef ", "char ",
    "extern ", "union ", "const ", "float ", "short ", "unsigned ", "continue ",
    "for ", "signed ", "void ", "default ", "goto ", "sizeof ", "volatile ",
    "do ", "static ", "type ", "alignof ", "ternary1 ", "colon ", "increment ", "decrement ",
    "land ", "lor ", "lnot ", "bor ", "xor ", "deref ", "bandaddrof ",
    "leftshift ", "rightshift ", "leftshifta ", "rightshifta ", "plusa ", "minusa ",
    "multiplya ", "dividea ", "moduloa ", "andeq ", "oreq ", "xoreq ",
    "intliteral ", "stringliteral ", "charliteral ", "fpliteral ", "neg ", "identifier ", "errorsym"
};

lextokens lextoken;
lextokens result;

lextokens lex(FILE*);

char identifier[MAXIDLEN+1];
char string[509];
char ch;
char numstring[20];

char charval;
int ival = 0;
long double fpval = 0.0;
int negflag = 0;
int fpflag = 0;

int incomment = 0;

extern lextokens lex(FILE* fp) {
    while (isspace(ch)) ch = getc(fp);

    switch (ch) {
    //single character non duplicated tokens
    case ';': lextoken = semicolonsym; ch = getc(fp); return lextoken;
    case ',': lextoken = commasym; ch = getc(fp); return lextoken;
    case '?': lextoken = ternary1sym; ch = getc(fp); return lextoken;
    case ':': lextoken = colonsym; ch = getc(fp); return lextoken;
    case '(': lextoken = openbracketsym; ch = getc(fp); return lextoken;
    case ')': lextoken = closebracketsym; ch = getc(fp); return lextoken;
    case '{': lextoken = opencurlysym; ch = getc(fp); return lextoken;
    case '}': lextoken = closecurlysym; ch = getc(fp); return lextoken;
    case '[': lextoken = opensquaresym; ch = getc(fp); return lextoken;
    case ']': lextoken = closesquaresym; ch = getc(fp); return lextoken;
    case '%': lextoken = modulosym; ch = getc(fp); return lextoken;
    case '~': lextoken = tildecomplsym; ch = getc(fp); return lextoken;
    case '.': lextoken = periodsym; ch = getc(fp); return lextoken;
    case '#': lextoken = hashsym; ch = getc(fp); return lextoken;
    case EOF: lextoken = eofsym; return lextoken;

    case '+':
        ch = getc(fp);
        if (ch == '+') {
            ch = getc(fp);
            lextoken = incrementsym;
            return lextoken;
        }
        else if (ch == '=') {
            ch = getc(fp);
            lextoken = plusasym;
            return lextoken;
        }
        else {
            lextoken = plussym;
            return lextoken;
        }
    case '-': 
        ch = getc(fp);
        if (ch == '-') {
            ch = getc(fp);
            lextoken = decrementsym;
            return lextoken;
        }
        else if (ch == '=') {
            ch = getc(fp);
            lextoken = minusasym;
            return lextoken;
        }
        else if (ch == '>') {
            ch = getc(fp);
            lextoken = derefsym;
            return lextoken;
        }
        else if (isdigit(ch)) {
            negflag = 1;
            lextoken = negsym;
            return lextoken;
        }
        else {
            lextoken = minussym;
            return lextoken;
        }
    case '*': 
        ch = getc(fp);
        if (ch == '=') {
            ch = getc(fp);
            lextoken = multiplyasym;
            return lextoken;
        }
        else {
            lextoken = multiplyindirectsym;
            return lextoken;
        }
    case '|':
        ch = getc(fp);
        if (ch == '|') {
            ch = getc(fp);
            lextoken = lorsym;
            return lextoken;
        }
        else if (ch == '=') {
            ch = getc(fp);
            lextoken = oreqsym;
            return lextoken;
        }
        else {
            lextoken = borsym;
            return lextoken;
        }
    case '^':
        ch = getc(fp);
        if (ch == '=') {
            ch = getc(fp);
            lextoken = xoreqsym;
            return lextoken;
        }
        else {
            lextoken = xorsym;
            return lextoken;
        }
    case '&':
        ch = getc(fp);
        if (ch == '&') {
            ch = getc(fp);
            lextoken = landsym;
            return lextoken;
        }
        else if (ch == '=') {
            ch = getc(fp);
            lextoken = andeqsym;
            return lextoken;
        }
        else {
            lextoken = bandaddrofsym;
            return lextoken;
        }
    
    //comparison operators
    case'<':
        ch = getc(fp);
        if (ch == '=') {
            lextoken = lesym;
            ch = getc(fp);
            return lextoken;
        }
        else if (ch == '<') {
            ch = getc(fp);
            if (ch == '=') {
                lextoken = leftshiftasym;
                ch = getc(fp);
                return lextoken;
            }
            else {
                lextoken = leftshiftsym;
                return lextoken;
            }
        }
        else {
            lextoken = ltsym;
            return lextoken;
        }
    case'>':
        ch = getc(fp);
        if (ch == '=') {
            lextoken = gesym;
            ch = getc(fp);
            return lextoken;
        }
        else if (ch == '>') {
            ch = getc(fp);
            if (ch == '=') {
                lextoken = rightshiftasym;
                ch = getc(fp);
                return lextoken;
            }
            else {
                lextoken = rightshiftsym;
                return lextoken;
            }
        }
        else {
            lextoken = gtsym;
            return lextoken;
        }
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
        if (ch == '=') {
            ch = getc(fp);
            lextoken = nesym;
            return lextoken;
        }
        else {
            lextoken = lnotsym;
            return lextoken;
        }
    //identifiers and reserved words
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm':
    case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
    {
        int i = 0;
        if (islower(ch)) {
            while (isalnum(ch)) {
                if (i < MAXIDLEN) {
                    //printf("%d\n", i);
                    identifier[i++] = ch;
                    ch = getc(fp);
                }
                else {
                    //printf("%s\n", identifier);
                    fprintf(stderr, "***Error - identifier longer than MAXIDLEN \n");
                    lextoken = errorsym;
                    return lextoken;
                }
            }
            identifier[i] = '\0';

            //improve the algorithm here
            //C reserved
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
            else if (strcmp(identifier, "return") == 0) {
                lextoken = returnsym;
                return lextoken;
            }
            else if (strcmp(identifier, "while") == 0) {
                lextoken = whilesym;
                return lextoken;
            }
            else if (strcmp(identifier, "auto") == 0) {
                lextoken = autosym;
                return lextoken;
            }
            else if (strcmp(identifier, "double") == 0) {
                lextoken = doublesym;
                return lextoken;
            }
            else if (strcmp(identifier, "struct") == 0) {
                lextoken = structsym;
                return lextoken;
            }
            else if (strcmp(identifier, "break") == 0) {
                lextoken = breaksym;
                return lextoken;
            }
            else if (strcmp(identifier, "long") == 0) {
                lextoken = longsym;
                return lextoken;
            }
            else if (strcmp(identifier, "switch") == 0) {
                lextoken = switchsym;
                return lextoken;
            }
            else if (strcmp(identifier, "case") == 0) {
                lextoken = casesym;
                return lextoken;
            }
            else if (strcmp(identifier, "enum") == 0) {
                lextoken = enumsym;
                return lextoken;
            }
            else if (strcmp(identifier, "register") == 0) {
                lextoken = registersym;
                return lextoken;
            }
            else if (strcmp(identifier, "typedef") == 0) {
                lextoken = typedefsym;
                return lextoken;
            }
            else if (strcmp(identifier, "char") == 0) {
                lextoken = charsym;
                return lextoken;
            }
            else if (strcmp(identifier, "extern") == 0) {
                lextoken = externsym;
                return lextoken;
            }
            else if (strcmp(identifier, "union") == 0) {
                lextoken = unionsym;
                return lextoken;
            }
            else if (strcmp(identifier, "const") == 0) {
                lextoken = constsym;
                return lextoken;
            }
            else if (strcmp(identifier, "float") == 0) {
                lextoken = floatsym;
                return lextoken;
            }
            else if (strcmp(identifier, "short") == 0) {
                lextoken = shortsym;
                return lextoken;
            }
            else if (strcmp(identifier, "unsigned") == 0) {
                lextoken = unsignedsym;
                return lextoken;
            }
            else if (strcmp(identifier, "continue") == 0) {
                lextoken = continuesym;
                return lextoken;
            }
            else if (strcmp(identifier, "for") == 0) {
                lextoken = forsym;
                return lextoken;
            }
            else if (strcmp(identifier, "signed") == 0) {
                lextoken = signedsym;
                return lextoken;
            }
            else if (strcmp(identifier, "void") == 0) {
                lextoken = voidsym;
                return lextoken;
            }
            else if (strcmp(identifier, "default") == 0) {
                lextoken = defaultsym;
                return lextoken;
            }
            else if (strcmp(identifier, "gotosym") == 0) {
                lextoken = gotosym;
                return lextoken;
            }
            else if (strcmp(identifier, "sizeof") == 0) {
                lextoken = sizeofsym;
                return lextoken;
            }
            else if (strcmp(identifier, "volatile") == 0) {
                lextoken = volatilesym;
                return lextoken;
            }
            else if (strcmp(identifier, "do") == 0) {
                lextoken = dosym;
                return lextoken;
            }
            else if (strcmp(identifier, "static") == 0) {
                lextoken = staticsym;
                return lextoken;
            }
            else if (strcmp(identifier, "type") == 0) {
                lextoken = typesym;
                return lextoken;
            }
            else if (strcmp(identifier, "alignof") == 0) {
                lextoken = alignofsym;
                return lextoken;
            }
            else if (strcmp(identifier, "not_eq") == 0) {
                lextoken = nesym;
                return lextoken;
            }
            else if (strcmp(identifier, "not") == 0) {
                lextoken = lnotsym;
                return lextoken;
            }
            else if (strcmp(identifier, "and") == 0) {
                lextoken = landsym;
                return lextoken;
            }
            else if (strcmp(identifier, "or") == 0) {
                lextoken = lorsym;
                return lextoken;
            }
            else if (strcmp(identifier, "compl") == 0) {
                lextoken = tildecomplsym;
                return lextoken;
            }
            else if (strcmp(identifier, "bitand") == 0) {
                lextoken = bandaddrofsym;
                return lextoken;
            }
            else if (strcmp(identifier, "bitor") == 0) {
                lextoken = borsym;
                return lextoken;
            }
            else if (strcmp(identifier, "xor") == 0) {
                lextoken = xorsym;
                return lextoken;
            }
            else if (strcmp(identifier, "and_eq") == 0) {
                lextoken = andeqsym;
                return lextoken;
            }
            else if (strcmp(identifier, "or_eq") == 0) {
                lextoken = oreqsym;
                return lextoken;
            }
            else if (strcmp(identifier, "xor_eq") == 0) {
                lextoken = xoreqsym;
                return lextoken;
            }
            //DL reserved
            else if (strcmp(identifier, "print") == 0) {
                lextoken = printsym;
                return lextoken;
            }
            else if (strcmp(identifier, "read") == 0) {
                lextoken = readsym;
                return lextoken;
            }
            else {
                lextoken = identifiersym;
                return lextoken;
            }
        }
    }
    //number literals
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    {
        int y = 0;
        while (isdigit(ch) || ch == '.' || ch == 'e') {
            if (ch == '.') {
                fpflag = 1;
            }
            numstring[y++] = ch;
            ch = getc(fp);
        }
        numstring[y] = '\0';

        //integer literal
        if (fpflag == 0) {
            int overflow = 0;
            ival = atoi(numstring);
            for (int u = 0; u < y; u++) {
                if (ival > INT_MAX / 10) overflow = 1;
                else if (ival * 10 > (INT_MAX - numstring[u] + '0')) overflow = 1;
                else ival = ival * 10 + numstring[u] - '0';
            }
            if (negflag == 1) {
                negflag = 0;
                ival = ival * -1;
            }
            if (overflow) {
                lextoken = errorsym;
                ival = INT_MAX;
                fprintf(stderr, "integer constant overflow\n");
                return lextoken;
            }
            else {
                lextoken = intliteralsym;
                return lextoken;
            }
        }
        //fp literal
        else {
            fpval = atof(numstring);
            
            if (fpval > LDBL_MAX) {
                lextoken = errorsym;
                fprintf(stderr, "floating-point constant overflow\n");
                fpflag = 0;
                return lextoken;
            }
            if (negflag == 1) {
                negflag = 0;
                fpval = fpval * -1;
            }
            fpflag = 0;
            lextoken = fpliteralsym;
            return lextoken;
        }

    }
    //comments and divide
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
            lextoken = lex(fp);
            return lextoken;
        }
        else if (ch == '=') {
            ch = getc(fp);
            lextoken = divideasym;
            return lextoken;
        }
        else if (ch == '/') {
            incomment = 1;
            ch = getc(fp);
            while (incomment) {
                if (ch == EOF) {
                    fprintf(stderr, "warning - end of file in comment\n");
                    lextoken = errorsym;
                    return lextoken;
                }
                else if (ch == '\n') {
                    ch = getc(fp);
                    incomment = 0;
                }
                else ch = getc(fp);
            }
            lextoken = lex(fp);
            return lextoken;
        }
        else {
            lextoken = dividesym;
            return lextoken;
        }

    //string literals
    case '\"':
        ch = getc(fp);
        int counter = 0;
        while (ch != '\"') {
            if (counter < 509) {
                string[counter++] = ch;
                ch = getc(fp);
            }
            else {
                fprintf(stderr, "***Error - string literal longer than max value \n");
                lextoken = errorsym;
                return lextoken;
            }
        }
        string[counter] = '\0';
        ch = getc(fp);
        lextoken = stringliteralsym;
        return lextoken;

    //char literals
    case '\'':
        ch = getc(fp);
        int counter2 = 0;
        while (ch != '\'') {
            if (counter2 < 2) {
                counter2++;
                charval = ch;
                ch = getc(fp);
            }
            else {
                fprintf(stderr, "***Error - char literal longer than one \n");
                lextoken = errorsym;
                return lextoken;
            }
        }
        ch = getc(fp);
        lextoken = charliteralsym;
        return lextoken;

    default:
        fprintf(stderr, "***Unexpected character %c\n", ch);
        lextoken = errorsym;
        return lextoken;
    }
}