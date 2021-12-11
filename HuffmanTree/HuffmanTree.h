#pragma once
#include <iostream>��
#include <string>
#include <fstream>  
#include "TreeNode.h"
#include "Word.h"
#include "Heap.h"
#include<queue>
using namespace std;
class HuffmanTree {
public:
	TreeNode* root;//Huffman���ĸ��ڵ�
	int child_num;
	HuffmanTree();//Ĭ�Ϲ��캯��
	HuffmanTree(Word* word_array, int size, const Word& invalid);
	void ShowTree(TreeNode* node);//չʾHuffman��
	int GetDepth(TreeNode* node);
};

