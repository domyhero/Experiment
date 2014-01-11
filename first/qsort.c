/*
 * =====================================================================================
 *
 *       Filename:  qsort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月21日 18时32分33秒
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

#define N 10

int cmp(const void *elem1, const void *elem2)
{
	return (*(int *)elem1 > *(int *)elem2);
}

int main(int argc, char *argv[])
{
	int array[N] = {5, 2, 8, 7, 9, 6, 0, 1, 3, 4};

	qsort(array, N, sizeof(int), cmp);

	int i;
	for (i = 0; i < N; i++) {
		printf("%d\n", array[i]);
	}

	return EXIT_SUCCESS;
}

