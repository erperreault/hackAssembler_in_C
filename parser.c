#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.c"

char getCommandType(char* line) {
    // return command type of current line
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

const char* getDest(char* line) {
    // return Dest mnemonic from command
	const char* dest = strtok(line, "=");
	return dest;
}

const char* getComp(char* line) {
    // return Comp mnemonic from command

}

const char* getJump(char* line) {
    // return Jump mnemonic from command
}

//
// lookup from data.c
//

const char* dest(const char* mnemonic) {
    // Get binary of dest mnemonic.
	return dest_lookup(mnemonic);
}

const char* comp(const char* mnemonic) {
    // Get binary of comp mnemonic.
	return comp_lookup(mnemonic);
}

const char* jump(const char* mnemonic) {
    // Get binary of jump mnemonic.
	return jump_lookup(mnemonic);
}

void encode_C(char* line, char* binline) {
    // Check type and lookup using getDest() getComp() or getJump()

	const char* C_mnemonic = getComp(line); 	// there will always be a C command
	const char* D_mnemonic = getDest(line);
	const char* J_mnemonic = getJump(line);

	if (strstr(line, ";")) {
		const char* J_mnemonic = getJump(line);	// J commands require a ;
	} else {
		const char* J_mnemonic = "null";
	}

	if (strstr(line, "=")) { 		// D commands require a =
		D_mnemonic = getDest(line);
	} else {
		D_mnemonic = "null";
	}

	// With mnemonic, reference lookup_x in data.c for binary
	const char* D_bin = dest(D_mnemonic);
	const char* C_bin = comp(C_mnemonic);
	const char* J_bin = jump(J_mnemonic);

	// TODO can this be replaced by sprintf()?
	// Reference the three binary commands to form binline
	strcpy(binline, "111"); // C commands always start with three 1s	
	strcpy(binline+3, C_bin); // C_bin will be 7 bytes; includes the A-bit
	strcpy(binline+10, D_bin); // D_bin will be 3 bytes
	strcpy(binline+13, J_bin); // J_bin will be 3 bytes
}

