const char* lookup(struct entry table[], const char* mnemonic) {
	int i;

	for (i=0; table[i].key != NULL; i++) {
		if (!strcmp(mnemonic, table[i].key)) { 
			return table[i].val;
		}
	}
}

void install(struct entry table[], struct entry new, int length) {
	table[length] = new;
	printf("%d\n", length);
	length++;
}
