#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

int fibonacci(int n);

int main(int argc, char *argv[])
{
    double time;
    int k = argc == 2 ? strtol(argv[1], NULL, 10) : 10;
    time = omp_get_wtime();
    int n = fibonacci(k);
    time = omp_get_wtime() - time;
    printf("Fibonacci %d: %d in %lf\n", k, n, time);
    return 0;
}

int fibonacci(int n)
{
    if (n < 2)
        return n;
    int x = fibonacci(n - 1);
    int y = fibonacci(n - 2);
    return x + y;
}