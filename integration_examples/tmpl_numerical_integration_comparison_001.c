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
#include <libtmpl/include/tmpl_integration.h>
#include <libtmpl/include/tmpl_math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	size_t n;
	clock_t t0, t1;
	const double start = 0.0;
	const double end = 1001.0;
	const size_t zero = (size_t)0;
	const size_t len = (size_t)(1E7);
	const double dx = (end - start) / ((double)len - 1.0);
	double *arr = malloc(sizeof(*arr)*len);
	double x = 0.0;
	double lsum, rsum, tsum;
	const double exact = 2.0 / tmpl_One_Pi;

	for (n = zero; n < len; ++n)
	{
		arr[n] = tmpl_Double_SinPi(x);
		x += dx;
	}

	t0 = clock();
	lsum = tmpl_Double_Left_Riemann_Sum(arr, dx, len);
	t1 = clock();
	printf("Left Time:  %e\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

	t0 = clock();
	rsum = tmpl_Double_Right_Riemann_Sum(arr, dx, len);
	t1 = clock();
	printf("Right Time: %e\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

	t0 = clock();
	tsum = tmpl_Double_Trapezoid_Sum(arr, dx, len);
	t1 = clock();
	printf("Trap Time:  %e\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

	printf("Right:       %.16e\n", rsum);
	printf("Left:        %.16e\n", lsum);
	printf("Trap:        %.16e\n", tsum);
	printf("Right Error: %.16e\n", rsum - exact);
	printf("Left Error:  %.16e\n", lsum - exact);
	printf("Trap Error:  %.16e\n", tsum - exact);
	return 0;
}
