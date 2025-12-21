#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void Vec_new_int(intVec *vecVar) {
	vecVar->size = 0;
	vecVar->capacity = 1;
	if ((vecVar->conts = malloc(sizeof(int))) == NULL) {
		perror("malloc");
		exit(1);
	}
	return;
}

void Vec_push_int(intVec *vecVar, int conts) {
	size_t index = vecVar->size;
	vecVar->size++;
	if (vecVar->size >= vecVar->capacity) {
		vecVar->capacity *= 2;
		if ((vecVar->conts = realloc(vecVar->conts, vecVar->capacity * sizeof(int))) == NULL) {
			free(vecVar->conts);
			perror("realloc");
			exit(1);
		}
	}
	vecVar->conts[index] = conts;
	return;
}

int Vec_get_int(intVec *vecVar, int index) {
	return vecVar->conts[index];
}

void Vec_free_int(intVec *vecVar) {
	free(vecVar->conts);
	return;
}

