#pragma once
#include <iostream>　
#include <string>
#include <fstream>  
#include "Word.h"
class TreeNode {
public:
	Word pow;//节点的权重,即Word类的数据
	int child_num;//孩子个数
	TreeNode* parent;//父亲节点
	TreeNode** child;//孩子数组,每一个存储一个孩子指针
	//构造函数
	TreeNode();
	TreeNode(Word pow, int child_num);
};

