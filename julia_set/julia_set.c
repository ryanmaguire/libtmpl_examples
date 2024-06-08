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
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Peter Doyle asked me to make this fractal some years ago. To date I   *
 *      still have no idea why it looks the way it does. But it is pretty.    *
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
    unsigned int x, y, n;
    double z_x, z_y, dist_sq;
    tmpl_ComplexDouble z0, z1, z2;
    tmpl_PPM_Color c;

    const unsigned int size = 4U * 1024U;
    const unsigned int max_iterations = 12U;

    const double x_min = -100.0;
    const double x_max = +100.0;
    const double y_min = -100.0;
    const double y_max = +100.0;
    const double eps = 1.0E-4;
    const double eps_sq = eps*eps;
    const double rcp_factor = 1.0 / (double)(size - 1U);
    const double progress_factor = 100.0 / (double)size;

    fp = fopen("julia_set.ppm", "w");

    if (!fp)
        return -1;

    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    for (y = 0U; y < size; ++y)
    {
        z_y = (size - y - 1) * (y_max - y_min) * rcp_factor + y_min;

        for (x = 0U; x < size; ++x)
        {
            z_x = x * (x_max - x_min) * rcp_factor + x_min;
            z0 = tmpl_CDouble_Rect(z_x, z_y);

            for (n = 0U; n < max_iterations; ++n)
            {
                z1 = func(z0);
                z2 = func(z1);
                dist_sq = tmpl_CDouble_Dist_Squared(z0, z2);

                if (dist_sq < eps_sq)
                    break;

                z0 = z1;
            }

            if (n == max_iterations)
                c = tmpl_PPM_Black;
            else
                c = tmpl_PPM_Linear_Gradient(n, 0, max_iterations);

            tmpl_PPM_Write_Color(fp, c);
        }

        if (y % 64 == 0U)
            fprintf(stderr, "Progress: %.4f%%  \r", progress_factor*y);
    }

    printf("\nDone.\n");
    fclose(fp);
    return 0;
}
