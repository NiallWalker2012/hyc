#include <string.h>
#include <stdio.h>

char *slice(const char *str, char *result, const size_t start, const size_t end) {
    return strncpy(result, str + start, end - start);
}

int main() {
    const char *str = "print(\"Hello\")";
    char result[strlen(str) + 1];
    slice(str, result, 0, strlen("print("));

    if (strcmp(result, "print(") == 0) {
        char arg[strlen(str) + 1];
        slice(str, arg, strlen("print("), strlen(str) - 1);

        
        printf("FUNCTION: print()\nARG: %s\n", arg);
    }
    printf("%c\n", str[strlen(str) - 1]);

    return 0;
}