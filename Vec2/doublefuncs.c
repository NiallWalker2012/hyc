#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void Vec_new_double(doubleVec *vecVar) {
	vecVar->size = 0;
	vecVar->capacity = 1;
	if ((vecVar->conts = malloc(sizeof(double))) == NULL) {
		perror("malloc");
		exit(1);
	}
	return;
}

void Vec_push_double(doubleVec *vecVar, double conts) {
	size_t index = vecVar->size;
	vecVar->size++;
	if (vecVar->size >= vecVar->capacity) {
		vecVar->capacity *= 2;
		if ((vecVar->conts = realloc(vecVar->conts, vecVar->capacity * sizeof(double))) == NULL) {
			free(vecVar->conts);
			perror("realloc");
			exit(1);
		}
	}
	vecVar->conts[index] = conts;
	return;
}

double Vec_get_double(doubleVec *vecVar, int index) {
	return vecVar->conts[index];
}

void Vec_free_double(doubleVec *vecVar) {
	free(vecVar->conts);
	return;
}

