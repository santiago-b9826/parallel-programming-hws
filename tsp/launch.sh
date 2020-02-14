#!/bin/bash

file_name="tsp-bf"
clear
[ -e $file_name.out ] && rm $file_name.out
gcc -Wall -fopenmp -o $file_name.out $file_name.c
[ $2 ] && a=$2  || a="default"
printf "Size: %s and Seed: %s\n\n" $1 $a
./$file_name.out $1 $2