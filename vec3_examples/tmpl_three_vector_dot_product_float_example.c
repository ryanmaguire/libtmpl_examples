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

/*  3D data types and functions found here.                                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  printf found here.                                                        */
#include <stdio.h>

/*  Function for showing basic use of tmpl_3DFloat_Dot_Product.               */
int main(void)
{
    /*  Declare all necessary variables.                                      */
    const float x0 = 1.0F;
    const float y0 = 2.0F;
    const float z0 = 3.0F;
    const float x1 = 4.0F;
    const float y1 = 5.0F;
    const float z1 = 6.0F;

    /*  Create two vectors from the given real values above.                  */
    const tmpl_ThreeVectorFloat V0 = tmpl_3DFloat_Rect(x0, y0, z0);
    const tmpl_ThreeVectorFloat V1 = tmpl_3DFloat_Rect(x1, y1, z1);

    /*  Compute the dot product of V0 and V1.                                 */
    const float dot = tmpl_3DFloat_Dot_Product(&V0, &V1);

    /*  Print the result.                                                     */
    printf("(%f, %f, %f) . (%f, %f, %f) = %f\n",
           (double)x0, (double)y0, (double)z0,
           (double)x1, (double)y1, (double)z1,
           (double)dot);
    return 0;
}
/*  End of main.                                                              */
