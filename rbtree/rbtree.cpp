// =====================================================================================
// 
//       Filename:  rbtree.hpp
//
//    Description:  红黑树的实现
//
//        Version:  1.0
//        Created:  2014年06月23日 16时50分30秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>

class RBTree {
private:
	enum color_t {red, black};

	struct RBNode {
		int key;
		RBNode *left;
		RBNode *right;
		RBNode *parent;
		color_t color;
	};
	
	RBNode root_;
	int count_;

public:
	RBTree(int key);
	~RBTree();

	bool find(int key);
	void insert(int key);
	bool remove(int key);
	int count() const;
	bool empty();

private:
	void destory(RBNode *node);
};

RBTree::RBTree(int key) : count_(1)
{
	root_.key = key;
	root_.left = NULL;
	root_.right = NULL;
	root_.parent = NULL;
	root_.color = black;
}

RBTree::~RBTree()
{
	destory(root_.left);
	destory(root_.right);
}

bool RBTree::find(int key)
{
	RBNode *node = &root_;

	while (node) {
		if (key < node->key) {
			node = node->left;
		} else if (key > node->key) {
			node = node->right;
		} else {
			return true;
		}
	}

	return false;
}

void RBTree::insert(int key)
{
	
}

bool RBTree::remove(int key)
{
	return true;
}

int RBTree::count() const
{
	return count_;
}

bool RBTree::empty()
{
	return (count_ == 0);
}

void RBTree::destory(RBNode *node)
{
	if (node) {
		destory(node->left);
		destory(node->right);
		delete node;
	}
}

int main(int argc, char *argv[])
{
	RBTree rbtree(0);

	return 0;
}

#endif 	// RBTREE_H_
