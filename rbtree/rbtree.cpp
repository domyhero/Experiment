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

enum color_t {
	black,
	red
};

template <typename Type>
struct RBNode {
	Type key;
	RBNode *left;
	RBNode *right;
	RBNode *parent;
	color_t color;
};

template <typename Type>
class RBTree {
public:
	RBTree();
	~RBTree();

	insert(T key);
	remove(T key);

private:
	RBNode<Type> root;
};

template <typename Type>
RBTree<Type>::RBTree()
{
	
}

template <typename Type>
RBTree<Type>::~RBTree()
{
	// TODO
}

#endif 	// RBTREE_H_
