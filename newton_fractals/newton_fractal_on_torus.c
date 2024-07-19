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

/*  The goal of this file is to show off what libtmpl can do and create       *
 *  a really pretty picture. We'll use the complex functions, numerical       *
 *  routines, and the geometry tools provided to wrap the Newton fractal up   *
 *  onto a sphere.                                                            */

/*  We'll need stdio to write to the output ppm file.                         */
#include <libtmpl/include/tmpl_root_finding_complex.h>
#include <stdio.h>

/*  Geometry, numerical, math, and complex routines all found here.           */
#include <libtmpl/include/tmpl.h>

/*  The number of pixels in the x and y axes. If you want a higher resolution *
 *  for the output fractal, increase this number. It is best to make n*1024   *
 *  where n is some positive integer.                                         */
static const unsigned int size = 2*1024;
static const double coeffs[4] = {-1.0, 0.0, 0.0, 1.0};
static const unsigned int degree = 3;

/*  We can be more general and set up fractals for general polynomials. This  *
 *  cubic will have three roots, so set NRoots to 3, and compute the roots.   */
#define NRoots 3
static const tmpl_ComplexDouble ROOT_1 = {{1.0, 0.0}};
static const tmpl_ComplexDouble ROOT_2 = {{-0.5, +0.8660254037844386}};
static const tmpl_ComplexDouble ROOT_3 = {{-0.5, -0.8660254037844386}};

int main(void)
{
    /* Values for the min and max of the x and y axes.                        */
    double x_min = -3.0;
    double x_max =  3.0;
    double y_min = -3.0;
    double y_max =  3.0;
    double r = 1.0;
    double R = 2.0;

    /*  Declare some necessary variables for the geometry.                    */
    tmpl_TwoVectorDouble proj_P, planar_Z;
    tmpl_ThreeVectorDouble P;

    /* List the roots of z^3 - 1.                                             */
    tmpl_ComplexDouble roots[NRoots] = {ROOT_1, ROOT_2, ROOT_3};

    /*  More dummy variables to loop over.                                    */
    unsigned int x, y, n, ind;
    double z_x, z_y, min, temp, Px, Py, Pz, theta, phi, rho;
    tmpl_ComplexDouble *z, root;

    /*  Colors for the roots (Red, Green, Blue).                              */
    const unsigned char colors[NRoots][3] = {
        {0xFFU, 0x00U, 0x1EU},
        {0x00U, 0xFFU, 0x1EU},
        {0x00U, 0x1EU, 0xFFU}
    };

    unsigned char brightness[3];

    /*  Declare a variable for the output.                                    */
    FILE *fp;

    /* Open and name the file and give it write permission.                   */
    fp = fopen("newton_fractal_on_sphere.ppm", "w");

    /*  Needed to create the output ppm file. This is the preamble.           */
    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    /*  Loop over every pixel and perform the Newton-Raphson method with the  *
     *  given point as the initial guess for the algorithm.                   */
    for (y = 0; y < size; ++y)
    {
        /*  We want to center z_y so scale and shift. This makes the output   *
         *  picture lie in the box [x_min, x_max] x [y_min, y_max].           */
        z_y = (size - y - 1.0) * (y_max - y_min) /(size - 1) + y_min;

        for (x = 0; x < size; ++x)
        {
            /*  Similarly, center z_x.                                        */
            z_x = x * (x_max - x_min)/(size - 1) + x_min;

            planar_Z = tmpl_2DDouble_Rect(z_x, z_y);
            P = tmpl_Inverse_Orthographic_Projection_Torus(planar_Z, r, R);
            Pz = tmpl_3DDouble_Z(&P);

            if (tmpl_Double_Is_NaN(Pz))
                tmpl_PPM_Write_Color_From_Values(fp, 0x00U, 0x00U, 0x00U);

            else if (Pz > 0.999999)
                tmpl_PPM_Write_Color_From_Values(fp, 0x00U, 0x00U, 0x00U);

            else
            {
                Px = tmpl_3DDouble_X(&P);
                Py = tmpl_3DDouble_Y(&P);
                rho = tmpl_Double_Quick_Hypot(Px, Py) - R;
                theta = tmpl_Double_Arctan2(Py, Px);
                phi = tmpl_Double_Arctan2(Pz, rho);
                proj_P = tmpl_Stereographic_Projection_Torus(phi, theta, r, R);

                z = (tmpl_ComplexDouble *)&proj_P;

                root = tmpl_CDouble_Newtons_Method_Polynomial(
                    *z, coeffs, degree
                );

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

                /*  Set the colors to correspond to the nearest root.     */
                for (n=0; n<3; ++n)
                    brightness[n] = colors[ind][n];

                /*  Color the current pixel.                              */
                tmpl_PPM_Write_Color_From_Values(
                    fp, brightness[0], brightness[1], brightness[2]
                );
            }
        }
    }
    return 0;
}
