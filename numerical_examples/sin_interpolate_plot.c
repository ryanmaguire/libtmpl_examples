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
#include <math.h>
#include <libtmpl/include/tmpl_interpolate.h>
#include <libtmpl/include/tmpl_math.h>

static void write_val(FILE *fp, double x, double y)
{
    fwrite(&x, sizeof(x), 1, fp);
    fwrite(&y, sizeof(y), 1, fp);
}


int main(void)
{
    FILE *linear_fp, *interp_fp, *diff_fp;

    const unsigned long N = 10000U;
    const unsigned long N_new = 100000U;
    unsigned long n;

    const double start = -3.0;
    const double end = +3.0;
    double dx =  (end - start) / N;

    double *x = malloc(sizeof(x) * (N + 1));
    double *y = malloc(sizeof(y) * (N + 1));
    double *x_new = malloc(sizeof(x_new) * N_new);
    double *y_new = malloc(sizeof(y_new) * N_new);

    x[0] = start;
    y[0] = tmpl_Double_Sin(x[0]);

    for (n = 1; n <= N; ++n)
    {
        x[n] = x[n-1] + dx;
        y[n] = tmpl_Double_Sin(x[n]);
    }

    dx = (end - start) / N_new;
    x_new[0] = start;

    for (n = 1U; n < N_new; ++n)
        x_new[n] = x_new[n-1] + dx;

    tmpl_Double_Sorted_Interp1d(x, y, N+1, x_new, y_new, N_new);

    free(x);
    free(y);

    y = malloc(sizeof(y) * N_new);

    for (n=0; n<N_new; ++n)
        y[n] = tmpl_Double_Sin(x_new[n]);

    linear_fp = fopen("linear_binary", "w");
    interp_fp = fopen("interp_binary", "w");
    diff_fp   = fopen("diff_binary", "w");

    for (n=0; n<N_new; ++n)
    {
        write_val(linear_fp, x_new[n], y[n]);
        write_val(interp_fp, x_new[n], y_new[n]);
        write_val(diff_fp, x_new[n], y_new[n] - y[n]);
    }

    fclose(interp_fp);
    fclose(linear_fp);
    fclose(diff_fp);

    system("graph -T ps -I d < linear_binary interp_binary "
           "--reposition 0.0 -0.8 1 diff_binary > sin_interp.ps");
    system("rm -f linear_binary interp_binary diff_binary");

    free(y);
    free(x_new);
    free(y_new);

    return 0;
}
