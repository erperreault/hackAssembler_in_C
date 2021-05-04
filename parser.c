#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char getCommandType(char* line) {
    // return command type of current line
    // TODO remove leading blanks
    int c = line[0];

    if (c == '/' || line[1] == '\n') {
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
    so (3, "00000") -> "00011"  */
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

void encode_C(char* line, char* binline) {
	char D_mnemonic[10], C_mnemonic[10], J_mnemonic[10];
	char D_bin[10], C_bin[10], J_bin[10];

    // Check type and lookup using getDest() getComp() or getJump()

	getComp(line, C_mnemonic); // there will always be a C command

	if (strstr(line, ';')) { 	// J commands require a ;
		getJump(line, J_mnemonic);
	}

	if (strstr(line, '=')) { 	// D commands require a =
		getDest(line, D_mnemonic);
	}

	// With mnemonic, reference lookup_x in data.c for binary
	D_bin = dest(D_mnemonic);
	C_bin = dest(C_mnemonic);
	J_bin = dest(J_mnemonic);

	// Reference the three binary commands to form binline
	strcpy(binline[0], "111"); // C commands always start with three 1s	
	strcpy(binline[3], C_bin); // C_bin will be 7 bytes; includes the A-bit
	strcpy(binline[10], D_bin); // D_bin will be 3 bytes
	strcpy(binline[13], J_bin); // J_bin will be 3 bytes
}

void getDest(char* line, char* mnemonic) {
    // update Dest mnemonic
	
}

void getComp(char* line, char* mnemonic) {
    // update Comp mnemonic
}

void getJump(char* line, char* mnemonic) {
    // update Jump mnemonic
}

/* lookup from data.c */

char* dest(char* mnemonic) {
    // Return binary of dest mnemonic.
}

char* comp(char* mnemonic) {
    // Return binary of comp mnemonic.
}

char* jump(char* mnemonic) {
    // Return binary of jump mnemonic.
}
