#ifndef LEX_BASE_H
#define LEX_BASE_H

#include <stddef.h>

typedef enum {
	FUNCTION,
	DIGIT,
	D_POINT,
	METHOD,
	DATA_TYPE,
	VARIABLE,
	DEFINER,
	OPERATOR,
	SEL_OP,	
	SELECT_OP,
	PARENTHESIS,
	DECLARATION,
	ELSE,
	ERR,
	ABORT,
	STATE_END,
} LexType;

typedef struct {
	LexType token;
	const char *lexeme;
	size_t length;
} LexStruct;

// Lex vector structure
typedef struct {
	size_t size;
	size_t capacity;
	LexStruct *conts;
} lexVec;


void Vec_new_lex(lexVec *vecVar);
int Vec_push_lex(lexVec *vecVar, LexStruct content);
LexStruct *lex(char *character);

#endif

