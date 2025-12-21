#include <stdio.h>
#include <stdbool.h>

int main() {
	bool boolVar;
	while (1) {
		if (boolVar || !boolVar) {
			break;
		}
	}
	printf("Finished, boolVar is %d\n", boolVar);

	return 0;
}
