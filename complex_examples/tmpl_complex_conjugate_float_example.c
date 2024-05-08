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
 *      Provides an example of using the complex conjugate function.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 11, 2020                                             *
 ******************************************************************************/

/*  Complex functions defined here.                                           */
#include <libtmpl/include/tmpl_complex.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for computing the complex conjugate of various test values.       */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat z[7];
    tmpl_ComplexFloat w[7];
    float re_z, im_z, re_w, im_w;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z.                                   */
    z[0] = tmpl_CFloat_Zero;
    z[1] = tmpl_CFloat_One;
    z[2] = tmpl_CFloat_I;
    z[3] = tmpl_CFloat_Rect(1.0F, 1.0F);
    z[4] = TMPL_CNANF;
    z[5] = TMPL_CINFINITYF;

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 6U; ++n)
    {
        /*  Compute the complex conjugate of the nth value.                   */
        w[n] = tmpl_CFloat_Conjugate(z[n]);

        /*  Extract the real and imaginary parts from z[n] and w[n].          */
        re_z = tmpl_CFloat_Real_Part(z[n]);
        im_z = tmpl_CFloat_Imag_Part(z[n]);
        re_w = tmpl_CFloat_Real_Part(w[n]);
        im_w = tmpl_CFloat_Imag_Part(w[n]);

        /*  And finally, print the result to the screen.                      */
        printf("conj(%f + i%f) = %f + i%f\n",
               (double)re_z, (double)im_z, (double)re_w, (double)im_w);
    }
    /*  End of for loop computing conj(z).                                    */

    return 0;
}
/*  End of main.                                                              */
