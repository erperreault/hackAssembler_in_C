/* Assembler for the Hack assembly language, implemented in C. */

#include "parser.c"

struct symbol* symbol_table;

// Scan through and create symbol table. 
int first_pass() {
	char* line = (char*) malloc(100*sizeof(char));
    int line_number = 0;

    while (fgets(line, 1000, stdin) != NULL) {
		line = cleanupLine(line);
		// printf("%s\n", line);
		if (getCommandType(line) == 'L') {
			char* symbol = (char*) malloc(100*sizeof(char));
			char* val = (char*) malloc(100*sizeof(char));

			getSymbol(line, symbol);
			sprintf(val, "%d", line_number);

			symbol_table = s_install(symbol_table, symbol, val);
		} else if (getCommandType(line) == '?') {
			;
		} else {
            line_number++;
        }
    }
	/*	
	struct symbol* x = symbol_table;
	while (x != NULL) {
		printf("%s %s\n", x->key, x->val);
		x = x->next;
	}
	*/
} 

// Perform actual translation, referencing symbol table.
int second_pass() {
	char* line = (char*) malloc(100*sizeof(char));
    char type;

	extern struct symbol* symbol_table;
	// printf("%s\n", s_lookup(symbol_table, "(OUTPUT_FIRST)"));

    while (fgets(line, 1000, stdin) != NULL) {
		line = cleanupLine(line);
        char binline[] = "0000000000000000"; 

        type = getCommandType(line);
		// printf("%c\n", type);
		// printf("%s\n", line);

		if (type == '?') {
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

// Also segfaults when writing labels to binary, fix encode_L

int main() {
    first_pass(); 		// this will be the symbol table
	rewind(stdin);
	second_pass(); 		// actual binary translation
}
