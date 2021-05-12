/* Assembler for the Hack assembly language, implemented in C. */

#include "parser.c"

struct symbol* symbol_table;

// Scan through and create symbol table. 
int first_pass() {
    char line[100];
    int line_number = 0;

    while (fgets(line, 1000, stdin) != NULL) {
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
	printf("%s\n", s_lookup(symbol_table, "(OUTPUT_D)"));
	*/
} 

// Perform actual translation, referencing symbol table.
int second_pass() {
    char line[100];
    char type;

    while (fgets(line, 1000, stdin) != NULL) {
        char* binline = (char*) malloc(16*sizeof(char));
		char* x = strrchr(line, '\n') - 1;
		*x = 0;

        type = getCommandType(line);

		if (type == '?') {
			;
		} else if (type == 'L') {
            encode_L(line, binline);
            printf("%s\n", binline);
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
    first_pass(); 		// this will be the symbol table
	rewind(stdin);
    // second_pass(); 		// actual binary translation
}
