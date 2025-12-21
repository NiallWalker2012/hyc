#include <stdlib.h>
#include <stdio.h>

#include "lex_base.h"


void Vec_new_lex(lexVec *vecVar) {
	vecVar->size = 0;
	vecVar->capacity = 1;
	if ((vecVar->conts = malloc(sizeof(LexStruct))) == NULL) {
		perror("malloc");
		exit(1);
	}
	return;
}

int Vec_push_lex(lexVec *vecVar, LexStruct conts) {
	size_t index = vecVar->size;
	vecVar->size++;
	if (vecVar->size >= vecVar->capacity) {
		vecVar->capacity += 4;
		LexStruct *newData = realloc(vecVar->conts, vecVar->capacity * sizeof(LexStruct));
		if (!newData) {
			free(vecVar->conts);
			perror("realloc");
			return 1;
		}
		vecVar->conts = newData;
	}
	vecVar->conts[index] = conts;
	return 0;
}
