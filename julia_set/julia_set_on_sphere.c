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
#include <stdio.h>

/*  Needed for the "exit" function.                                           */
#include <stdlib.h>

/*  Complex numbers and routines here.                                        */
#include <libtmpl/include/tmpl_complex.h>

/*  2D and 3D vectors are defined here, as well as the stereographic and      *
 *  inverse orthographic projections.                                         */
#include <libtmpl/include/tmpl_vec2.h>
#include <libtmpl/include/tmpl_vec3.h>
#include <libtmpl/include/tmpl_spherical_geometry.h>

/*  Routines for creating the PPM figure found here.                          */
#include <libtmpl/include/tmpl_ppm.h>

static double coeffsa[32] = {
    0.0,  341.0,    0.0, 0.0, 0.0, 0.0,  67518.0,   0.0, 0.0, 0.0,
    0.0, -398505.0, 0.0, 0.0, 0.0, 0.0, -1060200.0, 0.0, 0.0, 0.0,
    0.0,  326895.0, 0.0, 0.0, 0.0, 0.0,  10602.0,   0.0, 0.0, 0.0,
    0.0, -19.0
};

static double coeffsb[31] = {
    -19.0,     0.0, 0.0, 0.0, 0.0, -10602.0,   0.0, 0.0, 0.0, 0.0,
     326895.0, 0.0, 0.0, 0.0, 0.0,  1060200.0, 0.0, 0.0, 0.0, 0.0,
    -398505.0, 0.0, 0.0, 0.0, 0.0, -67518.0,   0.0, 0.0, 0.0, 0.0,
     341.0
};

static tmpl_ComplexDouble func(tmpl_ComplexDouble z)
{
    tmpl_ComplexDouble f, g, out;

    f = tmpl_CDouble_Poly_Eval_Real_Coeffs(coeffsa, 31, z);
    g = tmpl_CDouble_Poly_Eval_Real_Coeffs(coeffsb, 30, z);
    out = tmpl_CDouble_Divide(f, g);
    return out;
}

/*  This variable acts as the location of the observer looking at the sphere. *
 *  we'll perform our inverse orthographic projection about this point. Note  *
 *  that this variable will be normalize so u and lambda*u will result in the *
 *  same drawing for all positive lambda. u and -u will produce drawings of   *
 *  the opposite side of the sphere.                                          */
static const tmpl_ThreeVectorDouble camera_pos = {{0.0, 0.0, 1.0}};

/*  The number of pixels in the x and y axes. If you want a higher resolution *
 *  for the output fractal, increase this number. It is best to make n*1024   *
 *  where n is some positive integer.                                         */
static const unsigned int size = 4U * 1024U;
static const unsigned int max_iters = 12U;

/*  Tolerance for finding the period of the Julia set.                        */
static const double eps = 1.0E-8;

/* Values for the min and max of the x and y axes.                            */
static const double x_min = -1.0;
static const double x_max = +1.0;
static const double y_min = -1.0;
static const double y_max = +1.0;

int main(void)
{
    /*  Declare some necessary variables for the geometry.                    */
    tmpl_TwoVectorDouble proj_P, planar_Z;
    tmpl_ThreeVectorDouble P, u;

    /*  More dummy variables to loop over.                                    */
    const double eps_sq = eps*eps;
    unsigned int x, y, n;
    double z_x, z_y, Pz, dist_sq, norm;
    tmpl_ComplexDouble z0, z1, z2;
    double rcp_factor = 1.0 / (double)(size - 1);
    tmpl_PPM_Color c;
    tmpl_PPM_Color tmpl_PPM_Gray = tmpl_PPM_Create_Color(0x80U, 0x80U, 0x80U);
    const double progress_factor = 100.0 / (double)size;

    /*  Declare a variable for the output.                                    */
    FILE *fp;

    /*  Normalize the camera vector and set this to u. First check that the   *
     *  user didn't provide the zero vector since this will cause an error.   */
    norm = tmpl_3DDouble_L2_Norm(&camera_pos);

    if (norm == 0.0)
    {
        puts("Input camera_pos is the zero vector. Aborting.\n");
        return -1;
    }

    u = tmpl_3DDouble_Normalize(&camera_pos);

    /* Open and name the file and give it write permission.                   */
    fp = fopen("julia_set_on_sphere.ppm", "w");

    /*  Needed to create the output ppm file. This is the preamble.           */
    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    /*  Loop over every pixel and perform the Newton-Raphson method with the  *
     *  given point as the initial guess for the algorithm.                   */
    for (y=0; y<size; ++y)
    {
        /*  We want to center z_y so scale and shift. This makes the output   *
         *  picture lie in the box [x_min, x_max] x [y_min, y_max].           */
        z_y = (size - y - 1.0) * (y_max - y_min) * rcp_factor + y_min;

        for (x=0; x<size; ++x)
        {
            /*  Similarly, center z_x.                                        */
            z_x = x * (x_max - x_min) * rcp_factor + x_min;

            if ((z_x*z_x + z_y*z_y >= 1.0))
                c = tmpl_PPM_Black;
            else
            {
                planar_Z = tmpl_2DDouble_Rect(z_x, z_y);
                P = tmpl_Inverse_Orthographic_Projection(planar_Z, u);
                Pz = tmpl_3DDouble_Z(&P);

                if (Pz > 0.999999)
                    c = tmpl_PPM_Gray;
                else
                {
                    proj_P = tmpl_Stereographic_Projection(P);

                    /*  tmpl_ComplexDouble and tmpl_TwoVectorDouble structs   *
                     *  define identical structures, so we can just cast      *
                     *  proj_P to a tmpl_ComplexDouble safely.                */
                    z0 = *(tmpl_ComplexDouble *)(&proj_P);

                    /*  Use the Newton-Raphson function to compute a root.    */
                    for(n = 0; n < max_iters; n++)
                    {
                        z1 = func(z0);
                        z2 = func(z1);
                        dist_sq = tmpl_CDouble_Dist_Squared(z0, z2);

                        if (dist_sq < eps_sq)
                            break;

                        z0 = z1;
                    }
                    if(n == max_iters)
                        c = tmpl_PPM_Black;
                    else
                        c = tmpl_PPM_Linear_Gradient(n, 0, max_iters);
                }
            }

            tmpl_PPM_Write_Color(fp, c);
        }

        if (y % 64 == 0U)
            fprintf(stderr, "Progress: %.4f%%  \r", progress_factor*y);
    }

    printf("\nDone.\n");
    fclose(fp);
    return 0;
}
