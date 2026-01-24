#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void Vec_new_char(charVec *vecVar) {
	vecVar->size = 0;
	vecVar->capacity = 1;
	if ((vecVar->conts = malloc(sizeof(char))) == NULL) {
		perror("malloc");
		exit(1);
	}
	return;
}

int Vec_push_char(charVec *vecVar, char conts) {
	size_t index = vecVar->size;
	vecVar->size++;
	if (vecVar->size >= vecVar->capacity) {
		vecVar->capacity += 4;
		if ((vecVar->conts = realloc(vecVar->conts, vecVar->capacity * sizeof(char))) == NULL) {
			free(vecVar->conts);
			perror("realloc");
			return 1;
		}
	}
	vecVar->conts[index] = conts;
	return 0;
}

char Vec_get_char(charVec *vecVar, int index) {
	return vecVar->conts[index];
}

void Vec_free_char(charVec *vecVar) {
	free(vecVar->conts);
	return;
}

