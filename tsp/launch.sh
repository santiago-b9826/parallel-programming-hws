#!/bin/bash

file_name=$1
clear
[ -e $file_name.out ] && rm $file_name.out
gcc -Wall -fopenmp -o $file_name.out $file_name.c
[ $3 ] && a=$3  || a="default"
printf "Size: %s and Seed: %s\n\n" $2 $a
./$file_name.out $2 $3