#pragma once
#include <iostream>　
#include <string>
#include <fstream>  
#include "TreeNode.h"
#include "Word.h"
#include "Heap.h"
#include<queue>
using namespace std;
class HuffmanTree {
public:
	TreeNode* root;//Huffman树的根节点
	int child_num;
	HuffmanTree();//默认构造函数
	HuffmanTree(Word* word_array, int size, const Word& invalid);
	void ShowTree(TreeNode* node);//展示Huffman树
	int GetDepth(TreeNode* node);
};

