#include <string.h>
#include <assert.h>

/* is this better than using a simple struct and lookup function? */
const char* dest_lookup(const char* mnemonic) {
    if (!strcmp("null", mnemonic)) {
        return "000";
    } else if (!strcmp("M", mnemonic)) {
        return "001";
    } else if (!strcmp("D", mnemonic)) {
        return "010";
    } else if (!strcmp("MD", mnemonic)) {
        return "011";
    } else if (!strcmp("A", mnemonic)) {
        return "100";
    } else if (!strcmp("AM", mnemonic)) {
        return "101";
    } else if (!strcmp("AD", mnemonic)) {
        return "110";
    } else if (!strcmp("AMD", mnemonic)) {
        return "111";
    } else {
        return mnemonic; 
    }
}

const char* jump_lookup(const char* mnemonic) {
    if (!strcmp("null", mnemonic)) {
        return "000";
    } else if (!strcmp("JGT", mnemonic)) {
        return "001";
    } else if (!strcmp("JEQ", mnemonic)) {
        return "010";
    } else if (!strcmp("JGE", mnemonic)) {
        return "011";
    } else if (!strcmp("JLT", mnemonic)) {
        return "100";
    } else if (!strcmp("JNE", mnemonic)) {
        return "101";
    } else if (!strcmp("JLE", mnemonic)) {
        return "110";
    } else if (!strcmp("JMP", mnemonic)) {
        return "111";
    } else {
        return mnemonic;
    }
}

const char* comp_lookup(const char* mnemonic) {
	printf("mn = %s\n", mnemonic);
    if (!strcmp("0", mnemonic)) {
        return "0101010";
    } else if (!strcmp("1", mnemonic)) {
        return "0111111";
    } else if (!strcmp("-1", mnemonic)) {
        return "0111010";
    } else if (!strcmp("D", mnemonic)) {
        return "0001100";
    } else if (!strcmp("A", mnemonic)) {
        return "0110000";
    } else if (!strcmp("!D", mnemonic)) {
        return "0001101";
    } else if (!strcmp("!A", mnemonic)) {
        return "0110001";
    } else if (!strcmp("-D", mnemonic)) {
        return "0001111";
    } else if (!strcmp("-A", mnemonic)) {
        return "0110011";
    } else if (!strcmp("D+1", mnemonic)) {
        return "0011111";
    } else if (!strcmp("A+1", mnemonic)) {
        return "0110111";
    } else if (!strcmp("D-1", mnemonic)) {
        return "0001110";
    } else if (!strcmp("A-1", mnemonic)) {
        return "0110010";
    } else if (!strcmp("D+A", mnemonic)) {
        return "0000010";
    } else if (!strcmp("D-A", mnemonic)) {
        return "0010011";
    } else if (!strcmp("A-D", mnemonic)) {
        return "0000111";
    } else if (!strcmp("D&A", mnemonic)) {
        return "0000000";
    } else if (!strcmp("D|A", mnemonic)) {
        return "0010101";
    } else if (!strcmp("M", mnemonic)) {
        return "1110000";
    } else if (!strcmp("!M", mnemonic)) {
        return "1110001";
    } else if (!strcmp("-M", mnemonic)) {
        return "1110011";
    } else if (!strcmp("M+1", mnemonic)) {
        return "1110111";
    } else if (!strcmp("M-1", mnemonic)) {
        return "1110010";
    } else if (!strcmp("D+M", mnemonic)) {
        return "1000010";
    } else if (!strcmp("D-M", mnemonic)) {
        return "1010011";
    } else if (!strcmp("M-D", mnemonic)) {
        return "1000111";
    } else if (!strcmp("D&M", mnemonic)) {
        return "1000000";
    } else if (!strcmp("D|M", mnemonic)) {
        return "1010101";
    } else {
        return mnemonic;
    }
}

void data_unit_tests() {
    assert(strcmp(dest_lookup("D"), "010") == 0);
    assert(strcmp(dest_lookup("AMD"), "111") == 0);
    assert(strcmp(dest_lookup("null"), "000") == 0);

    assert(strcmp(jump_lookup("JGT"), "001") == 0);
    assert(strcmp(jump_lookup("JMP"), "111") == 0);
    assert(strcmp(jump_lookup("null"), "000") == 0);

    assert(strcmp(comp_lookup("0"), "0101010") == 0);
    assert(strcmp(comp_lookup("D"), "0001100") == 0);
    assert(strcmp(comp_lookup("!D"), "0001101") == 0);
    assert(strcmp(comp_lookup("A-1"), "0110010") == 0);
    assert(strcmp(comp_lookup("D&A"), "0000000") == 0);
    assert(strcmp(comp_lookup("-M"), "1110011") == 0);
    assert(strcmp(comp_lookup("M-D"), "1000111") == 0);
}
