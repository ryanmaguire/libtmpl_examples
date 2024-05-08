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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************/

/*  The printf function is found here.                                        */
#include <stdio.h>

/*  tmpl_Swap_Bytes is declared here.                                         */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for testing the tmpl_Swap_Bytes function and showing basic use.  */
int main(void)
{
    /*  Declare two unsigned char variables to test.                          */
    unsigned char c0, c1;

    /*  Set the char values to whatever you'd like.                           */
    c0 = 0x1FU;
    c1 = 0xEEU;

    /*  Print the result before the swap.                                     */
    printf("Before:\n\tc0 = %u\n\tc1 = %u\n", c0, c1);

    /*  Swap the bytes. tmpl_Swap_Bytes wants pointers to char values, so we  *
     *  need to grab the addresses of c0 and c1 via &c0 and &c1. Moreover, it *
     *  wants pointers to PLAIN char values, so we need to perform a cast.    *
     *  This is not necessary on most compilers, but with pedantic compiler   *
     *  warnings you may get something like -Wpointer-sign warnings.          *
     *  We cast the unsigned char pointer &c0 to a char pointer via           *
     *  (char *) &c0. Similarly for c1.                                       */
    tmpl_Swap_Bytes((char *)&c0, (char *)&c1);

    /*  Print the new results.                                                */
    printf("After:\n\tc0 = %u\n\tc1 = %u\n", c0, c1);

    return 0;
}
/*  End of main.                                                              */
