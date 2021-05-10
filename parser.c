#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.c"

char getCommandType(char* line) {
    // return command type of current line
    int c = line[0];

    if (c == '/' || c == 0) {
        return '?';
    } else if (c == '@') {
        return 'A';
    } else if (c == '(') {
        return 'L';
    } else {
        return 'C';
    }
}

int getSymbol(char* line, char* symbol) {
    // For A or L commands, return binary for associated symbol
    int type = getCommandType(line);

    if (type == 'A') {
        // A-command
    } else {
        // return contents between ( and )
    }
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
    // encode A
    int val, i, step;

    val = atoi(++line); // skip the @

    tobinary(val, binline);  
}

//
// lookup from data.c
//

void encode_C(char* line, char* binline) {
	const char* C_mnemonic = "null";
	const char* D_mnemonic = "null";
	const char* J_mnemonic = "null";
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
	const char* D_bin = "000";
	const char* C_bin = "0000000";
	const char* J_bin = "000";
	D_bin = get_binary(D_mnemonic, 'D');
	C_bin = get_binary(C_mnemonic, 'C');
	J_bin = get_binary(J_mnemonic, 'J');

	// Build binary string
	sprintf(binline, "111%s%s%s", C_bin, D_bin, J_bin);
}
