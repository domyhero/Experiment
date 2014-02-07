/*
 * =====================================================================================
 *
 *       Filename:  thread_value.c
 *
 *    Description:  线程私有变量
 *
 *        Version:  1.0
 *        Created:  2014年02月07日 22时57分38秒
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
#include <pthread.h>

__thread int value = 1;

void *thread_func(void *args)
{
	value = 2;
	printf("Thread: %d\n", value);
}

int main(int argc, char *argv[])
{
	pthread_t thread;
	pthread_create(&thread, NULL, thread_func, NULL);

	pthread_join(thread, NULL);

	printf("main: %d\n", value);

	return EXIT_SUCCESS;
}

