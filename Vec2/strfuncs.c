#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void Vec_new_str(strVec *vecVar) {
	vecVar->size = 0;
	vecVar->capacity = 1;
	if ((vecVar->conts = malloc(sizeof(char *))) == NULL) {
		perror("malloc");
		exit(1);
	}
	return;
}

void Vec_push_str(strVec *vecVar, char *conts) {
	size_t index = vecVar->size;
	vecVar->size++;
	if (vecVar->size >= vecVar->capacity) {
		vecVar->capacity += 4;
		if ((vecVar->conts = realloc(vecVar->conts, vecVar->capacity * sizeof(char *))) == NULL) {
			free(vecVar->conts);
			perror("realloc");
			exit(1);
		}
	}
	vecVar->conts[index] = conts;
	return;
}

char *Vec_get_str(strVec *vecVar, int index) {
	return vecVar->conts[index];
}

void Vec_free_str(strVec *vecVar) {
	free(vecVar->conts);
	return;
}
