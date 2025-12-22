#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

#include "lex_base.h"

// This messy rubbish was made by me!
LexStruct *lex(char *conts) {
	lexVec total_lex;
	Vec_new_lex(&total_lex);

	// For some reason, if I don't initialise seperately 
	// weird things start happening
	// No idea why lol
	int decCount = 0;
	int count = 0;
	int lineCount = 0;
	int errCount = 0;
	bool digitSearch = false;
	bool commentSearch = false;
	bool isSingCom = false;
	bool isMultCom = false;
	bool multComEnd = false;
	// Its probably a really stupid mistake
	

	for (unsigned __int128 i = 0; conts[i] != '\0'; i++) {
		LexStruct lexVar;
		
		// Once apon a time I was a never-nester...
		if (isSingCom) {
			if (conts[i] == '\n') {
				isSingCom = false;
			} else {
				continue;
			}
		}

		if (multComEnd) {
			if (conts[i] == '/') {
				multComEnd = false;
				isMultCom = false;
			}
			continue;
		}

		if (isMultCom) {
			if (conts[i] == '*') {
				multComEnd = true;
			}
			continue;
		}

		if (commentSearch) {
			if (conts[i] == '/') {
				isSingCom = true;
				continue;
			} else if (conts[i] == '*') {
				isMultCom = true;
				continue;
			} 
			commentSearch = false;
		}

		// Check for line
		if (conts[i] == '\n') {
			lineCount++;
		}
		// Check for start of comment
		if (conts[i] == '/') {
			commentSearch = true;
		}
	
		// Handle numbers
		if (digitSearch) {
			if (isdigit(conts[i])) {
				lexVar.token = DIGIT;
				goto PUSH;
			} else if (conts[i] == '.') {
				decCount++;
				if (decCount > 1) {
					// Ultra-wide monitor is necessary
					fprintf(stderr, "Error on line %d: Invalid number due to multiple decimal points\n\n", lineCount + 1);
					lexVar.token = ERR;
					errCount++;
					goto PUSH;
				}
				lexVar.token = D_POINT;
				goto PUSH;
			} else {
				digitSearch = false;
				decCount = 0;
				goto PUSH;
			}
		}

		if (isdigit(conts[i])) {
			lexVar.token = DIGIT;
			digitSearch = true;
			goto PUSH;
		} else {
			digitSearch = false;
		}

		switch (conts[i]) {
			case ';':
				digitSearch = false;
				lexVar.token = STATE_END;
				goto PUSH;
			case '=':
				lexVar.token = IDENTIFIER;
				goto PUSH;
			default:
				break;
		}
		
		PUSH:
			// Ensure that there aren't over 20 errors
			if (errCount > 20) {
				fprintf(stderr, "\nCompile aborted as error-count has exceded 20\n");
				total_lex.conts[0].token = ABORT;
				return total_lex.conts;
			}
			
			// Automatically push the result to lexeme
			char *string = malloc(2);
			if (!string) {
				fprintf(stderr, "Out of memory\n");
				exit(1);
			}
			string[0] = conts[i];
			string[1] = '\0';

			lexVar.lexeme = string;

			// Push the result to total vector
			if ((Vec_push_lex(&total_lex, lexVar)) != 0) {
				fprintf(stderr, "Failed to push the lexed contents\n");
			}	

			count++;
	}
	
	total_lex.conts[0].length = count;
	return total_lex.conts;
}
