/*
 * =====================================================================================
 *
 *       Filename:  producer_consumer.c
 *
 *    Description:  生产者消费者问题
 *
 *        Version:  1.0
 *        Created:  2013年09月26日 00时01分37秒
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
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_LENGTH 10

struct queue_buff {
	int buff[QUEUE_LENGTH]; 	// 缓冲区
	int in_point; 			// 生产者当前数据下标
	int out_point; 			// 消费者当前数据下标
	pthread_mutex_t mutex_buff; 	// 保护数据缓冲区的互斥量
	pthread_cond_t  queue_full; 	// 缓冲区满的条件变量
	pthread_cond_t  queue_empty; 	// 缓冲区空的条件变量
};

// 数据缓冲区
struct queue_buff que_buff;

// 是否退出所有线程
// 忘记这里的 volatile 是很悲剧的...是调试了半小时的悲剧...
volatile int is_stop = 0;

// 生产者线程函数
void *thread_producer_func(void *args)
{
	// 当前生产者 ID
	int num = (int)args;

	while (1) {
		pthread_mutex_lock(&(que_buff.mutex_buff));

		// 如果缓冲区满，则等待
		while ((que_buff.in_point + 1) % QUEUE_LENGTH == que_buff.out_point && is_stop == 0) {
			pthread_cond_wait(&(que_buff.queue_empty), &(que_buff.mutex_buff));
		}

		if (is_stop == 1) {
			pthread_mutex_unlock(&(que_buff.mutex_buff));
			pthread_exit(0);
		}

		printf("生产者 %d 在 %d 位置增加数据\n", num, que_buff.in_point);

		// 缓冲区增加一项当前生产者 ID 命名的数据
		que_buff.buff[que_buff.in_point] = num;

		que_buff.in_point = (que_buff.in_point + 1) % QUEUE_LENGTH;

		// 缓冲区满则通知消费者可以取数据了
		if ((que_buff.in_point + 1) % QUEUE_LENGTH == que_buff.out_point) {
			pthread_cond_broadcast(&(que_buff.queue_full));
		}

		pthread_mutex_unlock(&(que_buff.mutex_buff));

		// 稍微休眠下，较容易产生竞争
		usleep(200000);
	}
}

// 消费者线程函数
void *thread_consumer_func(void *args)
{
	// 当前消费者 ID
	int num = (int)args;
	int data;

	while (1) {
		pthread_mutex_lock(&(que_buff.mutex_buff));

		// 如果缓冲区空，则等待
		while (que_buff.out_point == que_buff.in_point && is_stop == 0) {
			pthread_cond_wait(&(que_buff.queue_full), &(que_buff.mutex_buff));
		}

		// 如果设置退出标记且队列空了则退出
		if (is_stop == 1 && que_buff.out_point == que_buff.in_point) {
			pthread_mutex_unlock(&(que_buff.mutex_buff));
			pthread_exit(0);
		}

		printf("\t\t\t\t\t消费者 %d 在 %d 位置取出数据\n", num, que_buff.out_point);

		// 缓冲区取出一个数据
		data = que_buff.buff[que_buff.out_point];

		que_buff.out_point = (que_buff.out_point + 1) % QUEUE_LENGTH;

		// 缓冲区空则通知生产者可以添加数据了
		if (que_buff.out_point == que_buff.in_point) {
			pthread_cond_broadcast(&(que_buff.queue_empty));
		}

		pthread_mutex_unlock(&(que_buff.mutex_buff));

		// 稍微休眠下，较容易产生竞争
		usleep(200000);
	}
}

int main(int argc, char *argv[])
{
	pthread_t thread_producer[10] = {0};
	pthread_t thread_consumer[10] = {0};

	// 初始化所有的条件变量和互斥锁，简单起见不对API调用进行错误处理
	pthread_mutex_init(&(que_buff.mutex_buff), NULL);
	pthread_cond_init(&(que_buff.queue_full), NULL);
	pthread_cond_init(&(que_buff.queue_empty), NULL);

	int i;
	// 创建 4 个生产者
	for (i = 0; i < 4; i++) {
		pthread_create(&thread_producer[i], NULL, thread_producer_func, (void *)i);
	}

	// 创建 4 个消费者
	for (i = 0; i < 4; i++) {
		pthread_create(&thread_consumer[i], NULL, thread_consumer_func, (void *)i);
	}

	// 等待 1 s 后通知线程们结束
	sleep(1);
	is_stop = 1;
	
	// 唤醒所有阻塞的线程结束
	pthread_cond_broadcast(&(que_buff.queue_empty));
	pthread_cond_broadcast(&(que_buff.queue_full));

	// 等待所有线程退出
	for (i = 0; i < 4; i++) {
		pthread_join(thread_producer[i], NULL);
		pthread_join(thread_consumer[i], NULL);
	}

	// 销毁互斥量和条件变量，当然，本程序非必须...
	pthread_mutex_destroy(&(que_buff.mutex_buff));
	pthread_cond_destroy(&(que_buff.queue_empty));
	pthread_cond_destroy(&(que_buff.queue_full));

	return EXIT_SUCCESS;
}

