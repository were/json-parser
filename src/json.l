%{

#include <cstdint>
#include <stdio.h>

#include "data.h"

#include "json.tab.h"
char *strclone(char *str);

%}

DIGIT1to9 [1-9]
DIGIT [0-9]
DIGITS {DIGIT}+
INT {DIGIT}|{DIGIT1to9}{DIGITS}|-{DIGIT}|-{DIGIT1to9}{DIGITS}
FRAC [.]{DIGITS}
EXP {E}{DIGITS}
E [eE][+-]?
HEX_DIGIT [0-9a-f]
NUMBER {INT}|{INT}{FRAC}|{INT}{EXP}|{INT}{FRAC}{EXP}
UNESCAPEDCHAR [ -!#-\[\]-~]
ESCAPEDCHAR \\["\\bfnrt/]
UNICODECHAR \\u{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}
CHAR {UNESCAPEDCHAR}|{ESCAPEDCHAR}|{UNICODECHAR}
CHARS {CHAR}+
DBL_QUOTE ["]
%%

{DBL_QUOTE}{DBL_QUOTE} |
{DBL_QUOTE}{CHARS}{DBL_QUOTE} {
    yylval.s = new json::String(yytext);
    return STRING;
};
{NUMBER} {
    yylval.i = new json::Int(atol(yytext));
    return NUMBER;
}
TRUE {
    yylval.b = new json::Bool(true);
    return TRUE;
};
FALSE {
    yylval.b = new json::Bool(true);
    return FALSE;
};
NONE {
    yylval.s = new json::String(yytext);
    return NONE;
};
\{ {
    return O_BEGIN;
};

\} {
    return O_END;
};

\[ {
    return A_BEGIN;
};

\] {
    return A_END;
};

, {
    return COMMA;
};
: {
    return COLON;
};

[ \t\n]+ /* ignore whitespace */;

. {
    printf("Unexpected: %c\nExiting...\n",*yytext);
    exit(0);
}
%%
char *strclone(char *str) {
  int len = strlen(str);
  char *clone = (char*) malloc(sizeof(char) * (len+1));
  strcpy(clone, str);
  clone[len] = 0;
  return clone;
}
