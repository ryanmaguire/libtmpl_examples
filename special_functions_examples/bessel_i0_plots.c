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
#include <gsl/gsl_sf.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

static void write_val(FILE *fp, double x, double y)
{
    fwrite(&x, sizeof(x), 1, fp);
    fwrite(&y, sizeof(y), 1, fp);
}

int main(void)
{
    FILE *tmpl_fp, *gsl_fp, *dif_fp;

    double start = -20;
    double end   =  20;

    unsigned long N = 1e5;
    unsigned long n;
    double x, y0, y1, diff;

    double dx = (end - start) / (double)N;

    tmpl_fp = fopen("tmpl_bessel_i0_binary", "w");
    gsl_fp = fopen("gsl_bessel_i0_binary", "w");
    dif_fp = fopen("diff_binary", "w");

    x = start;
    for (n = 0; n<N; ++n)
    {
        y0 = tmpl_Double_Bessel_I0(x);
        write_val(tmpl_fp, x, y0);

        y1 = gsl_sf_bessel_I0(x);
        write_val(gsl_fp, x, y1);

        diff = (y1 - y0)/fabs(y1);
        write_val(dif_fp, x, diff);
        x += dx;
    }

    fclose(tmpl_fp);
    fclose(gsl_fp);
    fclose(dif_fp);

    system("graph -T ps -I d < tmpl_bessel_i0_binary gsl_bessel_i0_binary "
           "-L \"Bessel I0\" --reposition 0.0 -0.8 1 diff_binary "
           "-L \"Difference (tmpl vs gsl)\" > bessel_I0.ps");
    system("rm -f tmpl_bessel_i0_binary gsl_bessel_i0_binary diff_binary");
    return 0;
}
