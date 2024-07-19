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

/*  The Euclidean norm is declared here.                                      */
#include <libtmpl/include/tmpl_vec3.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for computing the norm of the vector (1, 2, 3).                   */
int main(void)
{
    /*  Set the x, y, and z values to 1, 2, and 3, respectively.              */
    const float x = 1.0F;
    const float y = 2.0F;
    const float z = 3.0F;

    /*  Set p to the vector (x, y, z).                                        */
    const tmpl_ThreeVectorFloat p = tmpl_3DFloat_Rect(x, y, z);

    /*  Compute the norm of p.                                                */
    const float norm = tmpl_3DFloat_L2_Norm(&p);

    /*  Print the result:                                                     */
    printf("||(%f, %f, %f)|| = %f\n",
           (double)x, (double)y, (double)z, (double)norm);
    return 0;
}
/*  End of main.                                                              */
