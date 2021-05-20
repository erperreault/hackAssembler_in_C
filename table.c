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
	
	if (lookup(table, key)) {
		return lookup(table, key);
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
