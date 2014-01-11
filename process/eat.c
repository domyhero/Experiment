/*
 * =====================================================================================
 *
 *       Filename:  eat.c
 *
 *    Description:  传说中的哲学家就餐问题
 *
 *        Version:  1.0
 *        Created:  2013年09月25日 14时46分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// 叉子的类型定义
typedef 
struct fork_t {
	int num; 		// 叉子编号
	pthread_mutex_t mutex;
} fork_t;

// 定义有 5 个叉子
fork_t fork_array[5] = {
	{0, PTHREAD_MUTEX_INITIALIZER},
	{1, PTHREAD_MUTEX_INITIALIZER},
	{2, PTHREAD_MUTEX_INITIALIZER},
	{3, PTHREAD_MUTEX_INITIALIZER},
	{4, PTHREAD_MUTEX_INITIALIZER}
};

// 记录已经吃了多少次了...
int eat_count[5];

// 线程处理函数，代表哲学家
void *thread_func(void *args)
{
	int num = (int)args;

	// 奇数编号哲学家先拿左边的叉子，再拿右边的叉子
	// 偶数号相反
	for (eat_count[num] = 0; eat_count[num] < 4; eat_count[num]++) {
		if (num & 1) {
			pthread_mutex_lock(&(fork_array[num].mutex));
			pthread_mutex_lock(&(fork_array[(num+1)%5].mutex));
			printf("%d 号哲学家拿到了 %d 和 %d 号叉子开始第 %d 次吃饭。\n",
					num, fork_array[num].num, fork_array[(num+1)%5].num, eat_count[num]+1);
			usleep(20000);
			pthread_mutex_unlock(&(fork_array[num].mutex));
			pthread_mutex_unlock(&(fork_array[(num+1)%5].mutex));
		} else {
			pthread_mutex_lock(&(fork_array[(num+1)%5].mutex));
			pthread_mutex_lock(&(fork_array[num].mutex));
			printf("%d 号哲学家拿到了 %d 和 %d 号叉子开始第 %d 次吃饭。\n",
					num, fork_array[num].num, fork_array[(num+1)%5].num, eat_count[num]+1);
			usleep(20000);
			pthread_mutex_unlock(&(fork_array[(num+1)%5].mutex));
			pthread_mutex_unlock(&(fork_array[num].mutex));
		}
	}
	printf("%d 号哲学家吃饱了...\n");
}

int main(int argc, char *argv[])
{
	pthread_t thread[5];

	int i;
	for (i = 0; i < 5; i++) {
		pthread_create(&thread[i], NULL, thread_func, (void *)i);
	}

	for (i = 0; i < 5; i++) {
		pthread_join(thread[i], NULL);
	}

	return EXIT_SUCCESS;
}

