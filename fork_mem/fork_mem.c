/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月25日 12时36分52秒
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
	int i;

	for (i = 0; i < 512*1024; i++) {
		char *addr = malloc(4096);
		if (addr == NULL) {
			printf("malloc error\n");
		}
		addr[0] = '0';
	}
	
	printf("malloc OK!\n");
	getchar();

	switch (fork()) {
	case 0:
		printf("child!\n");
		sleep(1000);
		break;
	case -1:
		printf("fork error!\n");
		break;
	default:
		printf("father!\n");
		sleep(1000);
	}

	return EXIT_SUCCESS;
}

