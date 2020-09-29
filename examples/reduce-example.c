#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <string.h>

int sum_array(int n, int vec[]);
int prod_array(int n, int vec[]);
void print_vector(int n, int vec[]);

int main(int argc, char *argv[])
{
    // Define variables and input data
    int n = strtol(argv[1], NULL, 10);
    int m = strtol(argv[2], NULL, 10);
    char *opt = argv[3];
    int x[n];

    // Set random seed
    srand((unsigned int)time(NULL));

    // Initialize Vector with random values [0,m]
    for (int i = 0; i < n; i++)
    {
        x[i] = rand() % (m + 1);
    }

    // Select and execute reduce function
    int total = strcmp(opt, "sum") == 0 ? sum_array(n, x) : prod_array(n, x);

    print_vector(n, x);
    printf("Total: %d\n", total);

    return 0;
}

int sum_array(int n, int vec[])
{
    // Identity
    int sum = 0;

#pragma omp parallel for reduction(+ \
                                   : sum)
    for (int i = 0; i < n; i += 1)
    {
        sum += vec[i];
        printf("Instance %d from thread = %d\n", i, omp_get_thread_num());
    }
    return sum;
}

int prod_array(int n, int vec[])
{
    // Identity
    int prod = 1;

#pragma omp parallel for reduction(* \
                                   : prod)
    for (int i = 0; i < n; i += 1)
    {
        prod *= vec[i];
    }
    return prod;
}

void print_vector(int n, int vec[])
{
    for (int i = 0; i < n; i++)
    {
        printf("| %d ", vec[i]);
    }
    printf("|\n");
}