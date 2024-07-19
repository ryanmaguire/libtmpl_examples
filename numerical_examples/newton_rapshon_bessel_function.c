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

/*  We'll need stdio for printing the roots of the Bessel J_0 function.       */
#include <stdio.h>

/*  The Newton-Raphson routine is found here.                                 */
#include <libtmpl/include/tmpl_root_finding_real.h>

/*  The bessel function J_0 is defined here.                                  */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Create an alias for the Bessel function as "f".                           */
static double (*f)(double) = tmpl_Double_Bessel_J0;

/*  Numerically compute the derivative.                                       */
static double f_prime(double x)
{
    const double h = 1.0E-8;
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

int main(void)
{
    /*  Choose a value close to where we think the root is. By looking at the *
     *  graph of J_0(x) we can guess that a root lies between 2 and 3.        */
    double x0 = 2.0;
    double root;
    unsigned int max_iters = 20;
    const double eps = 1.0E-8;

    /*  Use Newton-Raphson to compute the root.                               */
    root = tmpl_Newton_Raphson_Double(x0, f, f_prime, max_iters, eps);

    /*  Print the result.                                                     */
    printf("First positive root of J_0: %f\n", root);
    return 0;
}
