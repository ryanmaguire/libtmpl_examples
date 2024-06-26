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
 *      Provides an example of using tmpl_LDouble_Arctan function.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 12, 2022                                            *
 ******************************************************************************/

/*  printf is here.                                                           */
#include <stdio.h>

/*  LDBL_MAX is found here.                                                   */
#include <float.h>

/*  tmpl_LDouble_Arctan function found here.                                  */
#include <libtmpl/include/tmpl_math.h>

/*  Function for showing use of tmpl_LDouble_Arctan function.                 */
int main(void)
{
    /*  Array for a few test values.                                          */
    long double x[11];

    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Variable for the output.                                              */
    long double out;

    /*  Set the values of the array.                                          */
    x[0] = 0.0L;
    x[1] = -TMPL_INFINITYL;
    x[2] = TMPL_INFINITYL;
    x[3] = LDBL_MAX;
    x[4] = -LDBL_MAX;
    x[5] = LDBL_MIN;
    x[6] = -LDBL_MIN;
    x[7] = TMPL_NANL;
    x[8] = -TMPL_NANL;
    x[9] = 3.1415926L;
    x[10] = -1.414L;

    /*  Run tmpl_LDouble_Arctan on the test values.                           */
    for (n = 0U; n < sizeof(x)/sizeof(x[0]); ++n)
    {
        out = tmpl_LDouble_Arctan(x[n]);
        printf("|%.8Le| = %.8Le\n", x[n], out);
    }

    return 0;
}
/*  End of main.                                                              */
