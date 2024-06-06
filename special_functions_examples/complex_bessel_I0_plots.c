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

/*  This program plots the real and imaginary parts of the complex bessel I0  *
 *  function using a color gradient to represent the values.                  */

/*  Needed for creating the output file.                                      */
#include <stdio.h>

/*  Contains malloc and free.                                                 */
#include <stdlib.h>

/*  Contains fabs.                                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Complex numbers.                                                          */
#include <libtmpl/include/tmpl_complex.h>

/*  Real Bessel functions found here.                                         */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Complex bessel function defined here.                                     */
#include <libtmpl/include/tmpl_special_functions_complex.h>

/*  The number of pixels in the x and y axes.                                 */
static const unsigned int size = 1024;

/*  This function is used to set the current pixel of the output ppm to the   *
 *  desired color. fp is the filename we'll be using.                         */
static void color(double mag, FILE *fp)
{
    /*  Declare variables for the color. We'll compute the color in RGB       *
     *  format, hence the need for these three variables.                     */
    unsigned char red, green, blue;

    /*  Use an RGB rainbow gradient to color the current pixel. We'll set     *
     *  blue to correspond to the least value and red for the greatest, with  *
     *  a continuous gradient in between.                                     */
    if (mag < 64)
    {
        red   = (unsigned char)0;
        green = (unsigned char)(4.0*mag);
        blue  = (unsigned char)255;
    }
    else if (mag < 128)
    {
        red   = (unsigned char)0;
        green = (unsigned char)255;
        blue  = (unsigned char)(255.0 - 4.0*(mag - 64.0));
    }
    else if (mag < 192)
    {
        red   = (unsigned char)(4.0*(mag - 128.0));
        green = (unsigned char)255;
        blue  = (unsigned char)0;
    }
    else
    {
        red   = (unsigned char)255;
        green = (unsigned char)(255.0 - 4.0*(mag - 192.0));
        blue  = (unsigned char)0;
    }

    /*  Color the current pixel.                                              */
    fputc(red,   fp);
    fputc(green, fp);
    fputc(blue,  fp);
}

int main(void)
{
    /* Values for the min and max of the x and y axes.                        */
    double x_min = -20.0;
    double x_max =  20.0;
    double y_min = -20.0;
    double y_max =  20.0;

    /*  Variables for the min and max of the real and imaginary parts of      *
     *  I0(z) in the region of interest.                                      */
    double min, max;

    /*  Declare variables needed for the computation.                         */
    unsigned int x, y;
    double z_x, z_y, w_x, w_y, rcp_factor;
    tmpl_ComplexDouble z, w;

    /*  Declare a variable for the output files.                              */
    FILE **fp;

    /*  Silly check to make sure the user provided a valid range for x and y. */
    if (x_max <= x_min)
    {
        puts("Error Encountered: tmpl\n"
             "\tcomplex_bessel_I0_plots.c\n\n"
             "x_min is greater than or equal to x_max.\n");
        exit(0);
    }
    else if (y_max <= y_min)
    {
        puts("Error Encountered: tmpl\n"
             "\tcomplex_bessel_I0_plots.c\n\n"
             "y_min is greater than or equal to y_max.\n");
        exit(0);
    }

    /*  Another silly error check to make sure size is greater than 1.        */
    if (size == 0)
    {
        puts("Error Encountered: tmpl\n"
             "\tcomplex_bessel_I0_plots.c\n\n"
             "Input size is zero. Aborting computation.\n");
        exit(0);
    }
    else if (size == 1)
    {
        puts("Error Encountered: tmpl\n"
             "\tcomplex_bessel_I0_plots.c\n\n"
             "Input size is one. This will cause divide-by-zero.\n"
             "Aborting computation.\n");
        exit(0);
    }

    /*  There are two files, so malloc memory for two.                        */
    fp = malloc(sizeof(*fp) * 2);

    /*  Create the files and give them write permissions.                     */
    fp[0] = fopen("complex_bessel_I0_real_part.ppm", "w");
    fp[1] = fopen("complex_bessel_I0_imag_part.ppm", "w");

    /*  Find the min and max of the function so we can set the color scale.   *
     *  This can be computed in terms of the bessel I0 function.              */
    if (tmpl_Double_Abs(y_min) < tmpl_Double_Abs(y_max))
        max = tmpl_Double_Bessel_I0(y_max);
    else
        max = tmpl_Double_Bessel_I0(y_min);

    /*  Compress the maximum to a smaller range.                              */
    max = tmpl_Double_Arctan(max);

    /*  For complex I0, the minimum is just minus the maximum.                */
    min = -max;

    /*  Needed to create the output ppm file. This is the preamble.           */
    fprintf(fp[0], "P6\n%d %d\n255\n", size, size);
    fprintf(fp[1], "P6\n%d %d\n255\n", size, size);

    /*  Translate max to be positive.                                         */
    max = max - min;

    /*  To translate from the pixel (x, y) to the point (z_x, z_y) lying in   *
     *  the rectangle [x_min, x_max] x [y_min, y_max] we'll need this term.   */
    rcp_factor = 1.0 / (size - 1.0);

    /*  Loop over each pixel and color it based on the value of I0(x+iy).     */
    for (y=0; y<size; ++y)
    {
        /*  We want to center z_y so scale and shift. This makes the output   *
         *  picture lie in the box [x_min, x_max] x [y_min, y_max].           */
        z_y = y * (y_max - y_min) * rcp_factor + y_min;

        for (x=0; x<size; ++x)
        {
            /*  Similarly, center z_x.                                        */
            z_x = x * (x_max - x_min) * rcp_factor + x_min;

            /*  Set z to x+iy.                                                */
            z = tmpl_CDouble_Rect(z_x, z_y);

            /*  Compute the I0(z).                                            */
            w = tmpl_CDouble_Bessel_I0(z);

            /*  Extract the real and imaginary parts of w.                    */
            w_x = tmpl_CDouble_Real_Part(w);
            w_y = tmpl_CDouble_Imag_Part(w);

            /*  Scale w_x and w_y to lie in the range [0, 255].               */
            w_x = 255*(tmpl_Double_Arctan(w_x) - min)/max;
            w_y = 255*(tmpl_Double_Arctan(w_y) - min)/max;

            /*  Color the current pixel.                                      */
            color(w_x, fp[0]);
            color(w_y, fp[1]);
        }
    }

    /*  Free the memory allocated to fp.                                      */
    free(fp);
    return 0;
}
