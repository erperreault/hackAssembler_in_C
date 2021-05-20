# hackAssembler (in C)
An assembler for the HACK assembly language, implemented in C.

If you are interested in my learning process building this project, please see the extensive learning remarks in the /learning_remarks folder! In these files all original comments are removed and instead I have provided longer descriptions of specific challenges and how I grew by completing this project.

## Structure
* assembler.c -> The main procedures.
* parser.c -> Helper functions for string manipulation, data sanitization, etc
* data.c -> Hardcoded data and lookup table
* table.c -> Linked list data structure and functions for symbol table

Testing is automated through test.sh. All sample programs and output references are in /programs.
