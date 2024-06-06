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
#include <time.h>
#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_vector_integer.h>

int main(void)
{
    const unsigned long int N = 1000UL;
    unsigned long int n;
    tmpl_ULongVector *out = tmpl_ULong_Sieve_of_Eratosthenes(N);

    if (!out)
    {
        puts("out == NULL. Aborting.");
        return -1;
    }
    else if (out->error_occurred)
    {
        if (out->error_message != NULL)
            puts(out->error_message);
        else
            puts("error_occurred == true with no error message.");

        tmpl_Destroy_ULongVector(&out);
        return -1;
    }

    for (n = 0UL; n < out->length; ++n)
        printf("%03lu: %03lu\n", n, out->data[n]);

    tmpl_Destroy_ULongVector(&out);
    return 0;
}
