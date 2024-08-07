/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl_examples.                                    *
 *                                                                            *
 *  libtmpl_examples is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl_examples is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License along   *
 *  with libtmpl_examples. If not, see <https://www.gnu.org/licenses/>.       *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_sf.h>
#include <libtmpl/include/tmpl_interpolate.h>

static void write_val(FILE *fp, double x, double y)
{
    fwrite(&x, sizeof(x), 1, fp);
    fwrite(&y, sizeof(y), 1, fp);
}

static double frand(void)
{
    int n_rand = rand();
    return (double)n_rand / RAND_MAX;
}

int main(void)
{
    FILE *linear_fp, *interp_fp;

    const unsigned long N = 9;
    const unsigned long N_new = 20;
    unsigned long n;

    const double start = -0.5*(N - 1);
    const double end =  0.5*(N - 1);
    const double dx =  (end - start) / N_new;

    double *x = malloc(sizeof(x) * N);
    double *y = malloc(sizeof(y) * N);
    double *x_new = malloc(sizeof(x_new) * N_new);
    double *y_new = malloc(sizeof(y_new) * N_new);

    for (n = 0U; n < N; ++n)
    {
        x[n] = start + (double)n;
        y[n] = frand();
    }

    x_new[0] = start;
    for (n = 1U; n < N_new; ++n)
        x_new[n] = x_new[n - 1U] + dx;

    tmpl_Double_Sorted_Interp1d(x, y, N, x_new, y_new, N_new);

    linear_fp = fopen("linear_binary", "w");
    interp_fp = fopen("interp_binary", "w");

    for (n = 0U; n < N; ++n)
        write_val(linear_fp, x[n], y[n]);

    for (n = 0U; n < N_new; ++n)
        write_val(interp_fp, x_new[n], y_new[n]);

    fclose(interp_fp);
    fclose(linear_fp);

    system("graph -T ps -I d < linear_binary > data.ps");
    system("graph -T ps -I d < interp_binary > interp.ps");
    system("rm -f linear_binary interp_binary");

    for (n = 0; n < N; ++n)
        printf("%e %e\n", x[n], y[n]);

    puts("");

    for (n = 0; n < N_new; ++n)
        printf("%e %e\n", x_new[n], y_new[n]);

    free(x);
    free(y);
    free(x_new);
    free(y_new);
    return 0;
}
