#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lexer/lex_base.h"

int main(int argc, char *argv[]) {
	#ifndef __unix__
		fputs("As of right now, the hyc Hydro compiler is only compatible in ", stderr);
		fputs("unix-like operating systems\nIn the future, this will be fixed\n", stderr);
		return 4;
	#endif

	int exit_code = 0;
	// Validate the command line arguments and print necessary messages
	if (argc == 1) {
		puts("No expected arguments found\nRun with --help for more info");
		return 2;
	}

	if (strcmp(argv[1], "--help") == 0 ||
	 	strcmp(argv[1], "-h") == 0) {

		puts("hyc: The Official Hydro Compiler");
		fputs("Hydro is a Lightweight Programming Language aimed to have the ", stderr);
		fputs("extensive standard library and OOP features of C++ with the simple syntax and predictability of C\n\n", stderr);
		puts("Usage: ./hyc <TARGET FILE> <COMPILE FILE>");
		return 3;
	}

	if (argc != 3) {
		printf("%d too %s arguments - 2 expected\nRun with --help for more info\n", 
		 	(argc > 3) ? (argc - 3) : (3 - argc),
		 	(argc > 3) ? "many" : "few"
		);
		return 2;
	}
	
	// Open the specified argument for reading
	FILE *fPtr = fopen(argv[1], "r");
	if (!fPtr) {
		perror("fopen");
		return 1;
	}

	// Get the byte length of the file
	fseek(fPtr, 0, SEEK_END);
	long long size = ftell(fPtr);
	if (size < 0) {
		fclose(fPtr);
		perror("ftell");
		return 1;
	}
	fseek(fPtr, 0, SEEK_SET);
	
	// Read the contents into heap allocated conts variable
	char *conts = malloc((size_t)size + 1);
	if (!conts) {
		fclose(fPtr);
		perror("malloc");
		return 1;
	}

	size_t read = fread(conts, 1, size, fPtr);
	if (read != (size_t)size) {
		perror("fread");
		free(conts);
		fclose(fPtr);
		return 1;
	}
	// NULL terminate the string
	conts[size] = '\0';

	LexStruct *lexed_conts = lex((char *)conts);

	int errCount = 0;

	for (long int i = 0; i < lexed_conts[0].length; i++) {
		if (lexed_conts[i].token == ERR) {
			errCount++;
		} else if (lexed_conts[i].token == ABORT) {
			exit_code = 1;
			goto FREE;
		}
	}

	if (errCount > 0) {
		fprintf(stderr, "Compile aborted with exit status 1 due to %d %s\n", 
		  	errCount,
		  	(errCount > 1) ? "errors" : "error"
		);
		exit_code = 1;
	}


	FREE:
		for (long int i = 0; i < lexed_conts[0].length; i++) {
			if (lexed_conts[i].lexeme != NULL) {
				free((void *)lexed_conts[i].lexeme);
			}
		}
		
		free(lexed_conts);
		free(conts);

		fclose(fPtr);


		return exit_code;
}
