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
 *      Provides an example of using the complex cosine function.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 11, 2020                                             *
 ******************************************************************************/

/*  Let's compute the complex cosine of the values pi, i pi, and 0, as well   *
 *  as complex and real nan and inf.                                          */

/*  Complex cosine is declared here.                                          */
#include <libtmpl/include/tmpl_complex.h>

/*  Pi and real nan and inf are defined here.                                 */
#include <libtmpl/include/tmpl_math.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for computing the complex cosine of various test values.          */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble z[7];
    tmpl_ComplexLongDouble w[7];
    long double re_z, im_z, re_w, im_w;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z.                                   */
    z[0] = tmpl_CLDouble_Zero;
    z[1] = tmpl_CLDouble_Rect(0.0L, tmpl_One_Pi_L);
    z[2] = tmpl_CLDouble_Rect(tmpl_One_Pi_L, 0.0L);
    z[3] = tmpl_CLDouble_Rect(TMPL_NANL, 0.0L);
    z[4] = tmpl_CLDouble_Rect(TMPL_INFINITYL, 0.0L);
    z[5] = TMPL_CNANL;
    z[6] = TMPL_CINFINITYL;

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 7U; ++n)
    {
        /*  Compute the complex cosine of the nth value.                      */
        w[n] = tmpl_CLDouble_Cos(z[n]);

        /*  Extract the real and imaginary parts from z[n] and w[n].          */
        re_z = tmpl_CLDouble_Real_Part(z[n]);
        im_z = tmpl_CLDouble_Imag_Part(z[n]);
        re_w = tmpl_CLDouble_Real_Part(w[n]);
        im_w = tmpl_CLDouble_Imag_Part(w[n]);

        /*  And finally, print the result to the screen.                      */
        printf("cos(%Lf + i%Lf) = %Lf + i%Lf\n", re_z, im_z, re_w, im_w);
    }
    /*  End of for loop computing cos(z).                                     */

    return 0;
}
/*  End of main.                                                              */
