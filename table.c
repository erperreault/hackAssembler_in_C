/* struct symbol implements a singly-linked list, expanding on struct entry
 * so that we can add new entries. 
 */
struct symbol {
	char* key;
	char* val;
	struct symbol* next;
};

/* Allocate memory for a new symbol, then point at the previous list head.
 */
struct symbol* s_install(struct symbol* head, char* key, char* val) {
	struct symbol* new = (struct symbol*) malloc(sizeof(struct symbol));

	new->key = key;
	new->val = val;
	new->next = head;

	return new;
}

/* First check the hard-corded symbol table, then our linked list for symbols
 * added during first_pass(). Starting at current list head, walk through 
 * the linked list checking for a match.
 */
char* s_lookup(struct symbol* head, char* key) {
	int i;
	
	for (i=0; table[i].key != NULL; i++) {
		if (!strcmp(key, table[i].key)) {
			return table[i].val;
		}
	}
	
	while (head != NULL) {
		if (!strcmp(key, head->key)) {
			return head->val;
		} else {
		head = head->next;
		}
	}

	return NULL;
}
