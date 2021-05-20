/* Assembler for the Hack assembly language, implemented in C. */

#include "headers.h"
#include "data.c"
#include "table.c"
#include "parser.c"

/* Create symbol table. We simply look for labels ex. (LABEL)
 * and add an entry for each associating it to the current line number.
 */
int first_pass() {
	char* line = (char*) malloc(100*sizeof(char));
    int line_number = 0; /* we need to track this for (LABEL) values */

    while (fgets(line, 1000, stdin) != NULL) {
		line = cleanupLine(line);
		char type = getCommandType(line);
		if (type == 'L') {
			char* symbol = (char*) malloc(100*sizeof(char));
			char* val = (char*) malloc(100*sizeof(char));
			stripParens(line, symbol);
			sprintf(val, "%d", line_number);
			symbol_table = s_install(symbol_table, symbol, val);
		} else if (type == '?') {
			;
		} else {
            line_number++;
        }
    }
} 

/* Perform actual translation, referencing symbol table.
 */
int second_pass() {
	char* line = (char*) malloc(100*sizeof(char));
    char type;

    while (fgets(line, 1000, stdin) != NULL) {
		line = cleanupLine(line);
        char binline[] = "0000000000000000"; 

        type = getCommandType(line);

		if (type == '?' || type == 'L') {
			;
		} else if (type == 'A') {
            encode_A(line, binline);
            printf("%s\n", binline);
		} else {
            encode_C(line, binline);
			printf("%s\n", binline);
        }
    }
}  

int main() {
    first_pass();
	rewind(stdin);
	second_pass();
}
