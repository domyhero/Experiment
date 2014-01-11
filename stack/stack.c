/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  一个栈的实现
 *
 *        Version:  1.0
 *        Created:  2013年07月23日 09时38分54秒
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

#include "stack.h"

// 栈初始化操作
void stack_init(Stack *s, int length, int size_elem, void (*elem_free)(void *))
{
	s->elem_addr = malloc(length * size_elem);
	s->size_elem = size_elem;
	s->log_elem = 0;
	s->count_elem = length;
	s->elem_free = elem_free;
}

// 栈销毁操作
void stack_dis(Stack *s)
{
	int i;

	if (s->elem_free != NULL) {
		for (i = 0; i < s->log_elem; i++) {
			char *addr = (char *)s->elem_addr + i * s->size_elem;
			s->elem_free(addr);
		} 
	}
	
	free(s->elem_addr);
}

// 调整栈大小
static void resize(Stack *s, int length)
{
	assert(length > s->count_elem);
	s->elem_addr = realloc(s->elem_addr, length * s->size_elem);
	s->count_elem = length;
	assert(s->elem_addr != NULL);
}

// 压栈操作
void stack_push(Stack *s, void *elem)
{
	if (s->count_elem == s->log_elem) {
		resize(s, s->count_elem * 2);
	}
	
	char *addr = (char *)s->elem_addr + s->size_elem * s->log_elem;

	memcpy(addr, elem, s->size_elem);
	s->log_elem++;
}

// 弹栈操作
void stack_pop(Stack *s, void *elem)
{
	assert(s->log_elem > 0);
	char *addr = (char *)s->elem_addr + s->size_elem * (s->log_elem - 1);

	memcpy(elem, addr, s->size_elem);
	s->log_elem--;
}

// 取栈顶
void stack_gettop(Stack *s, void *elem)
{
	assert(s->log_elem > 0);
	char *addr = (char *)s->elem_addr + s->size_elem * (s->log_elem - 1);

	memcpy(elem, addr, s->size_elem);
}

// 判断栈是否为空
int stack_is_empty(Stack *s)
{
	return (s->log_elem == 0) ? 1 : 0;
}

