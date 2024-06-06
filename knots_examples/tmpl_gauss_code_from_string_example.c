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
#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char str[] = "O4+O0+U1+O2+O3+U3+U0+O1+U2+U4+";
    unsigned int to_delete = 0U;
    tmpl_VirtualKnot *K = tmpl_Gauss_Code_From_String(str);

    printf("Input Gauss Code: ");
    tmpl_Print_Gauss_Code(K);

    if (tmpl_Is_Gauss_Code_Valid(K))
        puts("This is a valid Gauss code.\n");
    else
        puts("This is an invalid Gauss code.\n");

    puts("Performing Reidemeister I Reductions.");
    tmpl_Reidemeister_One_Reduction(K);
    printf("New Gauss Code: ");
    tmpl_Print_Gauss_Code(K);

    if (tmpl_Is_Gauss_Code_Valid(K))
        puts("This is a valid Gauss code.");
    else
        puts("This is an invalid Gauss code.");

    printf("Genus: %lu\n\n", tmpl_Virtual_Knot_Genus(K));

    printf("Deleting Crossing: %d\n", to_delete);
    tmpl_Delete_Virtual_Knot_Crossing(K, to_delete);

    printf("After: ");
    tmpl_Print_Gauss_Code(K);
    if (tmpl_Is_Gauss_Code_Valid(K))
        puts("This is a valid Gauss code.");

    printf("Genus: %lu\n", tmpl_Virtual_Knot_Genus(K));
    tmpl_Destroy_Virtual_Knot_Pointer(&K);

    return 0;
}
