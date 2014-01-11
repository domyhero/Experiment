/*
 * =====================================================================================
 *
 *       Filename:  qsort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月21日 18时32分33秒
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

#define N 10

struct student {
	char id[10];
	int age;
	// ... ...
};

int cmp(const void *elem1, const void *elem2)
{
	struct student *stu1 = (struct student *)elem1;
	struct student *stu2 = (struct student *)elem2;

	return strcmp(stu1->id, stu2->id);
}

int main(int argc, char *argv[])
{
	struct student stu[N] = {
		{"00009", 12},
		{"00001", 13},
		{"00005", 12},
		{"00008", 11},
		{"00004", 15},
		{"00006", 16},
		{"00003", 14},
		{"00007", 12},
		{"00002", 15},
		{"00000", 16}
	};

	qsort(stu, N, sizeof(struct student), cmp);

	int i;
	for (i = 0; i < N; i++) {
		printf("%s %d\n", stu[i].id, stu[i].age);
	}

	return EXIT_SUCCESS;
}

