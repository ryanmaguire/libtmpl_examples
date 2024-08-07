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

/*  Function for showing basic use of tmpl_3DLDouble_Cross_Product.           */
int main(void)
{
    /*  Declare all necessary variables.                                      */
    const long double x0 = 1.0L;
    const long double y0 = 2.0L;
    const long double z0 = 3.0L;
    const long double x1 = 4.0L;
    const long double y1 = 5.0L;
    const long double z1 = 6.0L;

    /*  Create two vectors from the given real values above.                  */
    const tmpl_ThreeVectorLongDouble V0 = tmpl_3DLDouble_Rect(x0, y0, z0);
    const tmpl_ThreeVectorLongDouble V1 = tmpl_3DLDouble_Rect(x1, y1, z1);

    /*  Compute the vector product of V0 and V1.                              */
    const tmpl_ThreeVectorLongDouble
        cross = tmpl_3DLDouble_Cross_Product(&V0, &V1);

    /*  Extract the components from cross.                                    */
    const long double xs = tmpl_3DLDouble_X(&cross);
    const long double ys = tmpl_3DLDouble_Y(&cross);
    const long double zs = tmpl_3DLDouble_Z(&cross);

    /*  Print the result.                                                     */
    printf("   (%Lf, %Lf, %Lf) x\n   (%Lf, %Lf, %Lf)\n = (%Lf, %Lf, %Lf)\n",
           x0, y0, z0, x1, y1, z1, xs, ys, zs);
    return 0;
}
/*  End of main.                                                              */
