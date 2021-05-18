struct symbol {
	char* key;
	char* val;
	struct symbol* next;
};

struct symbol* s_install(struct symbol* head, char* key, char* val) {
	struct symbol* new = (struct symbol*) malloc(sizeof(struct symbol));

	new->key = key;
	new->val = val;
	new->next = head;

	return new;
}

char* s_lookup(struct symbol* head, char* key) {
	while (head != NULL) {
		if (!strcmp(key, head->key)) {
			return head->val;
		} else {
		head = head->next;
		}
	}
	return NULL;
}

char* lookup(struct entry table[], char* mnemonic) {
	int i;

	for (i=0; table[i].key != NULL; i++) {
		// printf("%s\n", table[i].key);
		if (!strcmp(mnemonic, table[i].key)) { 
			return table[i].val;
		}
	}
}
