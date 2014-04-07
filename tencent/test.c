/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年03月30日 14时41分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10000000

double randf(double a, double b)
{
	return (double)rand()*(b-a)/RAND_MAX + a;
}

int main(int argc, char *argv[])
{
	srand(time(0));

	int count = 0;

	int i;
	for (i = 0; i < N; i++) {
		double a = randf(-1.0f, 1.0f);
		double b = randf(-1.0f, 1.0f);
		if (a*a + b*b < 1.0f) {
			count++;
		}
	}

	printf("%f\n", 4.0f * ((double)count / N));

	return EXIT_SUCCESS;
}

