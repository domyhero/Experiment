/*
 * =====================================================================================
 *
 *       Filename:  thread_max.c
 *
 *    Description:  创建线程的最大数字
 *
 *        Version:  1.0
 *        Created:  2013年07月30日 15时00分27秒
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
#include <pthread.h>

void *thread_func(void *args)
{
	printf("tid: %u pid: %u thread id: %u\n", getpid(), syscall(224), pthread_self());
	while(1) {
		sleep(10);
	}
}

int main(int argc, char *argv[])
{
	pthread_t thread;
	int count = 0;

	while (pthread_create(&thread, NULL, thread_func, NULL) == 0) {
	//	sleep(1);
		count++;
	}

	sleep(1);

	perror("Create Error:");
	printf("Max Count:%d\n", count);

	return EXIT_SUCCESS;
}

