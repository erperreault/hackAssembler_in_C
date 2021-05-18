#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "data.c"
#include "table.c"

char* cleanupLine(char* line) {
	while (isspace(*line)) {
		line++;
	};

	char* x = strstr(line, "//");
	if (x != NULL) {
		*x = 0;
	}

	char* y = strrchr(line, '\r');
	if (y != NULL) {
		*y = 0;
	}

	return line;
}

char getCommandType(char* line) {
    // return command type of current line
    char c = *line;

    if (c == '/' || c == '\t' || c == ' ' || c == '\n' || c == '\0' || c == '\r') {
        return '?';
    } else if (c == '@') {
        return 'A';
    } else if (c == '(') {
        return 'L';
    } else {
        return 'C';
    }
}

void getSymbol(char* line, char* symbol) {
	line++;
	if (strrchr(line, ')')) {
		*strrchr(line, ')') = 0;
	}
	strcpy(symbol, line);
}

/*  fill target string from the right with binary of given int
    so tobinary(3, "00000") -> "00011"  */
void tobinary(int val, char* line) {
    int i;
    int len = strlen(line);

    for (i = 1; i <= len; i++) {  // i = 1 so we have last index
        line[len-i] = '0' + (val % 2); // either 0 or 1
        val = val / 2;    
    }
}

void encode_A(char* line, char* binline) {
	extern struct symbol* symbol_table;
    int val;

	line++; // skip the @

	if (s_lookup(symbol_table, line) != NULL) {
		line = s_lookup(symbol_table, line);
	}

    val = atoi(line);

    tobinary(val, binline);  
}

void encode_C(char* line, char* binline) {
	char* C_mnemonic = "null";
	char* D_mnemonic = "null";
	char* J_mnemonic = "null";
	char* x;

	if (x = strchr(line, '=')) {
		*x = 0;
		D_mnemonic = line;
		line = x+1;
	}

	if (x = strchr(line, ';')) {
		*x = 0;
		C_mnemonic = line;
		J_mnemonic = x+1;
	} else {
		C_mnemonic = line;
	}

	// With mnemonic, reference lookup_x in data.c for binary
	char* C_bin = lookup(comp_table, C_mnemonic);
	char* D_bin = lookup(dest_table, D_mnemonic);
	char* J_bin = lookup(jump_table, J_mnemonic);

	// Build binary string
	sprintf(binline, "111%s%s%s", C_bin, D_bin, J_bin);
}
