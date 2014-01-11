/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月23日 10时22分20秒
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

#include "stack.h"

int main(int argc, char *argv[])
{
	Stack stk_int;
	Stack stk_double;

	int a = 0;
	int b;

	double da = 0.0;
	double db;

	stack_init(&stk_int, 1, sizeof(int), NULL);
	stack_init(&stk_double, 1, sizeof(double), NULL);

	stack_push(&stk_int, &a);
	a++;
	stack_push(&stk_int, &a);
	a++;
	stack_push(&stk_int, &a);
	a++;
	stack_push(&stk_int, &a);
	a++;
	stack_push(&stk_int, &a);
	a++;
	
	stack_push(&stk_double, &da);
	da++;
	stack_push(&stk_double, &da);
	da++;
	stack_push(&stk_double, &da);
	da++;
	stack_push(&stk_double, &da);
	da++;
	stack_push(&stk_double, &da);
	da++;

	stack_pop(&stk_int, &b);
	printf("%d\n", b);
	stack_pop(&stk_int, &b);
	printf("%d\n", b);
	stack_pop(&stk_int, &b);
	printf("%d\n", b);
	stack_pop(&stk_int, &b);
	printf("%d\n", b);
	stack_pop(&stk_int, &b);
	printf("%d\n", b);

	stack_pop(&stk_double, &db);
	printf("%.2f\n", db);
	stack_pop(&stk_double, &db);
	printf("%.2f\n", db);
	stack_pop(&stk_double, &db);
	printf("%.2f\n", db);
	stack_pop(&stk_double, &db);
	printf("%.2f\n", db);
	stack_pop(&stk_double, &db);
	printf("%.2f\n", db);

	stack_dis(&stk_int);
	stack_dis(&stk_double);

	return EXIT_SUCCESS;
}

