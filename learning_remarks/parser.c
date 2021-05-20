/* This was surprisingly my "valley of despair" in this project. All my
 * intuitions from higher-level programming were screaming at me, "THERE
 * MUST BE A SIMPLE WAY TO DO THIS". Turns out "simple" can equally well
 * mean rolling your own, and some simple math took care of this function.
 */
void tobinary(int val, char* line) {
    int i;
    int len = strlen(line);

    for (i = 1; i <= len; i++) {  
        line[len-i] = '0' + (val % 2);
        val = val / 2;    
    }
}

/* Once again, I wanted one unified function to clean up all my lines,
 * but stripping the parentheses off a (LABEL) was a single-use case so
 * it made more sense to just give it its own home rather than pass it as
 * an argument or setting.
 */
void stripParens(char* line, char* symbol) {
	line++;
	if (strrchr(line, ')')) {
		*strrchr(line, ')') = 0;
	}
	strcpy(symbol, line);
}

/* Yet another lesson learned here is to NEVER trust your input. Whereas I
 * thought the input program files were all formatted similarly, it turns out
 * some use indentations, comments in different ways, etc. This reminded me to
 * code defensively and go out of my way to sanitize and double-check inputs.
 */
char* cleanupLine(char* line) {
	char* x = strstr(line, "//");
	if (x != NULL) {
		*x = 0;
	}

	while (isspace(*line)) {
		line++;
	}
	
	x = line;
	while (!isspace(*x)) {
		x++;
	} 
	*x = 0;

	return line;
}

char getCommandType(char* line) {
    char c = *line;

    if (c == '/' || c == '\0' || c == ' ' 
		|| c == '\n' || c == '\t' || c == '\r') {
        return '?';
    } else if (c == '@') {
        return 'A';
    } else if (c == '(') {
        return 'L';
    } else {
        return 'C';
    }
}

int var_reg = 16;

/* The order of operations here was a little tricky since it had to change
 * while writing first_pass() even though I had already written second_pass().
 * Definitely an area I think I would have foreseen with more experience,
 * but a good learning experience.
 */
void encode_A(char* line, char* binline) {
    int val; 
	char* reg = (char*) malloc(100*sizeof(char)); 

	line++;

	if (isdigit(*line)) {
		val = atoi(line);
	} else if (s_lookup(symbol_table, line) != NULL) {
		val = atoi(s_lookup(symbol_table, line));
	} else if (s_lookup(symbol_table, line) == NULL) {
		char* key = (char*) malloc(100*sizeof(char)); 

		val = var_reg; 
		strcpy(key, line);
		sprintf(reg, "%d", var_reg);
		symbol_table = s_install(symbol_table, key, reg);
		var_reg++;
	}

    tobinary(val, binline);  
}

/* sprintf() sure is handy! I was building this output in a much more
 * roundabout way at first. Also, implementing customized procedural logic
 * for a string splitting function is a good demonstration of where doing
 * things manually can be way more clear and concise than stacking multiple
 * pre-built tools.
 */
void encode_C(char* line, char* binline) {
	char* D_mnemonic = "null";
	char* C_mnemonic = "null";
	char* J_mnemonic = "null";
	char* c;

	if (c = strchr(line, '=')) {
		*c = 0;
		D_mnemonic = line;
		line = c+1;
	}

	if (c = strchr(line, ';')) {
		*c = 0;
		C_mnemonic = line;
		J_mnemonic = c+1;
	} else {
		C_mnemonic = line;
	}

	char* D_bin = lookup(dest_table, D_mnemonic);
	char* C_bin = lookup(comp_table, C_mnemonic);
	char* J_bin = lookup(jump_table, J_mnemonic);

	sprintf(binline, "111%s%s%s", C_bin, D_bin, J_bin);
}
