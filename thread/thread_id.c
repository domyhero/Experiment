/*
 * =====================================================================================
 *
 *       Filename:  thread_id.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月30日 12时30分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define gettid() syscall(224)

void *thread_func(void *args)
{
	printf("Thread: pid: %d real id: %u pthread: %lu\n", getpid(), gettid(), pthread_self());
	while (1) {
		sleep(10);
	}
}

int main(int argc, char *argv[])
{
	pthread_t pthread1, pthread2;

	printf("Main  : pid: %u real id: %u pthread: %lu\n", getpid(), gettid(), pthread_self());

	pthread_create(&pthread1, NULL, thread_func, NULL);
	pthread_create(&pthread2, NULL, thread_func, NULL);

	pthread_join(pthread1, NULL);
	pthread_join(pthread2, NULL);

	return EXIT_SUCCESS;
}

