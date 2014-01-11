/*
 * =====================================================================================
 *
 *       Filename:  pass.c
 *
 *    Description:  密码验证
 *
 *        Version:  1.0
 *        Created:  2013年07月19日 08时33分44秒
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

int main(int argc, char *argv[])
{
	char *passwd = "passed word";
	char  pass_input[32];

	scanf("%31[^\n]", pass_input);

	if (strcmp(passwd, pass_input) == 0) {
		printf("Welcome!\n");
	} else {
		printf("Password Error!\n");
	}

	return EXIT_SUCCESS;
}

