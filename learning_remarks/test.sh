#!/bin/bash

# This project actually gave me my first occasion to learn some shell scripting,
# even after a decade using Linux. I guess since I didn't know how to code in 
# the past, it didn't seem worth the investment. Now that I'm comfortable with
# programming, though, it only took me 20 minutes or so to learn the syntax
# and write a minimal script to automate my testing. Love it!
# 
# I intend to learn make in the future, but for this project a simple script
# was more than sufficient.

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
