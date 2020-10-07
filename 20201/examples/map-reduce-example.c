#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void print_vector(int n, int *vec);
int openmp_sprod(int n, const int *a, const int *b);

int main(int argc, char *argv[])
{
    // Define variables and input data
    int n = strtol(argv[1], NULL, 10);
    int m = strtol(argv[2], NULL, 10);
    int *a = (int *)malloc(sizeof(int) * n);
    int *b = (int *)malloc(sizeof(int) * n);

    // Set random seed
    srand((unsigned int)time(NULL));

    // Initialize Vectors with random values
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % (m + 1);
        b[i] = rand() % (m + 1);
    }

    // Call map-reduce function
    int total = openmp_sprod(n, a, b);

    print_vector(n, a);
    print_vector(n, b);
    printf("Total: %d\n", total);
}

int openmp_sprod(int n, const int *a, const int *b)
{
    int res = 0;
#pragma omp parallel for reduction(+ \
                                   : res)
    for (int i = 0; i < n; i++)
    {
        res += a[i] * b[i];
    }
    return res;
}

void print_vector(int n, int *vec)
{
    for (int i = 0; i < n; i++)
    {
        printf("| %d ", vec[i]);
    }
    printf("|\n");
}