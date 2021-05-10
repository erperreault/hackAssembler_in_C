#!/bin/bash

check () {
	name=$(echo $1 | cut -f 1 -d '.')
	./a.out < $1 > $name.hackC
	diff $name.hack $name.hackC
}

# Assemble binary
gcc assembler.c

# Check all files
for FILE in $(ls programs | grep .asm)
do
	check programs/$FILE
done

# Cleanup
rm a.out programs/*.hackC
