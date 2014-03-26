/*
 * =====================================================================================
 *
 *       Filename:  bsearch.c
 *
 *    Description:  二分搜索
 *
 *        Version:  1.0
 *        Created:  2014年03月09日 12时44分23秒
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

int BSearch(int array[], int n, int value)
{
	int begin = 0, end = n - 1, mid;

	while (begin <= end) {
		mid = begin + ((end - begin) >> 1);
		if (array[mid] < value) {
			begin = mid + 1;
		} else if (array[mid] > value) {
			end = mid - 1;
		} else {
			return mid;
		}
	}

	return (end < 0) ? (begin) : (begin - 1);
}

int main(int argc, char *argv[])
{
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25, 35, 64, 84, 97, 102, 231, 254, 389, 500};
	int value = 0;

	int i;
	for(i = 0; i != sizeof(array)/sizeof(*array); ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");

	int index;
	for (; ;) {
		printf("Please input a number(-1 to quit): ");
		scanf("%d", &value);
		if (value == -1) {
			break;
		}
		if ((index = BSearch(array, sizeof(array)/sizeof(*array), value)) == -1) {
			printf("Not Found!\n");
		} else {
			printf("Index is %d\n", index);
		}
	}

	return EXIT_SUCCESS;
}

