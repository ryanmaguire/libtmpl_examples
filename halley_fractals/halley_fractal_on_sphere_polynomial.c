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
#include <libtmpl/include/tmpl_root_finding_complex.h>
#include <libtmpl/include/tmpl_vec2.h>
#include <libtmpl/include/tmpl_vec3.h>
#include <libtmpl/include/tmpl_spherical_geometry.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_ppm.h>

/*  This variable acts as the location of the observer looking at the sphere. *
 *  we'll perform our inverse orthographic projection about this point. Note  *
 *  that this variable will be normalize so u and lambda*u will result in the *
 *  same drawing for all positive lambda. u and -u will produce drawings of   *
 *  the opposite side of the sphere.                                          */
static const tmpl_ThreeVectorDouble camera_pos = {{1.0, 1.0, -1.0}};

/*  The number of pixels in the x and y axes. If you want a higher resolution *
 *  for the output fractal, increase this number. It is best to make n*1024   *
 *  where n is some positive integer.                                         */
static const unsigned int size = 1024;

static tmpl_ComplexDouble f(tmpl_ComplexDouble z)
{
    const double coeffs[4] = {-1.0, 0.0, 0.0, 1.0};
    return tmpl_CDouble_Poly_Eval_Real_Coeffs(coeffs, 3, z);
}

static tmpl_ComplexDouble f_prime(tmpl_ComplexDouble z)
{
    const double coeffs[3] = {0.0, 0.0, 3.0};
    return tmpl_CDouble_Poly_Eval_Real_Coeffs(coeffs, 2, z);
}

static tmpl_ComplexDouble f_2prime(tmpl_ComplexDouble z)
{
    const double coeffs[2] = {0.0, 6.0};
    return tmpl_CDouble_Poly_Eval_Real_Coeffs(coeffs, 1, z);
}

/*  We can be more general and set up fractals for general polynomials. This  *
 *  cubic will have three roots, so set NRoots to 3, and compute the roots.   */
#define NRoots 3
static const tmpl_ComplexDouble ROOT_1 = {{1.0, 0.0}};
static const tmpl_ComplexDouble ROOT_2 = {{-0.5, +0.8660254037844386}};
static const tmpl_ComplexDouble ROOT_3 = {{-0.5, -0.8660254037844386}};

int main(void)
{
    /* Values for the min and max of the x and y axes.                        */
    double x_min = -1.0;
    double x_max =  1.0;
    double y_min = -1.0;
    double y_max =  1.0;

    /*  Declare some necessary variables for the geometry.                    */
    tmpl_TwoVectorDouble proj_P, planar_Z;
    tmpl_ThreeVectorDouble P, u;

    /* List the roots of z^3 - 1.                                             */
    tmpl_ComplexDouble roots[NRoots] = {ROOT_1, ROOT_2, ROOT_3};

    /*  More dummy variables to loop over.                                    */
    unsigned int x, y, n, ind;
    double z_x, z_y, min, temp, Pz, norm;
    tmpl_ComplexDouble *z, root;

    /*  Colors for the roots (Red, Green, Blue).                              */
    const unsigned char colors[NRoots][3] = {
        {0xFF, 0x00, 0x00}, {0x00, 0xFF, 0x00}, {0x00, 0x00, 0xFF}
    };

    unsigned char brightness[3];

    /*  Declare a variable for the output.                                    */
    FILE *fp;

    /*  Normalize the camera vector and set this to u. First check that the   *
     *  user didn't provide the zero vector since this will cause an error.   */
    norm = tmpl_3DDouble_L2_Norm(&camera_pos);

    if (norm == 0.0)
    {
        puts(
            "\nError Encountered: tmpl\n"
            "\tnewton_fractal_on_sphere.c\n\n"
            "Your input camera_pos is the zero vector. Aborting.\n"
        );

        return -1;
    }
    else
        u = tmpl_3DDouble_Normalize(&camera_pos);

    /* Open and name the file and give it write permission.                   */
    fp = fopen("halley_fractal_on_sphere.ppm", "w");

    /*  Needed to create the output ppm file. This is the preamble.           */
    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    /*  Loop over every pixel and perform the Newton-Raphson method with the  *
     *  given point as the initial guess for the algorithm.                   */
    for (y=0; y<size; ++y)
    {
        /*  We want to center z_y so scale and shift. This makes the output   *
         *  picture lie in the box [x_min, x_max] x [y_min, y_max].           */
        z_y = y * (y_max - y_min)/(size - 1) + y_min;
        z_y = -z_y;

        for (x=0; x<size; ++x)
        {
            /*  Similarly, center z_x.                                        */
            z_x = x * (x_max - x_min)/(size - 1) + x_min;

            if ((z_x*z_x + z_y*z_y >= 1.0))
                tmpl_PPM_Write_Color_From_Values(fp, 0x00U, 0x00U, 0x00U);
            else
            {
                planar_Z = tmpl_2DDouble_Rect(z_x, z_y);
                P = tmpl_Inverse_Orthographic_Projection(planar_Z, u);
                Pz = tmpl_3DDouble_Z(&P);

                if (Pz > 0.999999)
                    tmpl_PPM_Write_Color_From_Values(fp, 0x00U, 0x00U, 0x00U);
                else
                {
                    proj_P = tmpl_Stereographic_Projection(P);

                    /*  tmpl_ComplexDouble and tmpl_TwoVectorDouble           *
                     *  define identical structures, so we can just cast      *
                     *  proj_P to a tmpl_ComplexDouble pointer and            *
                     *  perform Newton-Raphson with that.                     */
                    z = (tmpl_ComplexDouble *)&proj_P;

                    /*  Use the Newton-Raphson function to compute a root.    */
                    root = tmpl_CDouble_Halleys_Method_Explicit(
                        *z, f, f_prime, f_2prime
                    );

                    /*  Find which root the final iteration is closest too.   */
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
    }
    return 0;
}
