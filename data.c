#include <string.h>
#include <assert.h>

const char* dest_mnemonics[] = {
	"null",
	"M",
	"D",
	"MD",
	"A",
	"AM",
	"AD",
	"AMD"
};

const char* dest_binaries[] = {
	"000",
	"001",
	"010",
	"011",
	"100",
	"101",
	"110",
	"111"
};

const char* jump_mnemonics[] = {
	"null",
	"JGT",
	"JEQ",
	"JGE",
	"JLT",
	"JNE",
	"JLE",
	"JMP"
};

const char* jump_binaries[] = {
	"000",
	"001",
	"010",
	"011",
	"100",
	"101",
	"110",
	"111"
};

const char* comp_mnemonics[] = {
	"0",
	"1",
	"-1",
	"D",
	"A",
	"!D",
	"!A",
	"-D",
	"-A",
	"D+1",
	"A+1",
	"D-1",
	"A-1",
	"D+A",
	"D-A",
	"A-D",
	"D&A",
	"D|A",
	"M",
	"!M",
	"-M",
	"M+1",
	"M-1",
	"D+M",
	"D-M",
	"M-D",
	"D&M",
	"D|M"
};


const char* comp_binaries[] = {
	"0101010",
	"0111111",
	"0111010",
	"0001100",
	"0110000",
	"0001101",
	"0110001",
	"0001111",
	"0110011",
	"0011111",
	"0110111",
	"0001110",
	"0110010",
	"0000010",
	"0010011",
	"0000111",
	"0000000",
	"0010101",
	"1110000",
	"1110001",
	"1110011",
	"1110111",
	"1110010",
	"1000010",
	"1010011",
	"1000111",
	"1000000",
	"1010101"
};

const char* lookup(const char* abc[], const char* bin[], const char* mnemonic) {
	int i;

	for (i = 0; abc[i] != NULL; i++) {
		if (!strcmp(mnemonic, abc[i])) {
			return bin[i];			
		}
	}
}

const char* dest_lookup(const char* mnemonic) {
	return lookup(dest_mnemonics, dest_binaries, mnemonic);	
}

const char* jump_lookup(const char* mnemonic) {
	return lookup(jump_mnemonics, jump_binaries, mnemonic);	
}

const char* comp_lookup(const char* mnemonic) {
	return lookup(comp_mnemonics, comp_binaries, mnemonic);	
}
