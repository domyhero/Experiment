/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月13日 16时36分29秒
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


int main(int argc, char *argv[])
{
	int n = 10000000;

	printf("PID: %d\n", getpid());
	printf("addr_vir of n is %u, %p\n", (unsigned int)&n, &n);

	while (--n) {
		sleep(3);
	}

	printf("I am break!\n");

	return EXIT_SUCCESS;
}

