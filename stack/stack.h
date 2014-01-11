/*
 * =====================================================================================
 *
 *       Filename:  stack.h
 *
 *    Description:  一个栈的实现
 *
 *        Version:  1.0
 *        Created:  2013年07月23日 09时31分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef ARRAY_H_
#define ARRAY_H_

typedef
struct tagStack
{
	void *elem_addr; 	// 元素指针
	int size_elem; 		// 元素大小
	int log_elem; 		// 当前已有的元素个数
	int count_elem; 	// 栈总大小
	void (*elem_free)(void *); //释放用户数据 	
}Stack;

// 栈初始化操作
void stack_init(Stack *s, int length, int size_elem, void (*elem_free)(void *));

// 栈销毁操作
void stack_dis(Stack *s);

// 压栈操作
void stack_push(Stack *s, void *elem);

// 弹栈操作
void stack_pop(Stack *s, void *elem);

// 取栈顶
void stack_gettop(Stack *s, void *elem);

// 判断栈是否为空
int stack_is_empty(Stack *s);

#endif  // ARRAY_H_
