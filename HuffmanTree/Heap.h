#pragma once
#include <iostream>　
#include <string>
#include <fstream>  
#include "Word.h"
#include "TreeNode.h"
#include<vector>
class Heap {
public:
	int child_num;
	int size;
	TreeNode** node_p_array;
	Heap();//默认构造函数
	int Get_Size();
	void Sort();//从小到大排序
	TreeNode* Get_Top();
	void Push(TreeNode* new_node);
	void Pop();//删除头
	void Show_Heap();//展示堆
	void Be_Full();//让数组内的节点数量满足满k叉树的条件
};

