/*
 * =====================================================================================
 *
 *       Filename:  buddy.c
 *
 *    Description:  伙伴算法
 *
 *        Version:  1.0
 *        Created:  2013年11月22日 09时58分19秒
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

// 由父节点下标求左孩子下标
#define LEFT_LEAF(index) ((index) * 2 + 1)

// 由父节点下标求右孩子下标
#define RIGHT_LEAF(index) ((index) * 2 + 2)

// 由孩子节点计算父节点下标
#define PARENT(index) (((index) + 1) / 2 - 1)

// 判断一个数是否是 2 的幂
#define IS_POWER_OF_2(x) (!((x) & ((x) - 1)))

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define ALLOC malloc
#define FREE free

struct buddy {
	unsigned int size;
	unsigned int longest[1];
};

struct buddy *buddy_new(int size);
void buddy_destroy(struct buddy* self);
int buddy_alloc(struct buddy *self, int size);
void buddy_free(struct buddy *self, int offset);
int buddy_size(struct buddy *self, int offset);

struct buddy *buddy_new(int size)
{
	struct buddy *self;
	unsigned int node_size;
	int i;

	if (size < 1 || !IS_POWER_OF_2(size)) {
		return NULL;
	}

	self = (struct buddy *)ALLOC(2 * size * sizeof(unsigned int));
	self->size = size;
	node_size = size * 2;

	for (i = 0; i < 2 * size - 1; i++) {
		if (IS_POWER_OF_2(i + 1)) {
			node_size / = 2;
			self->longest[i] = node_size;
		}
	}
	
	return self;
}

void buddy_destroy(struct buddy *self)
{
	FREE(self);
}

static unsigned fixsize(unsigned size)
{
	size |= size >> 1;
	size |= size >> 2;
	size |= size >> 4;
	size |= size >> 8;
	size |= size >> 16;

	return size+1;
}

int buddy_alloc(struct buddy *self, int size)
{
	unsigned int index = 0;
	unsigned int node_size = 0;
	unsigned int offset = 0;

	if (!IS_POWER_OF_2(size)) {
		size = fixsize(size);
	}

	if (self->longest[index] < size) {
		return -1;
	}

	for (node_size = self->size; node_size != size; node_size /= 2) {
		if (self->longest[LEFT_LEAF(index)] >= size) {
			index = LEFT_LEAF(index);
		} else {
			index = RIGHT_LEAF(index);
		}
	}

	self->longest[index] = 0;
	offset = (index + 1) * node_size - self->size;

	while (index) {
		index = PARENT(index);
		self->longest[index] = MAX(self->longest[LEFT_LEAF(index)], self->longest[RIGHT_LEAF(index)]);
	}

	return offset;
}

void buddy_free(struct buddy *self, int offset)
{
	unsigned int index = 0;
	unsigned int node_size = 0;
	unsigned int left_longest, right_longest;

	node_size = 1;
	
	for (index = offset + self->size - 1; self->longest[index]; index = PARENT(index)) {
		node_size *= 2;
		if (index == 0) {
			return;
		}
	}

	self->longest[index] = node_size;

	while (index) {
		index = PARENT(index);
		node_size *= 2;
		left_longest = self->longest[LEFT_LEAF(index)];
		right_longest = self->longest[RIGHT_LEAF(index)];

		if (left_longest + right_longest == node_size) {
			self->longest[index] = node_size;
		} else {
			self->longest[index] = MAX(left_longest, right_longest);
		}
	}
}

int main(int argc, char *argv[])
{


	return EXIT_SUCCESS;
}

