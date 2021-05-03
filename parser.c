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

int encode_C(char* mnemonic) {
    // Check type and lookup using dest() comp() or jump()
}

/* dig out particular parts of C commands */

int getDest() {
    // for C commands, return Dest mnemonic
}

int getComp() {
    // for C commands, return Comp mnemonic
}

int getJump() {
    // for C commands, return Jump mnemonic
}

/* lookup from data.c */

int dest(char* mnemonic) {
    // Return binary of dest mnemonic.
}

int comp(char* mnemonic) {
    // Return binary of comp mnemonic.
}

int jump(char* mnemonic) {
    // Return binary of jump mnemonic.
}