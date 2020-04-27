%code requires{

#include "json/data.h"
#include "json/visitor.h"
#include <cstdint>

struct params {
  json::BaseNode *data;
};

extern int yylineno;

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

static void yyerror(params *p, const char *);
int yylex();

%}

%union {
  json::Int *i;
  json::Bool *b;
  json::String *s;
  json::BaseNode *base;
  json::Array *a;
  json::Object *o;
}

%token<s> STRING NONE
%token<i> NUMBER
%token<b> TRUE FALSE
%type<base> START VALUE
%type<a> ELEMENTS ARRAY
%type<o> PAIR OBJECT MEMBERS
%left O_BEGIN O_END A_BEGIN A_END
%left COMMA
%left COLON
%parse-param { struct params *p }

%%
START: ARRAY {
         $$ = p->data = $1;
       }
       | OBJECT {
         $$ = p->data = $1;
       };

OBJECT: O_BEGIN O_END {
        plain::Object empty;
        $$ = new json::Object(empty);
      }
      | O_BEGIN MEMBERS O_END {
        $$ = $2;
      };

MEMBERS: PAIR {
         $$ = $1;
       }
       | MEMBERS COMMA PAIR {
         // TODO(@were): This may cause a moderate memory leakage.
         //              Since I only supported a recursive destructor for now.
         //              I cannot delete $3 without a ref count --- it is kinda
         //              terrible to have a three-level pointer --- the underlying
         //              data, the ref, and converting the ref to a pointer POD.
         //              A quick hack to this is to write a duplication visitor.
         auto *pr = $3->As<plain::Object>();
         assert(pr && pr->size() == 1);
         auto &elem = *pr->begin();
         auto *mems = $1->As<plain::Object>();
         assert(mems);
         (*mems)[elem.first] = elem.second;
         $$ = $1;
       };

PAIR: STRING COLON VALUE {
      plain::Object obj;
      obj[*$1->As<std::string>()] = $3;
      $$ = new json::Object(obj);
      delete $1;
    };

ARRAY: A_BEGIN A_END {
       std::vector<json::BaseNode*> empty;
       $$ = new json::Array(empty);
     }
     | A_BEGIN ELEMENTS A_END {
       $$ = $2;
     };

ELEMENTS: VALUE {
          std::vector<json::BaseNode*> a{$1};
          $$ = new json::Array(a);
        }
        | ELEMENTS COMMA VALUE {
          $1->As<plain::Array>()->push_back($3);
          $$ = $1;
        };

VALUE: STRING { $$=$1; }
     | NUMBER { $$=$1; }
     | OBJECT { $$=$1; }
     | ARRAY  { $$=$1; }
     | TRUE   { $$=$1; }
     | FALSE  { $$=$1; }
     | NONE   { $$=$1; }
     ;
%%

static void yyerror (params *p, const char *s) {
  fprintf(stderr, "%d: %s\n", yylineno, s);
}
