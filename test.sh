#!/bin/bash

check () {
	name=$(echo $1 | cut -f 1 -d '.')
	./a.out < $1 > $name.hackC
	diff $name.hack $name.hackC
}

gcc assembler.c

for FILE in $(ls programs | grep .asm)
do
	check programs/$FILE
done

rm a.out programs/*.hackC
