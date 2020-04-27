%option prefix="JSON"

%{

#include <cstdint>
#include <stdio.h>

#include "json/data.h"
#include "json/visitor.h"

extern int JSONlineno;
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
    int len = strlen(JSONtext) - 2;
    std::string str(JSONtext + 1, JSONtext + 1 + len);
    JSONlval.s = new json::String(str);
    return STRING;
};
{NUMBER} {
    JSONlval.i = new json::Int(atol(JSONtext));
    return NUMBER;
}
true {
    JSONlval.b = new json::Bool(true);
    return TRUE;
};
false {
    JSONlval.b = new json::Bool(true);
    return FALSE;
};
NONE {
    JSONlval.s = new json::String(JSONtext);
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

%%
char *strclone(char *str) {
  int len = strlen(str);
  char *clone = (char*) malloc(sizeof(char) * (len+1));
  strcpy(clone, str);
  clone[len] = 0;
  return clone;
}
