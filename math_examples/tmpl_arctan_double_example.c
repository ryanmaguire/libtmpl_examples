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
 *      Provides an example of using tmpl_Double_Arctan function.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 12, 2022                                            *
 ******************************************************************************/

/*  printf is here.                                                           */
#include <stdio.h>

/*  DBL_MAX is found here.                                                    */
#include <float.h>

/*  tmpl_Double_Arctan function found here.                                   */
#include <libtmpl/include/tmpl_math.h>

/*  Function for showing use of tmpl_Double_Arctan function.                  */
int main(void)
{
    /*  Array for a few test values.                                          */
    double x[11];

    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Variable for the output.                                              */
    double out;

    /*  Set the values of the array.                                          */
    x[0] = 0.0;
    x[1] = -TMPL_INFINITY;
    x[2] = TMPL_INFINITY;
    x[3] = DBL_MAX;
    x[4] = -DBL_MAX;
    x[5] = DBL_MIN;
    x[6] = -DBL_MIN;
    x[7] = TMPL_NAN;
    x[8] = -TMPL_NAN;
    x[9] = 3.1415926;
    x[10] = -1.414;

    /*  Run tmpl_Double_Arctan on the test values.                            */
    for (n = 0U; n < sizeof(x)/sizeof(x[0]); ++n)
    {
        out = tmpl_Double_Arctan(x[n]);
        printf("|%.8e| = %.8e\n", x[n], out);
    }

    return 0;
}
/*  End of main.                                                              */
