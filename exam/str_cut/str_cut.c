/*
 * =====================================================================================
 *
 *       Filename:  str_cut.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月15日 10时54分11秒
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

int compare_int(const void *elem1, const void *elem2)
{
	return (*(int *)elem1 - *(int *)elem2);
}

void str_cut(const char *str_num)
{
	int  n = 0;
	int  i = 0;
	int  num[20] = {0};
	char num_tmp[11];
	char *p_tmp = num_tmp;
	const char *p_num = str_num;

	while (*p_num != '\0') {
		p_tmp = num_tmp;
		while (*p_num != '5') {
			*p_tmp++ = *p_num++;
		}
		*p_tmp = '\0';
		num[n++] = atoi(num_tmp);
		p_num++;
	}
	
	qsort(num, n, sizeof(int), compare_int);

	for (i = 0; i < n; i++) {
		printf("%d ", num[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	str_cut("0051231232050775225");

	return EXIT_SUCCESS;
}

