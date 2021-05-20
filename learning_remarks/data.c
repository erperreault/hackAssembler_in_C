/* Initially I threw together a set a functions which essentially did:
 * 		switch key: case (!strcmp("KEY", key)) -> return "VAL"
 * This was fine for phase 1 of the project (building second_pass),
 * and let me postpone digging into structs until after I got something
 * working. 
 *
 * Coming from Python, it was a big perspective shift to forget about 
 * dicts as a built-in data structure and accept that in C it very often 
 * makes sense to roll your own. 
 *
 * Once I got around to actually implementing the lookup table, I found
 * it fairly intuitive. Pointers were one of the easier concepts for me
 * to pick up (I suppose thanks to the rest of nand2tetris which I had
 * already completed) so it was really just a question of learning the
 * struct syntax. One hangup was ironing out the difference between:
 * 		.key	vs	->key
 * Which basically requires distinguishing between a pointer to the 
 * struct and the struct itself.
 */
struct entry {
	char* key;
	char* val;
};

/* There were a few things to learn related to what you get when you
 * look for structs and members that aren't there, but otherwise 
 * this was straightforward.
 */
char* lookup(struct entry table[], char* mnemonic) {
	int i;

	for (i=0; table[i].key != NULL; i++) {
		if (!strcmp(mnemonic, table[i].key)) { 
			return table[i].val;
		}
	}
}

struct entry table[] = {
	{"SP", "0"},
	{"LCL", "1"},
	{"ARG", "2"},
	{"THIS", "3"},
	{"THAT", "4"},
	{"R0", "0"},
	{"R1", "1"},
	{"R2", "2"},
	{"R3", "3"},
	{"R4", "4"},
	{"R5", "5"},
	{"R6", "6"},
	{"R7", "7"},
	{"R8", "8"},
	{"R9", "9"},
	{"R10", "10"},
	{"R11", "11"},
	{"R12", "12"},
	{"R13", "13"},
	{"R14", "14"},
	{"R15", "15"},
	{"SCREEN", "16384"},
	{"KBD", "24576"}
};

struct entry dest_table[] = {
	{"null", "000"},
	{"M", "001"},
	{"D", "010"},
	{"MD", "011"},
	{"A", "100"},
	{"AM", "101"},
	{"AD", "110"},
	{"AMD", "111"}
};

struct entry jump_table[] = {
	{"null", "000"},
	{"JGT", "001"},
	{"JEQ", "010"},
	{"JGE", "011"},
	{"JLT", "100"},
	{"JNE", "101"},
	{"JLE", "110"},
	{"JMP", "111"}
};

struct entry comp_table[] = {
	{"0", "0101010"},
	{"1", "0111111"},
	{"-1", "0111010"},
	{"D", "0001100"},
	{"A", "0110000"},
	{"!D", "0001101"},
	{"!A", "0110001"},
	{"-D", "0001111"},
	{"-A", "0110011"},
	{"D+1", "0011111"},
	{"A+1", "0110111"},
	{"D-1", "0001110"},
	{"A-1", "0110010"},
	{"D+A", "0000010"},
	{"D-A", "0010011"},
	{"A-D", "0000111"},
	{"D&A", "0000000"},
	{"D|A", "0010101"},
	{"M", "1110000"},
	{"!M", "1110001"},
	{"-M", "1110011"},
	{"M+1", "1110111"},
	{"M-1", "1110010"},
	{"D+M", "1000010"},
	{"D-M", "1010011"},
	{"M-D", "1000111"},
	{"D&M", "1000000"},
	{"D|M", "1010101"}
};
