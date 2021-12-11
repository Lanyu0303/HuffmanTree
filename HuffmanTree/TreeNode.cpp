#include "TreeNode.h"
extern int child__num;
extern TreeNode* null_node;
//默认构造函数
TreeNode::TreeNode() {
	this->pow = Word();
	child_num = child__num;
	parent = null_node;
	child = new TreeNode * [child_num];
	for (int i = 0; i < child_num; i++) {
		child[i] = null_node;
		child[i]->child = new TreeNode * [child_num];
		for (int j = 0; j < child_num; j++) {
			(child[i]->child)[j] = null_node;
		}
	}
}
//构造函数
TreeNode::TreeNode(Word pow, int child_num) {
	this->pow = pow;
	this->child_num = child_num;
	parent = null_node;
	child = new TreeNode * [child_num];
	for (int i = 0; i < child_num; i++) {
		child[i] = null_node;
		child[i]->child = new TreeNode * [child_num];
		for (int j = 0; j < child_num; j++) {
			(child[i]->child)[j] = null_node;
		}
	}
}