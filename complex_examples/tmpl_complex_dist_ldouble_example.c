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
 *      Provides an example of the complex distance function.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 23, 2020                                             *
 ******************************************************************************/

/*  Complex functions defined here.                                           */
#include <libtmpl/include/tmpl_complex.h>

/*  Real nan and inf found here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for computing the distance between complex values.                */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble z0[7], z1[7];
    long double w[7];
    long double re_z0, im_z0, re_z1, im_z1;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z0.                                  */
    z0[0] = tmpl_CLDouble_Zero;
    z0[1] = tmpl_CLDouble_One;
    z0[2] = tmpl_CLDouble_Rect(1.0L, 1.0L);
    z0[3] = tmpl_CLDouble_Rect(TMPL_NANL, 0.0L);
    z0[4] = tmpl_CLDouble_Rect(TMPL_INFINITYL, 0.0L);
    z0[5] = TMPL_CNANL;
    z0[6] = TMPL_CINFINITYL;

    /*  Set the test values for the array z1.                                 */
    z1[0] = tmpl_CLDouble_Rect(1.0L, 1.0L);
    z1[1] = tmpl_CLDouble_Rect(2.0L, 0.0L);
    z1[2] = tmpl_CLDouble_Rect(1.0L, 3.0L);
    z1[3] = tmpl_CLDouble_Rect(1.0L, 4.0L);
    z1[4] = tmpl_CLDouble_Rect(1.0L, 0.0L);
    z1[5] = tmpl_CLDouble_Rect(1.0L, 8.0L);
    z1[6] = tmpl_CLDouble_Rect(1.0L, 1.0L);

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 7U; ++n)
    {
        /*  Compute |z0 - z1| of the nth value.                               */
        w[n] = tmpl_CLDouble_Dist(z0[n], z1[n]);

        /*  Extract the real and imaginary parts from z0[n].                  */
        re_z0 = tmpl_CLDouble_Real_Part(z0[n]);
        im_z0 = tmpl_CLDouble_Imag_Part(z0[n]);

        /*  Extract the real and imaginary parts from z1[n].                  */
        re_z1 = tmpl_CLDouble_Real_Part(z1[n]);
        im_z1 = tmpl_CLDouble_Imag_Part(z1[n]);

        /*  And finally, print the result to the screen.                      */
        printf("|(%Lf + i%Lf) - (%Lf + i%Lf)| = %Lf\n",
               re_z0, im_z0, re_z1, im_z1, w[n]);
    }
    /*  End of for loop z0 + z1.                                              */

    return 0;
}
/*  End of main.                                                              */
