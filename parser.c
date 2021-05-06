#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.c"

char getCommandType(char* line) {
    // return command type of current line
    int c = line[0];

    if (c == '/' || line[1] == 0) {
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

	printf("line = %s\n", line);

	if (x = strchr(line, '=')) {
		*x = 0;
		D_mnemonic = line;
		printf("Dmn = %s\n", D_mnemonic);
		line = x+1;
	}

	if (x = strchr(line, ';')) {
		*x = 0;
		C_mnemonic = line;
		printf("Cmn = %s\n", C_mnemonic);
		J_mnemonic = x+1;
		printf("Jmn = %s\n", J_mnemonic);
	} else {
		C_mnemonic = line;
		printf("Cmn = %s\n", C_mnemonic);
	}
		
	// With mnemonic, reference lookup_x in data.c for binary
	const char* D_bin = "000";
	const char* C_bin = "0000000";
	const char* J_bin = "000";
	D_bin = dest_lookup(D_mnemonic);
	printf("Db = %s\n", D_bin);
	C_bin = comp_lookup(C_mnemonic);
	printf("Cb = %s\n", C_bin);
	J_bin = jump_lookup(J_mnemonic);
	printf("Jb = %s\n", J_bin);

	// TODO can this be replaced by sprintf()?
	// Reference the three binary commands to form binline
	strcpy(binline, "111"); // C commands always start with three 1s	
	strcpy(binline+3, C_bin); // C_bin will be 7 bytes; includes the A-bit
	strcpy(binline+10, D_bin); // D_bin will be 3 bytes
	strcpy(binline+13, J_bin); // J_bin will be 3 bytes
}

