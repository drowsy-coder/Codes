%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex();
int count = 0;

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int countTs(const char *word) {
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == 't' || word[i] == 'T') {
            count++;
        }
    }
    return count;
}

%}

%union {
    char *str;
}

%token <str> WORD

%%

input:
    | input line
    ;

line:
    WORD {
        int t_count = countTs($1);
        if (t_count == 3) {
            printf("%s\n", $1);
            count++;
        }
        free($1);
    }
    ;

%%

int main() {
    printf("Enter text (Ctrl+D to end):\n");
    yyparse();
    printf("Count: %d\n", count);
    return 0;
}
