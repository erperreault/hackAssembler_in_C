/* fill target string from the right with binary of given int
 * so: tobinary(3, "00000") -> "00011"  
 */
void tobinary(int val, char* line) {
    int i;
    int len = strlen(line);

    for (i = 1; i <= len; i++) {  /* i = 1 so we have last index */
        line[len-i] = '0' + (val % 2); /* either 0 or 1 */
        val = val / 2;    
    }
}

/* line: (JUMPLABEL) -> symbol: JUMPLABEL
 */
void stripParens(char* line, char* symbol) {
	line++;
	if (strrchr(line, ')')) {
		*strrchr(line, ')') = 0;
	}
	strcpy(symbol, line);
}

/* Remove leading/trailing whitespace and comments from string.
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

/* Return command type of current line (A/L/C/?)
 */
char getCommandType(char* line) {
    char c = *line;

	/* non-alphanumeric characters or leading slashes
	 * which survive cleanupLine() will be treated as ? and skipped
	 */
    if (c == '/' || c == '\0' || c == ' ' 
		|| c == '\n' || c == '\t' || c == '\r') {
        return '?';
    } else if (c == '@') {
        return 'A';
    } else if (c == '(') {
        return 'L';
    } else {
		/* there is a gap here for characters not in the lookup tables,
		 * but they will cause a noisy crash which is appropriate.
		 */
        return 'C';
    }
}

/* Initial register for variable assignment, which is incremented
 * as we encounter new variables.
 */
int var_reg = 16;

/* A-commands are formatted as @xxxxxxxxx...
 * encode_A strips the @, looks up or assigns label/variable values 
 * if needed, and returns a final binary command.
 */
void encode_A(char* line, char* binline) {
    int val; /* the eventual memory address */
	char* reg = (char*) malloc(100*sizeof(char)); /* string to hold it */

	line++; // skip the @

	/* ex. @12845 converted directly */
	if (isdigit(*line)) {
		val = atoi(line);
	/* ex. @LABEL after (LABEL) found in first_pass() */
	} else if (s_lookup(symbol_table, line) != NULL) {
		val = atoi(s_lookup(symbol_table, line));
	/* ex. @variable after (variable) NOT found in first_pass() */
	} else if (s_lookup(symbol_table, line) == NULL) {
		/* to be added to symbol_table */
		char* key = (char*) malloc(100*sizeof(char)); 

		val = var_reg; /* grab next open register */
		strcpy(key, line);
		sprintf(reg, "%d", var_reg);
		symbol_table = s_install(symbol_table, key, reg);
		var_reg++;
	}

    tobinary(val, binline);  
}
/* C-commands are formatted as A=M;JMP --> dest = comp ; jump
 * the binary command is formatted as 111CCCCCCCDDDJJJ
 * dest and jump are optional, so we look for '=' and ';' to see if they exist
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

	/* Reference lookup_x in data.c for each mnemonic */
	char* D_bin = lookup(dest_table, D_mnemonic);
	char* C_bin = lookup(comp_table, C_mnemonic);
	char* J_bin = lookup(jump_table, J_mnemonic);

	sprintf(binline, "111%s%s%s", C_bin, D_bin, J_bin);
}
