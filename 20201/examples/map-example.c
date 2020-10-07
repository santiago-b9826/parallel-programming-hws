#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void print_result(int n, float a, float x[], float y[], float y_copy[]);
void saxpy_openmp(int n, float a, float x[], float y[]);

int main(int argc, char *argv[])
{
    // Define variables and input data
    int n = strtol(argv[1], NULL, 10);
    float a = strtol(argv[2], NULL, 10);
    float x[n];
    float y[n];
    float y_copy[n];

    // Set random seed
    srand((unsigned int)time(NULL));

    // Initialize Vectors with random values
    for (int i = 0; i < n; i++)
    {
        x[i] = (float)rand() / (float)rand();
        y[i] = (float)rand() / (float)rand();
    }

    // Set Y Vector with Zeros
    //  memset(y, 0, sizeof(y));

    // Copy initial Y values
    memcpy(y_copy, y, sizeof(y_copy));

    // Call map function
    saxpy_openmp(n, a, x, y);

    // Print the result
    print_result(n, a, x, y, y_copy);
}

void saxpy_openmp(int n, float a, float x[], float y[])
{
#pragma omp parallel for
    for (int i = 0; i < n; ++i)
    {
        y[i] = a * x[i] + y[i];
        printf("Instance %d from thread = %d\n", i, omp_get_thread_num());
    }
}

void print_result(int n, float a, float x[], float y[], float y_copy[])
{
    for (int i = 0; i < n; i++)
    {
        printf("Y[%d] =  a * X[%d] + Y[%d]    <====>   %f = %f * %f + %f\n", i, i, i, y[i], a, x[i], y_copy[i]);
    }
}