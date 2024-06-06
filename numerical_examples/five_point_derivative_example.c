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
#include <libtmpl/include/tmpl_differentiation_real.h>
#include <libtmpl/include/tmpl_math.h>

int main(void)
{
    const double dx = 0.001;
    const double h = 1.0E-8;
    double x = 0.0;
    double max = 0.0;
    double y0, y, diff;

    const unsigned int N = (unsigned int)(tmpl_Two_Pi / dx);
    unsigned int n;

    double (*f)(double) = tmpl_Double_Sin;
    double (*f_prime)(double) = tmpl_Double_Cos;

    for (n = 0U; n < N; ++n)
    {
        x += dx;
        y = f_prime(x);
        y0 = tmpl_Double_Five_Point_Derivative(f, x, h);
        diff = tmpl_Double_Abs(y - y0);

        if (max < diff)
            max = diff;
    }

    /*  Print the result.                                                     */
    printf("Maximum Absolute Error: %E\n", max);
    return 0;
}
