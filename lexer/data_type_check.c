#include <string.h>
#include <stdbool.h>

#include "lex_base.h"

bool isDataType(const char *string) {
    return (strcmp(string, "char") == 0 ||
            strcmp(string, "int") == 0 ||
            strcmp(string, "float") == 0 ||
            strcmp(string, "double") == 0 ||
            strcmp(string, "str") == 0 ||
            strcmp(string, "bool") == 0) ? true : false;
}
