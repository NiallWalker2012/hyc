#include <string.h>
#include <stdbool.h>

#include "lex_base.h"

void slice(const char *str, char *result, size_t start, size_t end);
FuncResult func_check(const char *str, const char *func);

FuncResult isFunc(const char *str) {
    FuncResult r;

    r = func_check(str, "print(");
    if (r.type[0] != '\0')
        return r;

    r = func_check(str, "uin(");
    if (r.type[0] != '\0')
        return r;

    if (strcmp(r.type, "err") == 0) {
        return r;
    }
    return (FuncResult){ "err", "Function not declared" };
}

FuncResult func_check(const char *str, const char *func) {
    FuncResult res = { "", "" };

    size_t func_len = strlen(func);
    size_t str_len  = strlen(str);

    if (str_len < func_len)
        return res;

    char temp[str_len + 1];
    slice(str, temp, 0, func_len);

    if (strcmp(temp, func) != 0)
        return res;

    if (str[str_len - 1] != ')') {
        res.type = "err";
        strcpy(res.value,
            "Syntax Error: Function parenthesis not closed. Expected ')'");
        return res;
    }

    slice(str, res.value, func_len, str_len - 1);

    if (strlen(res.value) == 0) {
        res.type = "err";
        strcpy(res.value, "Expected 1 argument. None found");
        return res;
    }

    res.type = func;  // "print(" or "uin("
    return res;
}


void slice(const char *str, char *result, size_t start, size_t end) {
    size_t len = end - start;
    memcpy(result, str + start, len);
    result[len] = '\0';
}