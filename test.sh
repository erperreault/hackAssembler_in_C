#!/bin/bash

CC=gcc
SRC=assembler.c
OUT=assembler

check () {
	name=$(echo "$1" | cut -f 1 -d '.')
	./$OUT < $1 > $name.hackC
	diff $name.hack $name.hackC
}

# Compile assembler
$CC $SRC -o $OUT

# Assemble binaries and test each output 
for FILE in $(ls programs | grep .asm)
do
	check "programs/$FILE"
done

# Cleanup
rm $OUT programs/*.hackC
