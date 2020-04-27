%code requires{
#include "data.h"
#include <cstdint>

}

%{

#include "json.tab.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

extern "C"
int yywrap() {
   return 1;
}

char *strconcat(char *str1, char *str2);
static void yyerror(params *p, const char *);
int yylex();

struct params {
  void *data;
};

%}

%union {
  json::Int *i;
  json::Bool *b;
  json::String *s;
  json::BaseNode *base;
}

%token<s> STRING NONE
%token<i> NUMBER
%token<b> TRUE FALSE
%type<s> START OBJECT MEMBERS PAIR ARRAY
%type<base> VALUE ELEMENTS
%left O_BEGIN O_END A_BEGIN A_END
%left COMMA
%left COLON
%parse-param { struct params *p }

%%
START: ARRAY {
    printf("%s",$1);
  }
| OBJECT {
    printf("%s",$1);
  }
;
OBJECT: O_BEGIN O_END {
    $$ = nullptr;
  }
| O_BEGIN MEMBERS O_END {
    $$ = nullptr;
  }
;
MEMBERS: PAIR {
    $$ = $1;
  }
| PAIR COMMA MEMBERS {
    $$ = nullptr;
  }
;
PAIR: STRING COLON VALUE {
    $$ = nullptr;
  }
;
ARRAY: A_BEGIN A_END {
    $$ = nullptr;
  }
| A_BEGIN ELEMENTS A_END {
    $$ = nullptr;
}
;
ELEMENTS: VALUE {
    $$ = $1;
  }
| VALUE COMMA ELEMENTS {
    $$ = nullptr;
  }
;
VALUE: STRING {$$=nullptr;//yylval;
}
| NUMBER {$$=nullptr;//yylval;
}
| OBJECT {$$=$1;}
| ARRAY {$$=$1;}
| TRUE {$$=$1;}
| FALSE {$$=$1;}
| NONE {$$=$1;}
;
%%
int main()
{
   printf("\n");
   struct params p;
   yyparse(&p);
   printf("\n");
   return 0;
}
static void yyerror (params *p, const char *s) {
  fprintf(stderr, "%s\n", s);
}
char *strconcat(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char *str3 = (char *)malloc(sizeof(char)*(len1+len2+1));
    strcpy(str3,str1);
    strcpy(&(str3[len1]),str2);
    return str3;
}
