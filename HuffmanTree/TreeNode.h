#pragma once
#include <iostream>��
#include <string>
#include <fstream>  
#include "Word.h"
class TreeNode {
public:
	Word pow;//�ڵ��Ȩ��,��Word�������
	int child_num;//���Ӹ���
	TreeNode* parent;//���׽ڵ�
	TreeNode** child;//��������,ÿһ���洢һ������ָ��
	//���캯��
	TreeNode();
	TreeNode(Word pow, int child_num);
};

