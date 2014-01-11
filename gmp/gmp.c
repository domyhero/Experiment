/*
 * =====================================================================================
 *
 *       Filename:  gmp.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月09日 15时18分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <gmp.h>

int main(int argc, char *argv[])
{
	mpz_t n;

	if (argc < 2) {
		printf("Usage: %s n\n", argv[0]);
		return -1;
	}

	/* 初始化10进制大整数n，并且把命令行的第一个参数赋值给它*/
	mpz_init(n);
	if (mpz_set_str(n, argv[1], 10) != 0) {
		return -1;
	}

	/* 打印大整数n的值 */
	printf ("n = ");
	mpz_out_str(stdout, 10, n);
	printf ("\n");

	/* 计算(n + 1)的平方 */
	mpz_add_ui(n, n, 1);
	mpz_mul(n, n, n);

	/* 打印(n + 1)平方的值 */
	printf ("(n + 1) ^ 2 = ");
	mpz_out_str(stdout, 10, n);
	printf("\n");

	/* 清除和释放大整数n */
	mpz_clear(n);

	return 0;
}

