#pragma once
#include <iostream>��
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
	Heap();//Ĭ�Ϲ��캯��
	int Get_Size();
	void Sort();//��С��������
	TreeNode* Get_Top();
	void Push(TreeNode* new_node);
	void Pop();//ɾ��ͷ
	void Show_Heap();//չʾ��
	void Be_Full();//�������ڵĽڵ�����������k����������
};

