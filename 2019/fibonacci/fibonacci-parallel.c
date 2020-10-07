#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

int fibonacci(int n);
int serialFibonacci(int n);

int main(int argc, char *argv[])
{
    double time;
    int k = argc == 2 ? strtol(argv[1], NULL, 10) : 10;

#pragma omp parallel
    {
#pragma omp master
        {
            time = omp_get_wtime();
            int n = fibonacci(k);
            time = omp_get_wtime() - time;
            printf("Fibonacci %d: %d in %lf\n", k, n, time);
        }
    }
    return 0;
}

int fibonacci(int n)
{
    int x, y;

    if (n < 2)
        return n;
    if (n <= 30)
        return serialFibonacci(n);
#pragma omp task shared(x)
    x = fibonacci(n - 1);

#pragma omp task shared(y)
    y = fibonacci(n - 2);

#pragma omp taskwait
    return x + y;
}

int serialFibonacci(int n)
{
    if (n < 2)
        return n;
    int x = fibonacci(n - 1);
    int y = fibonacci(n - 2);
    return x + y;
}