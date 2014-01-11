/*
 * =====================================================================================
 *
 *       Filename:  libc_version.c
 *
 *    Description:  获取 libc 的版本
 *
 *        Version:  1.0
 *        Created:  2013年07月18日 20时37分34秒
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
#include <gnu/libc-version.h>

int main(int argc, char *argv[])
{
	printf("%s\n", gnu_get_libc_version());

	return EXIT_SUCCESS;
}

