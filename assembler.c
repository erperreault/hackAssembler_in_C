/* Assembler for the Hack assembly language, implemented in C. */

#include "parser.c"

// Scan through and create symbol table. 
int first_pass() {
    char line[1000];
    char symbol[1000];
    int line_number = 0;

    while (fgets(line, 1000, stdin) != NULL) {
		if (getCommandType(line) == 'L') {
			getSymbol(line, symbol);
            // add label to symbol table, mapped to line_number
        } else {
            line_number++;
        }
    }
} 

// Perform actual translation, referencing symbol table.
int second_pass() {
    char line[1000];
    char type;
    
    while (fgets(line, 1000, stdin) != NULL) {
        char binline[] = "0000000000000000";
		char* x = strrchr(line, '\n') - 1;
		*x = 0;

        type = getCommandType(line);

		if (type == '?') {
			;
		} else if (type == 'A') {
            encode_A(line, binline);
            printf("%s\n", binline);
		} else {
            encode_C(line, binline);
			printf("%s\n", binline);
        }
        // write line to output file
    }
}  

int main() {
    // first_pass(); 	// this will be the symbol table
    second_pass(); 		// actual binary translation
}
