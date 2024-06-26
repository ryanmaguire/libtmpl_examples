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
 *  Date:       March 29, 2021                                                *
 ******************************************************************************/

/*  The puts function is found here.                                          */
#include <stdio.h>

/*  tmpl_Determine_Endianness is declared here.                               */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for testing the tmpl_Determine_Endianness function.              */
int main(void)
{
    /*  Declare a tmpl_Endian data type and compute the endianness.           */
    tmpl_Endian end = tmpl_Determine_Endianness();

    /*  Check the value of end and print the corresponding endianness.        */
    if (end == tmpl_LittleEndian)
        puts("Little Endian");
    else if (end == tmpl_MixedEndian)
        puts("Mixed Endian");
    else if (end == tmpl_BigEndian)
        puts("Big Endian");
    else
        puts("Unknown Endian");

    return 0;
}
/*  End of main.                                                              */
