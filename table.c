const char* bin_lookup(const char* abc[], const char* bin[], const char* mnemonic) {
	int i;

	for (i = 0; abc[i] != NULL; i++) {
		if (!strcmp(mnemonic, abc[i])) {
			return bin[i];			
		}
	}
}

const char* get_binary(const char* mnemonic, char type) {
	if (type == 'D') {
		return bin_lookup(dest_mnemonics, dest_binaries, mnemonic);
	} else if (type == 'C') {
		return bin_lookup(comp_mnemonics, comp_binaries, mnemonic);	
	} else if (type == 'J') {
		return bin_lookup(jump_mnemonics, jump_binaries, mnemonic);	
	}
}
