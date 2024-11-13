%{
int COMMENT = 0;
%}

identifier [a-zA-Z][a-zA-Z0-9]*

%%

#.* { 
    printf("\n%s is a Preprocessor Directive", yytext); 
}

int |
float |
main |
if |
else |
printf |
scanf |
for |
char |
getch |
while { 
    printf("\n%s is a Keyword", yytext); 
}

"/*" { 
    COMMENT = 1; 
}

"*/" { 
    COMMENT = 0; 
}

{identifier}\( { 
    if (!COMMENT) 
        printf("\nFunction:\t%s", yytext); 
}

\{ { 
    if (!COMMENT) 
        printf("\nBlock Begins"); 
}

\} { 
    if (!COMMENT) 
        printf("\nBlock Ends"); 
}

{identifier}(\[[0-9]*\])? { 
    if (!COMMENT) 
        printf("\n%s is an Identifier", yytext); 
}

\".*\" { 
    if (!COMMENT) 
        printf("\n%s is a String", yytext); 
}

[0-9]+ { 
    if (!COMMENT) 
        printf("\n%s is a Number", yytext); 
}

\)(\;)? { 
    if (!COMMENT) {
        printf("\t");
        ECHO;
        printf("\n");
    }
}

\( { 
    ECHO; 
}

= { 
    if (!COMMENT) 
        printf("\n%s is an Assignment Operator", yytext); 
}

\<= |
\>= |
\< |
== { 
    if (!COMMENT) 
        printf("\n%s is a Relational Operator", yytext); 
}

.|\n

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file;
        file = fopen(argv[1], "r");
        if (!file) {
            printf("\nCould not open the file: %s", argv[1]);
            exit(0);
        }
        yyin = file;
    }
    yylex();
    printf("\n\n");
    return 0;
}

int yywrap() {
    return 1;
}
