/*
 *  OpenMP lecture exercises
 *  Copyright (C) 2011 by Christian Terboven <terboven@rz.rwth-aachen.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

void CalcPi(double *fPi, int n);

int main(int argc, char **argv)
{
    int n = 150000000;
    const double fPi25DT = 3.141592653589793238462643;
    double fPi = 0.0;
    double fTimeStart, fTimeEnd;
    int thread_count = strtol(argv[1], NULL, 10);

#ifdef READ_INPUT
    printf("Enter the number of intervals: ");
    scanf("%d", &n);
#endif

    if (n <= 0 || n > 2147483647)
    {
        printf("\ngiven value has to be between 0 and 2147483647\n");
        return 1;
    }
    fTimeStart = omp_get_wtime();

#pragma omp parallel num_threads(thread_count)
    CalcPi(&fPi, n);

    fTimeEnd = omp_get_wtime();
    printf("Pi is approximately: \t%.20f \nError: \t\t\t%.20f\n", fPi, fabs(fPi - fPi25DT));
    printf("Wall clock time: \t%.20f\n", fTimeEnd - fTimeStart);

    return 0;
}

double f(double a)
{
    return (4.0 / (1.0 + a * a));
}

void CalcPi(double *fPi, int n)
{
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    int local_n = n / thread_count;

    const double fH = 1.0 / (double)n;
    double fSum = 0.0;
    double fX;
    double aux = 0.0;
    int i;

    for (i = 0; i < local_n; i += 1)
    {
        fX = fH * ((double)(my_rank * local_n + i) + 0.5);
        fSum += f(fX);
    }
    aux = fH * fSum;
    printf("i: %d and Actual value: %.20f\n", (my_rank * local_n + i), aux);
#pragma omp critical
    *fPi += aux;
}