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
    tmpl_ComplexFloat z0[9], z1[9];
    float re_z0, im_z0, re_z1, im_z1;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z0.                                  */
    z0[0] = tmpl_CFloat_Zero;
    z0[1] = tmpl_CFloat_One;
    z0[2] = tmpl_CFloat_Rect(1.0F, 1.0F);
    z0[3] = tmpl_CFloat_I;
    z0[4] = tmpl_CFloat_Rect(-1.0F, 1.0F);
    z0[5] = tmpl_CFloat_Rect(-1.0F, 0.0F);
    z0[6] = tmpl_CFloat_Rect(-1.0F, -1.0F);
    z0[7] = tmpl_CFloat_Rect(0.0F, -1.0F);
    z0[8] = tmpl_CFloat_Rect(1.0F, -1.0F);

    /*  Set the test values in the array z1.                                  */
    z1[0] = tmpl_CFloat_Zero;
    z1[1] = tmpl_CFloat_Rect(1.0F, 1.0F);
    z1[2] = tmpl_CFloat_One;
    z1[3] = tmpl_CFloat_I;
    z1[4] = tmpl_CFloat_Rect(-1.0F, 0.0F);
    z1[5] = tmpl_CFloat_Rect(-1.0F, 1.0F);
    z1[6] = tmpl_CFloat_Rect(-1.0F, -1.0F);
    z1[7] = tmpl_CFloat_Rect(1.0F, -1.0F);
    z1[8] = tmpl_CFloat_Rect(0.0F, -1.0F);

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 9U; ++n)
    {
        /*  Extract the real and imaginary parts from z0[n].                  */
        re_z0 = tmpl_CFloat_Real_Part(z0[n]);
        im_z0 = tmpl_CFloat_Imag_Part(z0[n]);

        /*  Extract the real and imaginary parts from z1[n].                  */
        re_z1 = tmpl_CFloat_Real_Part(z1[n]);
        im_z1 = tmpl_CFloat_Imag_Part(z1[n]);

        /*  Check if the values are equal.                                    */
        if (tmpl_CFloat_Compare(z0[n], z1[n]))
            printf("%f + i%f = %f + i%f: True\n",
                   (double)re_z0, (double)im_z0, (double)re_z1, (double)im_z1);
        else
            printf("%f + i%f = %f + i%f: False\n",
                   (double)re_z0, (double)im_z0, (double)re_z1, (double)im_z1);
    }
    /*  End of for loop comparing z0 and z1.                                  */

    return 0;
}
/*  End of main.                                                              */
