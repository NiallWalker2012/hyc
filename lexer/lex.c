#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "lex_base.h"
#include "../Vec2/vector.h"


void elseDisable(elseVars *vars);

// This messy rubbish was made by me!
LexStruct *lex(char *conts) {
	lexVec total_lex;
	Vec_new_lex(&total_lex);

	charVec elseLex;
	Vec_new_char(&elseLex);

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
	
	elseVars elseV = { false, false, true };
	// Its probably a really stupid mistake
	

	for (unsigned __int128 i = 0; conts[i] != '\0'; i++) {
		LexStruct lexVar;

		if (elseV.elseFin) {
			lexVar.token = ELSE;
		}
		
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
				elseDisable(&elseV);
				goto PUSH;
			} else if (conts[i] == '.') {
				decCount++;
				if (decCount > 1) {
					fprintf(stderr, "Error on line %d: Invalid number due to multiple decimal points\n\n", lineCount + 1);
					lexVar.token = ERR;
					errCount++;
				    elseDisable(&elseV);
					goto PUSH;
				}
				lexVar.token = D_POINT;
				elseDisable(&elseV);
				goto PUSH;
			} else {
				digitSearch = false;
				decCount = 0;
				elseDisable(&elseV);
				goto PUSH;
			}
		}

		if (isdigit(conts[i])) {
			lexVar.token = DIGIT;
			digitSearch = true;
			elseDisable(&elseV);
			goto PUSH;
		} else {
			digitSearch = false;
		}
		
		// Check for operators
		switch (conts[i]) {
			case ';':
				digitSearch = false;
				lexVar.token = STATE_END;
				elseDisable(&elseV);
				goto PUSH;
			case '=':
				lexVar.token = DEFINER;
				elseDisable(&elseV);
				goto PUSH;
			case '+':
			case '-':
			case '*':
			case '/':
				lexVar.token = OPERATOR;
				elseDisable(&elseV);
				goto PUSH;
			case '>':
			case '<':
				lexVar.token = SELECT_OP;
				elseDisable(&elseV);
				goto PUSH;
			default:
				break;
		}

		Vec_push_char(&elseLex, conts[i]);
		elseV.elseSearch = true;
		elseV.autoLex = false;
		
		PUSH:
			// Ensure that there aren't over 20 errors
			if (errCount > 20) {
				fprintf(stderr, "\nCompile aborted as error-count has exceded 20\n");
				total_lex.conts[0].token = ABORT;
				return total_lex.conts;
			}
			
			// Automatically push the result to lexeme
			char buffer[2] = { conts[i], '\0' };
			char *string = strdup(buffer);
			if (!string) {
				perror("strdup");
				total_lex.conts[0].token = ABORT;
				return total_lex.conts;
			}
			
			if (elseV.autoLex) {
				lexVar.lexeme = string;
				// Push the result to total vector
				if ((Vec_push_lex(&total_lex, lexVar)) != 0) {
					fprintf(stderr, "Failed to push the lexed contents\n");
				}	
			}

			count++;
	}
	
	total_lex.conts[0].length = count;
	return total_lex.conts;
}

void elseDisable(elseVars *vars) {
	vars->elseSearch = false;
	vars->elseFin = false;
	vars->autoLex = true;
	return;
}
