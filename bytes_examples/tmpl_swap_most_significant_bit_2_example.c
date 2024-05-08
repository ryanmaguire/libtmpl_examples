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
 *  Date:       March 12, 2021                                                *
 ******************************************************************************/

/*  The printf function is found here.                                        */
#include <stdio.h>

/*  tmpl_Swap_Most_Significant_Bit_2 is declared here.                        */
#include <libtmpl/include/tmpl_bytes.h>

/*  We'll need the macro CHAR_BIT from limits.h to see how big a char is.     *
 *  This is almost universally always 8 bits, but it can be 16 bits on        *
 *  handheld calculators, and 12-bits on other strange devices. For           *
 *  portability it never hurts to check.                                      */
#include <limits.h>

/*  Probe the macros in limits.h to find an integer data type that is two     *
 *  bytes. The C standard does not guarantee this must exist, so abort        *
 *  the compiling process if none is found.                                   */
#if CHAR_BIT == 8
#if USHRT_MAX == 0xFFFF
typedef short unsigned int two_byte_integer;
#elif UINT_MAX == 0xFFFF
typedef unsigned int two_byte_integer;
#else
#error "No 16-bit integer type found."
#endif
/*  End of #if USHRT_MAX == 0xFFFF.                                           */

#elif CHAR_BIT == 16
#if USHRT_MAX == 0xFFFFFFFF
typedef short unsigned int two_byte_integer;
#elif UINT_MAX == 0xFFFFFFFF
typedef unsigned int two_byte_integer;
#elif ULONG_MAX == 0xFFFFFFFF
typedef unsigned long int two_byte_integer;
#else
#error "No 32-bit integer type found."
#endif
/*  End of #if USHRT_MAX == 0xFFFFFFFF.                                       */

#else
#error "CHAR_BIT is neither 8 nor 16. Aborting."
#endif
/*  End of #if CHAR_BIT == 8.                                                 */

/*  Function for testing the tmpl_Swap_Most_Significant_Bit_2 function and    *
 *  showing basic use.                                                        */
int main(void)
{
    /*  Create a union with a two-byte-wide integer and a char array with     *
     *  two elements. We can swap the endianness of this integer using the    *
     *  tmpl_Swap_Most_Significant_Bit_2 function.                            */
    union {
        two_byte_integer x;
        char c[2];
    } u = { 0xFF00 };

    /*  Print the result before the swap.                                     */
    printf("Before: %u\n", (unsigned int)u.x);

    /*  Swap the most significant bit using the char array inside the union.  */
    tmpl_Swap_Most_Significant_Bit_2(u.c);

    /*  Print the result after the swap.                                      */
    printf("After: %u\n", u.x);
    return 0;
}
/*  End of main.                                                              */
