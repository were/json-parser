%define api.prefix {JSON}

%code requires{

#include <iostream>
#include <cstdint>
#include "json/value.h"

struct params {
  Json::Value data;
  std::vector<std::string> literals;
};

extern int JSONlineno;

}

%{

#include "json.tab.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

extern "C"
int JSONwrap() {
   return 1;
}

static void JSONerror(params *p, const char *);
int JSONlex();

%}

%union {
  Json::ValueBase *value;
  std::string *s;

  struct pair_t {
    std::string *key;
    Json::ValueBase *value;
  } ky_pair;
  int64_t i64;
  double d;
}

%token NONE
%token<i64> INT
%token<d> NUMBER
%token<i64> TRUE FALSE
%token<s> STRING
%left O_BEGIN O_END A_BEGIN A_END
%left COMMA
%left COLON

%type<value> start array object value elements members
%type<ky_pair> pair

%parse-param { struct params *p }

%%
start: array {
  $$ = $1;
  p->data = Json::Value($1);
}
| object {
  $$ = $1;
  p->data = Json::Value($1);
};

object: O_BEGIN O_END {
  $$ = new Json::ValueObject({});
}
| O_BEGIN members O_END {
  $$ = $2;
};

members: pair {
  std::map<std::string, Json::Value> data;
  data[*($1.key)] = Json::Value($1.value);
  delete $1.key;
  $$ = new Json::ValueObject(data);
}
| members COMMA pair {
  std::string ky(*$3.key);
  static_cast<Json::ValueObject*>($1)->val[ky] = Json::Value($3.value);
  delete $3.key;
  $$ = $1;
};

pair: STRING COLON value {
  $$.key = $1;
  $$.value = $3;
};

array: A_BEGIN A_END {
  $$ = new Json::ValueArray({});
}
| A_BEGIN elements A_END {
  $$ = $2;
};

elements: value {
  $$ = new Json::ValueArray({Json::Value($1)});
}
| elements COMMA value {
  static_cast<Json::ValueArray*>($1)->val.emplace_back($3);
};

value: STRING {
  $$ = new Json::ValueString(*$1);
  delete $1;
}
| INT {
  $$ = new Json::ValueInt($1);
}
| NUMBER {
  $$ = new Json::ValueDouble($1);
}
| object {
  $$ = $1;
}
| array  {
  $$ = $1;
}
| TRUE   {
  $$ = new Json::ValueBool((bool) $1);
}
| FALSE  {
  $$ = new Json::ValueBool((bool) $1);
}
| NONE   {
  $$ = new Json::ValueNull(nullptr);
}
;
%%

static void JSONerror (params *p, const char *s) {
  fprintf(stderr, "%d: %s\n", JSONlineno, s);
}
