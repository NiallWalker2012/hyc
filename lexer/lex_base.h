#ifndef LEX_BASE_H
#define LEX_BASE_H

#include <stddef.h>
#include <stdbool.h>

// Lexeme types
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
	long int length;
} LexStruct;

// Lex vector structure
typedef struct {
	size_t size;
	size_t capacity;
	LexStruct *conts;
} lexVec;

// lex_vecs.c
void Vec_new_lex(lexVec *vecVar);
int Vec_push_lex(lexVec *vecVar, LexStruct content);

// lex.c
typedef struct {
	bool elseSearch;
	bool elseFin;
	bool autoLex;
} elseVars;

LexStruct *lex(char *character);
void elseDisable(elseVars *vars);


// # Checks for data types e.g. int; functions e.g. print("...");

// data_type_check.c
bool isDataType(const char *string);

// func_check.c
typedef struct {
	const char *type;
	char value[256];
} FuncResult;

void slice(const char *string, char *result, size_t start, size_t end);
FuncResult isFunc(const char *string);

#endif

