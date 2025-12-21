#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	if (chdir("..") != 0) {
		perror("chdir");
		return 1;
	}
	FILE *fptr = fopen("main.c", "r");
	if (!fptr) {
		perror("fopen");
		return 1;
	}

	fseek(fptr, 0, SEEK_END);
	size_t size = ftell(fptr);
	if (size < 0) {
		perror("ftell");
		return 1;
	}
	fseek(fptr, 0, SEEK_SET);

	printf("%zu\n", size);

	return 0;
}
