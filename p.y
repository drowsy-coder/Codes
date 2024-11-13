%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int flag = 0;
int yylex();
void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%right '^'
%left '(' ')'

%%

ArithmeticExpression: E {
    printf("\nValid parentheses\n");
    return 0;
};

E: E '+' E {
    $$ = $1 + $3;
}
| E '-' E {
    $$ = $1 - $3;
}
| E '*' E {
    $$ = $1 * $3;
}
| E '/' E {
    if ($3 == 0) {
        yyerror("Division by zero error");
    } else {
        $$ = $1 / $3;
    }
}
| E '%' E {
    $$ = $1 % $3;
}
| '(' E ')' {
    $$ = $2;
}
| NUMBER {
    $$ = $1;
}
;

%%

int main() {
    printf("\nEnter Any Expression:\n");
    yyparse();
    if (flag == 0)
        printf("\n\n");
    return EXIT_SUCCESS;
}

void yyerror(const char *s) {
    printf("Invalid Parenthesis\n");
    flag = 1;
}
