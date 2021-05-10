#!/bin/bash

gcc assembler.c
mv a.out programs
cd programs
./a.out < Add.asm > Add.hackC
./a.out < MaxL.asm > MaxL.hackC
./a.out < PongL.asm > PongL.hackC
diff Add.hack Add.hackC
diff MaxL.hack MaxL.hackC
diff PongL.hack PongL.hackC
