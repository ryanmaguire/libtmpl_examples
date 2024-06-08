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

static const double coeffsa[32] = {
    0.0, +341.0,    0.0, 0.0, 0.0, 0.0, +67518.0,   0.0, 0.0, 0.0,
    0.0, -398505.0, 0.0, 0.0, 0.0, 0.0, -1060200.0, 0.0, 0.0, 0.0,
    0.0, +326895.0, 0.0, 0.0, 0.0, 0.0, +10602.0,   0.0, 0.0, 0.0,
    0.0, -19.0
};

static const double coeffsb[31] = {
    -19.0,     0.0, 0.0, 0.0, 0.0, -10602.0,   0.0, 0.0, 0.0, 0.0,
    +326895.0, 0.0, 0.0, 0.0, 0.0, +1060200.0, 0.0, 0.0, 0.0, 0.0,
    -398505.0, 0.0, 0.0, 0.0, 0.0, -67518.0,   0.0, 0.0, 0.0, 0.0,
    +341.0
};

static tmpl_ComplexDouble func(tmpl_ComplexDouble z)
{
    tmpl_ComplexDouble f, g, out;

    f = tmpl_CDouble_Poly_Eval_Real_Coeffs(coeffsa, 31, z);
    g = tmpl_CDouble_Poly_Eval_Real_Coeffs(coeffsb, 30, z);
    out = tmpl_CDouble_Divide(f, g);
    return out;
}

int main(void)
{
    FILE *fp;
    unsigned int x, y, n, nfile;
    double z_x, z_y, norm;
    tmpl_ComplexDouble z;
    tmpl_PPM_Color c;

    const unsigned int n_frames = 100U;
    const unsigned int size = 1024;
    const unsigned int max_iterations = 12U;

    const double rcp_factor = 1.0 / (double)(size - 1U);
    const double scale_factor = 0.9;
    const double radius = 8.0;

    char filename[17] = "julia_animation_";
    char nth_filename[23];

    double x_min = -1.0;
    double x_max = +1.0;
    double y_min = -1.0;
    double y_max = +1.0;

    for (nfile = 0U; nfile < n_frames; ++nfile)
    {
        if (nfile < 10)
            sprintf(nth_filename, "%s0%d.ppm", filename, nfile);
        else
            sprintf(nth_filename, "%s%d.ppm", filename, nfile);

        fp = fopen(nth_filename, "w");
        fprintf(fp, "P6\n%d %d\n255\n", size, size);

        for (y = 0U; y < size; ++y)
        {
            z_y = (size - y - 1.0) * (y_max - y_min) * rcp_factor + y_min;
            for (x = 0U; x < size; ++x)
            {
                z_x = x * (x_max - x_min) * rcp_factor + x_min;
                z = tmpl_CDouble_Rect(z_x, z_y);

                for (n = 0U; n < max_iterations; ++n)
                {
                    z = func(z);
                    norm = tmpl_CDouble_Abs(z);

                    if (norm > radius)
                        break;
                }

                if (n == max_iterations)
                    c = tmpl_PPM_Black;
                else
                    c = tmpl_PPM_Linear_Gradient(n, 0, max_iterations);

                tmpl_PPM_Write_Color(fp, c);
            }
        }

        printf("Current: %d    Total: %d\n", nfile, n_frames);
        fclose(fp);

        x_min *= scale_factor;
        x_max *= scale_factor;
        y_min *= scale_factor;
        y_max *= scale_factor;
    }

    return 0;
}
