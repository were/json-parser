#include "json.lex.h"
#include "json.tab.h"
#include "json/value.h"
#include "json/printer.h"

namespace Json {

Value parseJSON(const char *fname);

}
