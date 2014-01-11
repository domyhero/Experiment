/*
 * =====================================================================================
 *
 *       Filename:  backtrace.c
 *
 *    Description:  打印函数调用栈
 *
 *    		    编译方法：gcc backtrace.c -rdynamic
 *
 *        Version:  1.0
 *        Created:  2013年12月26日 10时50分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

/* 打印调用栈的最大深度 */
#define DUMP_STACK_DEPTH_MAX 16

/* 打印调用栈函数 */
void dump_trace()
{
	void *stack_trace[DUMP_STACK_DEPTH_MAX] = {0};
	char **stack_strings = NULL;
	int stack_depth = 0;
	int i = 0;

	/* 获取栈中各层调用函数地址 */
	stack_depth = backtrace(stack_trace, DUMP_STACK_DEPTH_MAX);

	/* 查找符号表将函数调用地址转换为函数名称 */
	stack_strings = (char **)backtrace_symbols(stack_trace, stack_depth);
	if (!stack_strings) {
		printf(" Memory is not enough while dump Stack Trace! \r\n");
		return;
	}

	/* 打印调用栈 */
	printf(" Stack Trace: \r\n");
	for (i = 0; i < stack_depth; ++i) {
		printf(" [%d] %s \r\n", i, stack_strings[i]);
	}

	/* 获取函数名称时申请的内存需要自行释放 */
	free(stack_strings);
	stack_strings = NULL;
}

/* 测试函数 2 */
void test_meloner()
{
	dump_trace();
}

/* 测试函数 1 */
void test_hutaow()
{
	test_meloner();
}

int main(int argc, char *argv[])
{
	test_hutaow();
	return 0;
}

