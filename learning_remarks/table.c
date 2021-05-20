/* I spent a lot of time implementing a full-on hash table for this,
 * before realizing after a conversation with a friend that I didn't 
 * need the functionality it offers compared to a singly-linked list.
 * I have worked with linked lists in various coding challenges (leetcode,
 * codewars, etc) so this was actually easy for me to implement.
 *
 * Since the table is just generated once and then referenced, there's
 * no need to remove entries, and the lookup time for simply walking
 * over the list is fine considering the scope of the project. One "next
 * step" improvement for this assembler could be a sorted / doubly-linked
 * list with a more sophisticated lookup algorithm.
 *
 * Overall this was a great reminder to connect with others and seek feedback,
 * especially when learning new material. None of the technical concepts here
 * were new to me, but "choosing the right tool" is a hard skill to learn
 * and a great area to grow from others's insight.
 */
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

/* I went back and forth on whether to combine the hardcoded and
 * dynamically added labels into one table, and eventually decided to 
 * keep all the hard-coded data together and the dynamic stuff separate.
 * This means two steps for the s_lookup function, but makes more
 * organizational sense to me. It also makes data.c more readable.
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
