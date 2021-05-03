/* Assembler for the Hack assembly language, implemented in C. */


#include "data.c"
#include "parser.c"

// Scan through and create symbol table. 
// TESTING
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
        type = getCommandType(line);

        if (type == 'A') {
            encode_A(line, binline);
            printf("%s\n", binline);
        } else {
            // line = encode_C
			// ?
        }
        // write line to output file
    }
}  

int main() {
    // first_pass();
    second_pass();
}
