#!/bin/bash

gcc -o matrix Matrix_multiplication.c #statement to run program.

for ((i=64;i<=400;i++)); #creating a for loop to enter different matrix sizes.
do
./matrix $i                      
done