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

/*	3D vector functions found here.                                           */
#include <libtmpl/include/tmpl_vec3.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*	Function for computing orthogonal vectors.                                */
int main(void)
{
	/*	Create a vector in R^3.                                               */
	const tmpl_ThreeVectorLongDouble P = tmpl_3DLDouble_Rect(1, -1, 1);

	/*	Compute a vector orthogonal to the initial one.                       */
	const tmpl_ThreeVectorLongDouble Q = tmpl_3DLDouble_Orthogonal(&P);

	/*	Print the results.                                                    */
	printf("<%Lf, %Lf, %Lf>\n", P.dat[0], P.dat[1], P.dat[2]);
	printf("<%Lf, %Lf, %Lf>\n", Q.dat[0], Q.dat[1], Q.dat[2]);
	return 0;
}
