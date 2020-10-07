#!/bin/bash

file_name=$1
clear
[ -e $file_name.out ] && rm $file_name.out
gcc -Wall -fopenmp -o $file_name.out $file_name.c

line_separator_1="++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
line_separator_2="------------------------------------------------------";

for n in 150000000 1500000000 2147483647
do
    for thread in 2 4 8 16
    do
        echo $line_separator_1
        for value in {1..30}
        do 
            echo $value, $thread, $n $line_separator_2
            ./$file_name.out $thread $n
        done
    done
done
