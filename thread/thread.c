/*
 * =====================================================================================
 *
 *       Filename:  thread.c
 *
 *    Description:  线程计算游戏
 *
 *        Version:  1.0
 *        Created:  2013年07月27日 13时45分06秒
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

typedef struct calc_sum
{
	int start;
	int end;
}calc_sum_t;

void *thread_calc(void *args)
{
	calc_sum_t *calc_sum = (calc_sum_t *)args;

	int i;
	int *sum = (int *)malloc(sizeof(int));
	*sum = 0;

	for (i = calc_sum->start; i < calc_sum->end; i++) {
		*sum += i;
	}

	pthread_exit((void *)sum);
}

int main(int argc, char *argv[])
{
	pthread_t thread_1;
	pthread_t thread_2;
	calc_sum_t calc_num_1;
	calc_sum_t calc_num_2;

	calc_num_1.start = 20000;
	calc_num_1.end   = 40000;
	
	pthread_create(&thread_1, NULL, thread_calc, (void *)&calc_num_1);

	calc_num_2.start = 40000;
	calc_num_2.end   = 60000;

	pthread_create(&thread_2, NULL, thread_calc, (void *)&calc_num_2);

	int i;
	int sum = 0;
	for (i = 0; i < 20000; i++) {
		sum += i;
	}

	int *sum_thread;

	pthread_join(thread_1, (void **)&sum_thread);
	sum += *sum_thread;
	free(sum_thread);

	pthread_join(thread_2, (void **)&sum_thread);
	sum += *sum_thread;
	free(sum_thread);

	printf("%d\n", sum);

	return EXIT_SUCCESS;
}

