clear
file_name=$1
gcc -Wall -fopenmp -o $file_name.out $file_name.c
./$file_name.out $2 $3 $4