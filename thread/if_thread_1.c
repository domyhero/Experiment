/*
 * =====================================================================================
 *
 *       Filename:  if_thread_1.c
 *
 *    Description:  原始方法一个例子
 *
 *        Version:  1.0
 *        Created:  2013年07月30日 10时48分45秒
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
#include <time.h>
#include <pthread.h>

#define STR_LENGTH 50

char *time_str = NULL;

void *thread_create_str(void *arg)
{
	time_t timeval;
	char *tmp = (char *)malloc(STR_LENGTH);
	
	// 假设该进程进行一个耗时的操作
	sleep(10);

	time(&timeval);
	bzero(tmp, STR_LENGTH);

	sprintf(tmp, "The date is: %s", ctime(&timeval));
	time_str = tmp;
}

void *thread_print_str(void *arg)
{
	while (time_str == NULL)
	      ;

	printf("%s", time_str);
}

int main(int argc, char *argv[])
{
	pthread_t thread_create;
	pthread_t thread_print;

	pthread_create(&thread_create, NULL, thread_create_str, NULL);
	pthread_create(&thread_print, NULL, thread_print_str, NULL);

	pthread_join(thread_create, NULL);
	pthread_join(thread_print, NULL);

	return EXIT_SUCCESS;
}

