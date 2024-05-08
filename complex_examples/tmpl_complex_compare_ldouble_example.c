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
 *      Provides an example of using the compare function for complex numbers.*
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 22, 2020                                             *
 ******************************************************************************/

/*  Complex functions defined here.                                           */
#include <libtmpl/include/tmpl_complex.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for testing the compare function.                                 */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble z0[9], z1[9];
    long double re_z0, im_z0, re_z1, im_z1;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z0.                                  */
    z0[0] = tmpl_CLDouble_Zero;
    z0[1] = tmpl_CLDouble_One;
    z0[2] = tmpl_CLDouble_Rect(1.0L, 1.0L);
    z0[3] = tmpl_CLDouble_I;
    z0[4] = tmpl_CLDouble_Rect(-1.0L, 1.0L);
    z0[5] = tmpl_CLDouble_Rect(-1.0L, 0.0L);
    z0[6] = tmpl_CLDouble_Rect(-1.0L, -1.0L);
    z0[7] = tmpl_CLDouble_Rect(0.0L, -1.0L);
    z0[8] = tmpl_CLDouble_Rect(1.0L, -1.0L);

    /*  Set the test values in the array z1.                                  */
    z1[0] = tmpl_CLDouble_Zero;
    z1[1] = tmpl_CLDouble_Rect(1.0L, 1.0L);
    z1[2] = tmpl_CLDouble_One;
    z1[3] = tmpl_CLDouble_I;
    z1[4] = tmpl_CLDouble_Rect(-1.0L, 0.0L);
    z1[5] = tmpl_CLDouble_Rect(-1.0L, 1.0L);
    z1[6] = tmpl_CLDouble_Rect(-1.0L, -1.0L);
    z1[7] = tmpl_CLDouble_Rect(1.0L, -1.0L);
    z1[8] = tmpl_CLDouble_Rect(0.0L, -1.0L);

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 9U; ++n)
    {
        /*  Extract the real and imaginary parts from z0[n].                  */
        re_z0 = tmpl_CLDouble_Real_Part(z0[n]);
        im_z0 = tmpl_CLDouble_Imag_Part(z0[n]);

        /*  Extract the real and imaginary parts from z1[n].                  */
        re_z1 = tmpl_CLDouble_Real_Part(z1[n]);
        im_z1 = tmpl_CLDouble_Imag_Part(z1[n]);

        /*  Check if the values are equal.                                    */
        if (tmpl_CLDouble_Compare(z0[n], z1[n]))
            printf("%Lf + i%Lf = %Lf + i%Lf: True\n",
                   re_z0, im_z0, re_z1, im_z1);
        else
            printf("%Lf + i%Lf = %Lf + i%Lf: False\n",
                   re_z0, im_z0, re_z1, im_z1);
    }
    /*  End of for loop comparing z0 and z1.                                  */

    return 0;
}
/*  End of main.                                                              */
