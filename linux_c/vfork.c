/*
 * =====================================================================================
 *
 *       Filename:  vfork.c
 *
 *    Description:  探究vfork的return和exit
 *
 *        Version:  1.0
 *        Created:  2014年07月20日 14时47分48秒
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
#include <sys/types.h>

int globVar = 1;

int main(int argc, char *argv[])
{
	int var = 1, i = 0;

	pid_t pid = vfork();

	switch (pid) {
		// 子进程
		case 0:
			i = 3;
			while (i-- > 0) {
				printf("Child process is running var = %d  globVar = %d\n", var, globVar);
				globVar++;
				var++;
				sleep(1);
			}
			printf("Child`s globVar = %d, var = %d\n", globVar, var);
			break;
		// 错误
		case -1:
			perror("Process creation failed\n");
			exit(0);
		break;
		// 父进程
		default:
			i = 5;
			while (i-- > 0) {
				printf("\t\tParent process is running var = %d globVar = %d\n", var, globVar);
				globVar++;
				var++;
				sleep(1);
			}
			printf("\t\tParent globVar = %d, var = %d\n", globVar, var);
			exit(0);
	}
	printf("var = %d\n", var);

	return 0;
}

