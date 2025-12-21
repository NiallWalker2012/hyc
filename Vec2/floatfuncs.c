#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void Vec_new_float(floatVec *vecVar) {
	vecVar->size = 0;
	vecVar->capacity = 1;
	if ((vecVar->conts = malloc(sizeof(float))) == NULL) {
		perror("malloc");
		exit(1);
	}
	return;
}

void Vec_push_float(floatVec *vecVar, float conts) {
	size_t index = vecVar->size;
	vecVar->size++;
	if (vecVar->size >= vecVar->capacity) {
		vecVar->capacity *= 2;
		if ((vecVar->conts = realloc(vecVar->conts, vecVar->capacity * sizeof(float))) == NULL) {
			free(vecVar->conts);
			perror("realloc");
			exit(1);
		}
	}
	vecVar->conts[index] = conts;
	return;
}

float Vec_get_float(floatVec *vecVar, int index) {
	return vecVar->conts[index];
}

void Vec_free_float(floatVec *vecVar) {
	free(vecVar->conts);
	return;
}

