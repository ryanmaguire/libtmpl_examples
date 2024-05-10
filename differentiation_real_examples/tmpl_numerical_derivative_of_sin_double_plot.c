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
 *      Provides an example of using numerical differentiation to plot the    *
 *      derivative of the sine function.                                      *
 *  Notes:                                                                    *
 *      This routine makes use of the "system" function and plotutils must    *
 *      be installed for this to work.                                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2024/01/26                                                    *
 ******************************************************************************/

/*  Used for the FILE date type and writing data.                             */
#include <stdio.h>

/*  The system function is provided here. Used for calling plotutils.         */
#include <stdlib.h>

/*  Trig functions given here.                                                */
#include <libtmpl/include/tmpl_math.h>

/*  Numerical differentiation.                                                */
#include <libtmpl/include/tmpl_differentiation_real.h>

/*  Command for creating the plots from binary data.                          */
static const char plot_command[] =
    "graph -T ps -I d "
   "sin_binary -L \"Sin Plot\" "
   "--reposition 0.0 -0.8 1.0 cos_binary -L \"Derivative Plot\" "
   "--reposition 0.0 -1.6 1.0 diff_binary -L \"Difference Plot\" "
   "> sin_derivative.ps";

/*  Command for cleaning up and removing the binary data.                     */
static const char rm_command[] = "rm -f sin_binary cos_binary diff_binary";

/*  Function for writing a data point to the file.                            */
static void write_val(FILE * const fp, double x, double y)
{
    fwrite(&x, sizeof(x), 1, fp);
    fwrite(&y, sizeof(y), 1, fp);
}

/*  Function for plotting the numerical derivative of sine against cosine.    */
int main(void)
{
    /*  Left-most point on the x axis that is used.                           */
    const double start = -20.0;

    /*  Right-most point on the x axis that is to be plotted.                 */
    const double end = 20.0;

    /*  Zero, cast to type "size_t" for indexing over the array.              */
    const size_t zero = (size_t)0;

    /*  Number of points to be plotted.                                       */
    const size_t n_elements = (size_t)(1E3);

    /*  Displacement between plot points.                                     */
    const double dx = (end - start) / (double)n_elements;

    /*  Variable for indexing.                                                */
    size_t n;

    /*  Open three files: The data for sin, cos, and the difference between   *
     *  cos and the result of the numerical derivative.                       */
    FILE * const sin_fp = fopen("sin_binary", "w");
    FILE * const cos_fp = fopen("cos_binary", "w");
    FILE * const diff_fp = fopen("diff_binary", "w");

    /*  Variable for looping over data points.                                */
    double x = start;

    /*  Loop across the data set and compute.                                 */
    for (n = zero; n < n_elements; ++n)
    {
        /*  Compute sin(x) and the numerical derivative of sin at x. The      *
         *  exact value is cos(x). Compute cos(x) and then compare the result *
         *  of the numerical derivative with the actual value.                */
        const double y = tmpl_Double_Sin(x);
        const double dy = tmpl_Double_Derivative(tmpl_Double_Sin, x);
        const double z = tmpl_Double_Cos(x);
        const double diff = tmpl_Double_Abs(z - dy);

        /*  Write all of this to the data files.                              */
        write_val(sin_fp, x, y);
        write_val(cos_fp, x, dy);
        write_val(diff_fp, x, diff);

        /*  Move to the next data point.                                      */
        x += dx;
    }

    /*  We're done writing data, close all of the files.                      */
    fclose(sin_fp);
    fclose(cos_fp);
    fclose(diff_fp);

    /*  Make the plots and clean up the binary files.                         */
    system(plot_command);
    system(rm_command);

    return 0;
}
/*  End of main.                                                              */
