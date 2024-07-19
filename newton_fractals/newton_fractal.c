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

/*  We'll need stdio to write to the output ppm file.                         */
#include <libtmpl/include/tmpl_root_finding_complex.h>
#include <stdio.h>

/*  Geometry, numerical, math, and complex routines all found here.           */
#include <libtmpl/include/tmpl.h>

/*  The function we're working with is f(z) = z^3 - 1, so create this.        */
static tmpl_ComplexDouble f(tmpl_ComplexDouble z)
{
    tmpl_ComplexDouble z_cubed, z_cubed_minus_1;
    z_cubed = tmpl_CDouble_Multiply(tmpl_CDouble_Multiply(z, z), z);
    z_cubed_minus_1 = tmpl_CDouble_Subtract(z_cubed, tmpl_CDouble_One);

    return z_cubed_minus_1;
}

/*  The derivative is f'(z) = 3z^2, so create this.                           */
static tmpl_ComplexDouble f_prime(tmpl_ComplexDouble z)
{
    tmpl_ComplexDouble w;
    w = tmpl_CDouble_Multiply_Real(3.0, tmpl_CDouble_Multiply(z, z));
    return w;
}

/*  We can be more general and set up fractals for general polynomials. This  *
 *  cubic will have three roots, so set NRoots to 3, and compute the roots.   */
#define NRoots 3
static const tmpl_ComplexDouble ROOT_1 = {{1.0, 0.0}};
static const tmpl_ComplexDouble ROOT_2 = {{-0.5, +0.8660254037844386}};
static const tmpl_ComplexDouble ROOT_3 = {{-0.5, -0.8660254037844386}};

/*  This function is used to set the current pixel of the output ppm to the   *
 *  desired color. fp is the filename we'll be using.                         */
static void
color(unsigned char red, unsigned char green, unsigned char blue, FILE *fp)
{
    fputc(red,   fp);
    fputc(green, fp);
    fputc(blue,  fp);
}

int main(void)
{
    /* Values for the min and max of the x and y axes.                        */
    const double x_min = -1.0;
    const double x_max =  1.0;
    const double y_min = -1.0;
    const double y_max =  1.0;

    /*  The number of pixels in the x and y axes. If you want a higher        *
     *  resolution for the output fractal, increase this number. It is best   *
     *  to make n*1024 where n is some positive integer.                      */
    const unsigned int size  = 1024;

    /* List the roots of z^3 - 1.                                             */
    tmpl_ComplexDouble roots[NRoots] = {ROOT_1, ROOT_2, ROOT_3};

    /*  More dummy variables to loop over.                                    */
    unsigned int x, y, n, ind;
    double z_x, z_y, min, temp;
    tmpl_ComplexDouble z, root;

    /*  Colors for the roots (Red, Green, Blue).                              */
    const unsigned char colors[NRoots][3] = {
        {0xFFU, 0x00U, 0x1EU},
        {0x00U, 0xFFU, 0x1EU},
        {0x00U, 0x1EU, 0xFFU}
    };

    unsigned char brightness[3];

    /*  Declare a variable for the output file and give it write permission.  */
    FILE *fp = fopen("newton_fractal.ppm", "w");

    /*  Needed to create the output ppm file. This is the preamble.           */
    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    /*  Loop over every pixel and perform the Newton-Raphson method with the  *
     *  given point as the initial guess for the algorithm.                   */
    for (y = 0; y < size; ++y)
    {
        /*  We want to center z_y so scale and shift. This makes the output   *
         *  picture lie in the box [x_min, x_max] x [y_min, y_max].           */
        z_y = y * (y_max - y_min)/(size - 1) + y_min;

        for (x = 0; x < size; ++x)
        {
            /*  Similarly, center z_x.                                        */
            z_x = x * (x_max - x_min)/(size - 1) + x_min;

            /*  Set out current guess to z_x + i z_y.                         */
            z = tmpl_CDouble_Rect(z_x, z_y);

            /*  Use the Newton-Raphson function to compute a root.            */
            root = tmpl_CDouble_Newtons_Method_Explicit(z, f, f_prime);

            /*  Find which root the final iteration is closest too.           */
            min = tmpl_CDouble_Dist(root, roots[0]);
            ind = 0;

            for (n=1; n<NRoots; ++n)
            {
                temp = tmpl_CDouble_Dist(root, roots[n]);
                if (temp < min) {
                    min = temp;
                    ind = n;
                }
            }

            /*  Set the colors to correspond to the nearest root.             */
            for (n=0; n<3; ++n)
                brightness[n] = colors[ind][n];

            /*  Color the current pixel.                                      */
            color(brightness[0], brightness[1], brightness[2], fp);
        }
    }
    return 0;
}
