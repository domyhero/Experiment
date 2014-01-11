/*
 * =====================================================================================
 *
 *       Filename:  time.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年12月09日 16时08分08秒
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
	int min = 0;
	int sec = 0;
	char buff[20];
	
	if (argc == 1) {
		printf("Usage: %s seconds\n", argv[0]);
		exit(0);
	}
	sec = atoi(argv[1]);
	min = sec / 60;
	sec %= 60;

	while (min != 0 || sec != 0) {
		if (sec == 0 && min != 0) {
			min--;
			sec = 60;
		}
		sec--;
		sleep(1);
		sprintf(buff, "banner %02d:%02d", min, sec);
		system("clear");
		system(buff);
	}

	system("clear");
	system("banner TIME-OVER!");

	return EXIT_SUCCESS;
}

