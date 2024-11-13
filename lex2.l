%{
%}

%s Q1 Q2 DEAD

%%

<INITIAL>1           BEGIN Q1;
<INITIAL>0           BEGIN INITIAL;
<INITIAL>[^01\n]     BEGIN DEAD;
<INITIAL>\n          BEGIN INITIAL; { printf("Not Accepted\n"); }

<Q1>1                BEGIN Q2;
<Q1>0                BEGIN INITIAL;
<Q1>[^01\n]          BEGIN DEAD;
<Q1>\n               BEGIN INITIAL; { printf("Not Accepted\n"); }

<Q2>1                BEGIN Q2;
<Q2>0                BEGIN INITIAL;
<Q2>[^01\n]          BEGIN DEAD;
<Q2>\n               BEGIN INITIAL; { printf("Accepted\n"); }

<DEAD>[^\n]          BEGIN DEAD;
<DEAD>\n             BEGIN INITIAL; { printf("Invalid\n"); }

%%

int main() {
    printf("Enter String\n");
    yylex();
    return 0;
}
