/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  calc
 *
 *        Version:  1.0
 *        Created:  2013年07月27日 13时51分08秒
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

int main(int argc, char *argv[])
{
	int i, sum = 0;

	for (i = 0; i < 60000; i++) {
		sum += i;
	}

	printf("%d\n", sum);

	return EXIT_SUCCESS;
}

