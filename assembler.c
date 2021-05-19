/* Assembler for the Hack assembly language, implemented in C. */

#include "headers.h"
#include "data.c"
#include "table.c"

struct symbol* symbol_table;

/*  fill target string from the right with binary of given int
    so tobinary(3, "00000") -> "00011"  */
void tobinary(int val, char* line) {
    int i;
    int len = strlen(line);

    for (i = 1; i <= len; i++) {  // i = 1 so we have last index
        line[len-i] = '0' + (val % 2); // either 0 or 1
        val = val / 2;    
    }
}

void getSymbol(char* line, char* symbol) {
	line++;
	if (strrchr(line, ')')) {
		*strrchr(line, ')') = 0;
	}
	strcpy(symbol, line);
}

char* cleanupLine(char* line) {
	while (isspace(*line)) {
		line++;
	};

	char* x = strstr(line, "//");
	if (x != NULL) {
		*x = 0;
	}

	char* z = line;
	while (!isspace(*z)) {
		z++;
	}
	*z = '\0';

	return line;
}

char getCommandType(char* line) {
    // return command type of current line
    char c = *line;

    if (c == '/' || c == '\t' || c == ' ' || c == '\n' || c == '\0' || c == '\r') {
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

void encode_A(char* line, char* binline) {
    int val;
	char* reg = (char*) malloc(100*sizeof(char));
	line++; // skip the @

	if (isdigit(*line)) {
		val = atoi(line);
		// printf("numeric line: __%d__\n", val);
	} else if (s_lookup(symbol_table, line) != NULL) {
		val = atoi(s_lookup(symbol_table, line));
		// printf("looked up line: __%d__\n", val);
	// this is somehow overwriting most previous keys when installing, why?
	// it doesn't overwrite the symbols from first_pass()...
	// and the new keys have dead space / tabs added in front
	// the dead space explains why lookup doesn't match but where is it coming from?
	} else if (s_lookup(symbol_table, line) == NULL) {
		val = var_reg;
		char* key = (char*) malloc(100*sizeof(char));
		strcpy(key, line);
		sprintf(reg, "%d", var_reg);
		symbol_table = s_install(symbol_table, key, reg); // somehow this is fucking up line, it works for all other strings...
		// printf("installed line: key __%s__, val __%d__\n", key, var_reg);
		var_reg++;
	}

    tobinary(val, binline);  
}

void encode_C(char* line, char* binline) {
	char* C_mnemonic = "null";
	char* D_mnemonic = "null";
	char* J_mnemonic = "null";
	char* x;

	if (x = strchr(line, '=')) {
		*x = 0;
		D_mnemonic = line;
		line = x+1;
	}

	if (x = strchr(line, ';')) {
		*x = 0;
		C_mnemonic = line;
		J_mnemonic = x+1;
	} else {
		C_mnemonic = line;
	}

	// With mnemonic, reference lookup_x in data.c for binary
	char* C_bin = lookup(comp_table, C_mnemonic);
	char* D_bin = lookup(dest_table, D_mnemonic);
	char* J_bin = lookup(jump_table, J_mnemonic);

	// Build binary string
	sprintf(binline, "111%s%s%s", C_bin, D_bin, J_bin);
}

// Scan through and create symbol table. 
int first_pass() {
	char* line = (char*) malloc(100*sizeof(char));
    int line_number = 0;

    while (fgets(line, 1000, stdin) != NULL) {
		line = cleanupLine(line);
		// printf("%s\n", line);
		char type = getCommandType(line);
		if (type == 'L') {
			char* symbol = (char*) malloc(100*sizeof(char));
			char* val = (char*) malloc(100*sizeof(char));
			getSymbol(line, symbol);
			sprintf(val, "%d", line_number);
			symbol_table = s_install(symbol_table, symbol, val);
		} else if (type == '?') {
			;
		} else {
            line_number++;
        }
    }
	/*
	struct symbol* x = symbol_table;
	while (x != NULL) {
		printf("%s %s\n", x->key, x->val);
		x = x->next;
	}
	*/
} 

// Perform actual translation, referencing symbol table.
int second_pass() {
	char* line = (char*) malloc(100*sizeof(char));
    char type;

    while (fgets(line, 1000, stdin) != NULL) {
		line = cleanupLine(line);
		// printf("line: %s end\n", line);
        char binline[] = "hellohithereheya"; 

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
	/*
	struct symbol* x = symbol_table;
	while (x != NULL) {
		printf("key: %s, val: %s\n", x->key, x->val);
		x = x->next;
	}	
	*/
}  

int main() {
    first_pass(); 		// this will be the symbol table
	rewind(stdin);
	second_pass(); 		// actual binary translation
}
