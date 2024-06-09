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
#include <stdio.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_ppm.h>

static tmpl_ComplexDouble
square(tmpl_ComplexDouble z, tmpl_ComplexDouble c)
{
    tmpl_ComplexDouble out;

    out = tmpl_CDouble_Multiply(z, z);
    tmpl_CDouble_AddTo(&out, &c);
    return out;
}

int main(void)
{
    /*  Declare a variable for the output file and give it write permission.  */
    FILE *fp;
    unsigned int x, y, n;
    unsigned char red, green, blue;
    double z_x, z_y, norm_sq;
    tmpl_ComplexDouble z, c;

    const unsigned int max_iterations = 256U;
    const unsigned int size = 1024;

    const double x_min = -2.0;
    const double x_max = +2.0;
    const double y_min = -2.0;
    const double y_max = +2.0;

    const double radius = 4.0;
    const double radius_sq = radius * radius;

    const double rcp_factor = 1.0/ (double)(size - 1U);


    fp = fopen("mandelbrot_set.ppm", "w");
    fprintf(fp, "P6\n%d %d\n255\n", size, size);


    /*  Loop through each pixel.                                              */
    for (y = 0U; y < size; ++y)
    {
        /*  We want to center z_y so scale and shift. This makes the output   *
         *  picture lie in the box [x_min, x_max] x [y_min, y_max].           */
        z_y = (size - y - 1) * (y_max - y_min) * rcp_factor + y_min;

        for (x = 0U; x < size; ++x)
        {
            /*  Similarly, center z_x.                                        */
            z_x = x * (x_max - x_min) * rcp_factor + x_min;

            /*  Compute the complex number z_x + i z_y.                       */
            c = tmpl_CDouble_Rect(z_x, z_y);

            /*  Reset starting Real and Imaginary parts to zero.              */
            z = tmpl_CDouble_Zero;

            /*  Start the iteration process.                                  */
            for(n = 0; n < max_iterations; n++)
            {

                /*  Calculate real and imaginary parts.                       */
                z = square(z, c);

                /*  Check for divergence.                                     */
                norm_sq = tmpl_CDouble_Abs_Squared(z);

                if (norm_sq > radius_sq)
                    break;
            }

            if (n == max_iterations)
            {
                red = 0x00U;
                green = 0x00U;
                blue = 0x00U;
            }

            else if (n < 0x40U)
            {
                red = (unsigned char) (n << 2);
                green = red;
                blue = 0xFFU - red;
            }

            else
            {
                red = 0xFFU;
                green = 0xFFU;
                blue = 0xFFU;
            }

            tmpl_PPM_Write_Color_From_Values(fp, red, green, blue);
        }
    }
    return 0;
}
