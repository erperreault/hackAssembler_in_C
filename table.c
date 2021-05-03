#include <stdio.h>

#define HASHSIZE 1000

static struct entry *hashtab[HASHSIZE];

struct entry {
    struct entry *next;
    char *key;
    char *value;
};

/* hash: form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct entry *lookup(char *s) {
    struct entry *e;

    for (e = hashtab[hash(s)]; e != NULL; e = e->next) {
        if (strcmp(s, e->key) == 0) {
            return e;
        }
    }
    return NULL;
}

struct entry *lookup(char *);
char *strdup(char *);

/* install: put (key, value) in hashtab */
struct entry *install(char *key, char *value) {
    struct entry *e;
    unsigned hashval;

    if ((e = lookup(key)) == NULL) {
        e = (struct entry *) malloc(sizeof(*e));

        if (e == NULL || (e->key = strdup(key)) == NULL) {
            return NULL;
        }

        hashval = hash(key);
        e->next = hashtab[hashval];
        hashtab[hashval] = e;
    } else {
        free((void *) e->value);
    }

    if ((e->value = strdup(value)) == NULL) {
        return NULL;
    } 

    return e;
}

/* make a duplicate of s */
char *strdup(char *s) {
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}