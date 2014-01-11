/*
 * =====================================================================================
 *
 *       Filename:  sort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月21日 19时31分47秒
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

void swap(void *elem1, void *elem2, int size)
{
	char tmp[size];

	memcpy(tmp, elem1, size);
	memcpy(elem1, elem2, size);
	memcpy(elem2, tmp, size);
}

void sort(void *addr, int count, int size, int cmp(void *, void *))
{
	char *elem1 = (char *)addr;
	char *elem2 = (char *)addr + size;

	for (i = 0; i < N-1; i++) {
	      for (j = 0; j < N-1; j++)
	      {
		     if (cmp((char *)addr+(j+1)*size, (char *)addr+j*size))
		     {
			      swap(&array[j], &array[j+1], sizeof(int));
		     }
	      }
	}
}

int main(int argc, char *argv[])
{
	int array[N] = {1, 5, 8, 7, 4, 6, 9, 3, 0, 2};
	int i, j;

	for (i = 0; i < N; i++) {
		printf("%d\n", array[i]);
	}

	return EXIT_SUCCESS;
}

