/* Assembler for the Hack assembly language, implemented in C. */

#include "parser.c"

// Scan through and create symbol table. 
int first_pass() {
    char line[1000];
    char symbol[1000];
	char address[] = "0000000000000000";
    int line_number = 0;
	int length = 23;


    while (fgets(line, 1000, stdin) != NULL) {
		if (getCommandType(line) == 'L') {
			getSymbol(line, symbol);
			struct entry new = {.key = "0000000000", .val = "0000000000"};
			strcpy(new.key, symbol);
			char temp[100];
			sprintf(temp, "%d", line_number);
			strcpy(new.val, temp);
			install(table, new, length);
        } else {
            line_number++;
        }
    }

	int i;
	for (i = 0; i < length; i++) {
		printf("%s : %s\n", table[i].key, table[i].val);
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
    // second_pass(); 		// actual binary translation
}
