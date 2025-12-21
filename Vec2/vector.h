#ifndef VECTOR_H
#define VECTOR_H

#include "../lexer/lex_base.h"
#include <stddef.h>

// String vector structure
typedef struct {
	size_t size;
	size_t capacity;
	char **conts;
} strVec;

// Int vector structure
typedef struct {
	size_t size;
	size_t capacity;
	int *conts;
} intVec;

// Char vector structure
typedef struct {
	size_t size;
	size_t capacity;
	char *conts;
} charVec;

// Double vector structure
typedef struct {
	size_t size;
	size_t capacity;
	double *conts;
} doubleVec;

// Float vector structure
typedef struct {
	size_t size;
	size_t capacity;
	float *conts;
} floatVec;




// # Definitions for generic functions:

// Vec_new functions:
#define Vec_new(x) _Generic((x),    \
    strVec*: Vec_new_str,           \
    intVec*: Vec_new_int,           \
    charVec*: Vec_new_char,         \
    doubleVec*: Vec_new_double,     \
    floatVec*: Vec_new_float,       \
)(x)

// Vec_push functions:
#define Vec_push(x, y) _Generic((x), \
    strVec*: Vec_push_str,              \
    intVec*: Vec_push_int,              \
    charVec*: Vec_push_char,            \
    doubleVec*: Vec_push_double,        \
    floatVec*: Vec_push_float,          \
)(x, y)

// Vec_get functions:
#define Vec_get(x, y) _Generic((x), \
    strVec*: Vec_get_str,           \
    intVec*: Vec_get_int,           \
    charVec*: Vec_get_char,         \
    doubleVec*: Vec_get_double,     \
    floatVec*: Vec_get_float,        \
)(x, y)

// Vec_free functions:
#define Vec_free(x) _Generic((x), \
    strVec*: Vec_free_str,        \
    intVec*: Vec_free_int,        \
    charVec*: Vec_free_char,      \
    doubleVec*: Vec_free_double,  \
    floatVec*: Vec_free_float,     \
)(x)


// String functions
void Vec_new_str(strVec *vecVar);
void Vec_push_str(strVec *vecVar, char *conts);
char *Vec_get_str(strVec *vecVar, int index);
void Vec_free_str(strVec *vecVar);

// Int functions
void Vec_new_int(intVec *vecVar);
void Vec_push_int(intVec *vecVar, int conts);
int Vec_get_int(intVec *vecVar, int index);
void Vec_free_int(intVec *vecVar);

// Char functions
void Vec_new_char(charVec *vecVar);
void Vec_push_char(charVec *vecVar, char conts);
char Vec_get_char(charVec *vecVar, int index);
void Vec_free_char(charVec *vecVar);

// Double functions
void Vec_new_double(doubleVec *vecVar);
void Vec_push_double(doubleVec *vecVar, double conts);
double Vec_get_double(doubleVec *vecVar, int index);
void Vec_free_double(doubleVec *vecVar);


// Float functions
void Vec_new_float(floatVec *vecVar);
void Vec_push_float(floatVec *vecVar, float conts);
float Vec_get_float(floatVec *vecVar, int index);
void Vec_free_float(floatVec *vecVar);


// We made it eventually...

#endif
