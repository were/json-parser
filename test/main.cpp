#include <cstdio>
#include "json.tab.h"

void yyrestart(FILE*);

int main(int argc, char *argv[]) {
   params p;
   yyrestart(fopen(argv[1], "r"));
   yyparse(&p);
   json::JSONPrinter printer(std::cout);
   p.data->Accept(&printer);
   return 0;
}