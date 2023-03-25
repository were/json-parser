%option prefix="JSON"

%{

#include <iostream>
#include <cstdint>
#include <stdio.h>

#include "json.tab.h"

extern int JSONlineno;
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
    int len = strlen(JSONtext);
    JSONlval.s = new std::string(JSONtext + 1, JSONtext + len - 1);
    return STRING;
};
{NUMBER} {
    JSONlval.i64 = atol(JSONtext);
    return NUMBER;
}
true {
    JSONlval.i64 = 1;
    return TRUE;
};
false {
    JSONlval.i64 = 0;
    return FALSE;
};
"null" {
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

"\n" {
}

[ \t]+ /* ignore whitespace */;

%%
char *strclone(char *str) {
  int len = strlen(str);
  char *clone = (char*) malloc(sizeof(char) * (len+1));
  strcpy(clone, str);
  clone[len] = 0;
  return clone;
}
