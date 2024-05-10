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
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an example of using the complex exponential function.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 11, 2020                                             *
 ******************************************************************************/

/*  Let's compute the complex exponential of the values 1, i, i pi, and pi.   */

/*  Complex exponential is declared here.                                     */
#include <libtmpl/include/tmpl_complex.h>

/*  Pi is defined here.                                                       */
#include <libtmpl/include/tmpl_math.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for computing the complex exponential for several test values.    */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble z[7];
    tmpl_ComplexDouble w[7];
    double re_z, im_z, re_w, im_w;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z.                                   */
    z[0] = tmpl_CDouble_Zero;
    z[1] = tmpl_CDouble_I;
    z[2] = tmpl_CDouble_Rect(0.0, tmpl_One_Pi);
    z[3] = tmpl_CDouble_Rect(TMPL_NAN, 0.0);
    z[4] = tmpl_CDouble_Rect(TMPL_INFINITY, 0.0);
    z[5] = TMPL_CNAN;
    z[6] = TMPL_CINFINITY;

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 7U; ++n)
    {
        /*  Compute the complex exponential of the nth value.                 */
        w[n] = tmpl_CDouble_Exp(z[n]);

        /*  Extract the real and imaginary parts from z[n] and w[n].          */
        re_z = tmpl_CDouble_Real_Part(z[n]);
        im_z = tmpl_CDouble_Imag_Part(z[n]);
        re_w = tmpl_CDouble_Real_Part(w[n]);
        im_w = tmpl_CDouble_Imag_Part(w[n]);

        /*  And finally, print the result to the screen.                      */
        printf("exp(%f + i%f) = %f + i%f\n", re_z, im_z, re_w, im_w);
    }
    /*  End of for loop computing exp(z).                                     */

    return 0;
}
/*  End of main.                                                              */
