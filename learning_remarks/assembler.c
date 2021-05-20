/* Upon finishing the first half of nand2tetris (and implementing the
 * assembler for Project 6 in Python), I wanted to learn C to a basic level.
 * After a little thought, I decided re-implementing the assembler in C would
 * make for a decent milestone of basic competence and also give me something
 * to focus on while integrating the new concepts. 
 *
 * For all its reputation as a simple language, my experience learning basic C
 * reminded me of my experience with Arch Linux. Technically, Arch is a very
 * simple distribution, with a manual installer and no desktop environment 
 * by default, yet it's famously difficult for novices to get running.
 * I think this is because "simplicity" in computer terms doesn't necessarily
 * translate to "easy to use". In fact it often requires more expertise.
 * The less the system does for you, the more you need to know and understand
 * in order to direct it appropriately. A manual transmission in a car might be
 * "simple", but it demands more of the user. Of course there are tradeoffs
 * in the form of reduced control if you abstract out those demands, as well
 * as the possibility for more frequent and difficult problems to arise.
 *
 * Thankfully, my experience with nand2tetris was very helpful in learning C,
 * and some concepts which have a reputation for being challenging weren't so
 * hard for me to pick up (pointers, for example, and memory allocation). 
 *
 * I had two major struggles during this project. The first is the basic task
 * of working with strings in C. Since they are implemented as arrays of chars,
 * the modality is worlds apart from Python with its smorgasbord of convenient
 * string manipulation methods. Even after adjusting my mental model to
 * arrays, I ran into several confusing bugs related to terminating characters.
 * The second major challenge was the overall mindset required. Coming from
 * higher level languages, my instinct was to research built-in functionality
 * for each use-case. Several times I found functions that were close to what
 * I needed, and tried to bend my design around those functions. This mostly
 * wasted time, and eventually I found working in C much easier when I started
 * to default to "rolling my own" (ex. tobinary and lookup functions). Rather
 * than looking for easy string split methods or using strtok, I instead
 * learned what strtok does and then wrote my own barebones version that
 * addressed my particular needs.
 *
 * Overall learning C and completing this project have been my most fruitful
 * work yet in becoming a better coder.
 */

/* This project could have fit in one file, but splitting it up makes more
 * organizational sense and helped me learn how best to modularize / DRY 
 * my code in C.
 */
#include "headers.h"
#include "data.c"
#include "table.c"
#include "parser.c"

/* Naturally, this was actually completed last. I had already grown comfortable
 * working with strings while building second_pass(), so most of what I learned
 * here was related to structs / data structures in C. Linked lists were
 * already familiar to me in other languages, so it was mostly a question of
 * syntax and also honing my fluency using pointers.
 */
int first_pass() {
	char* line = (char*) malloc(100*sizeof(char));
    int line_number = 0; 

    while (fgets(line, 1000, stdin) != NULL) {
		line = cleanupLine(line);
		char type = getCommandType(line);
		if (type == 'L') {
			char* symbol = (char*) malloc(100*sizeof(char));
			char* val = (char*) malloc(100*sizeof(char));
			stripParens(line, symbol);
			sprintf(val, "%d", line_number);
			symbol_table = s_install(symbol_table, symbol, val);
		} else if (type == '?') {
			;
		} else {
            line_number++;
        }
    }
} 

/* This was a good lesson in planning. When I wrote the assembler in Python,
 * I was able to treat everything as a class and write an easy skeleton up
 * front. With more experience I could probably do the same in C, but for this
 * project I had to spend a lot more time clarifying up front how I would
 * structure my code.
 */
int second_pass() {
	char* line = (char*) malloc(100*sizeof(char));
    char type;

    while (fgets(line, 1000, stdin) != NULL) {
		line = cleanupLine(line);
        char binline[] = "0000000000000000"; 

        type = getCommandType(line);

		if (type == '?' || type == 'L') {
			;
		} else if (type == 'A') {
            encode_A(line, binline);
            printf("%s\n", binline);
		} else {
            encode_C(line, binline);
			printf("%s\n", binline);
        }
    }
}  

/* rewind(stdin) is a neat trick :)
 */
int main() {
    first_pass();
	rewind(stdin);
	second_pass();
}
