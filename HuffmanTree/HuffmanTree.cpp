#include "HuffmanTree.h"
TreeNode zero_node;
TreeNode* null_node = &zero_node;
int Huffman_Tree_Depth;
extern int child__num;
HuffmanTree::HuffmanTree() {
	root = NULL;
	child_num = child__num;
}
//构造Huffman树
HuffmanTree::HuffmanTree(Word* word_array, int size, const Word& invalid) {
	//开始构造
	assert(word_array);
	child_num = child__num;
	Heap minheap;
	for (int i = 0; i < size; i++) {
		if (word_array[i] != invalid) {
			minheap.Push(new TreeNode(word_array[i], child_num));
		}
	}
	//增加虚节点来补满Huffman树
	int n = minheap.Get_Size();
	if ((n - 1) % (child_num - 1) != 0) {
		int m = child_num - ((n - 1) % (child_num - 1)) - 1;
		for (int i = 0; i < m; ++i) {
			minheap.Push(null_node);
		}
	}
	while (minheap.Get_Size() > 1)
	{
		TreeNode* parent = new TreeNode();
		for (int j = 0; j < child_num; j++) {
			TreeNode* node = new TreeNode();
			node = minheap.Get_Top();
			minheap.Pop();
			parent->pow.count = parent->pow.count + node->pow.count;
			(parent->child)[j] = node;
			node->parent = parent;
		}
		minheap.Push(parent);
	}
	root = minheap.Get_Top();
}

void HuffmanTree::ShowTree(TreeNode* node) {
	if (node == null_node) {
		return;
	}
	else {
		int flag = 0;//判断是否到了最后一层
		int num = 0;
		Huffman_Tree_Depth = GetDepth(root);
		int depth = 1;
		cout << "Huffman_Tree_Depth = " << Huffman_Tree_Depth << endl;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			if (depth == Huffman_Tree_Depth + 1) {
				break;
			}
			TreeNode* front = new TreeNode();
			front = q.front();
			cout << front->pow << "   ";
			q.pop();
			num++;
			if (num == pow(child_num, depth - 1)) {
				cout << endl;
				num = 0;
				depth++;
			}
			for (int i = 0; i < child_num; i++) {
				q.push((front->child)[i]);
			}
		}
		cout << endl;
	}
}
int HuffmanTree::GetDepth(TreeNode* node) {
	if (node == null_node) {
		return 0;
	}
	else {
		int temp_depth = 0;
		int max_depth = 0;
		for (int i = 0; i < child_num; i++) {
			int temp = GetDepth((node->child)[i]);
			if (temp > max_depth) {
				max_depth = temp;
			}
		}
		temp_depth = max_depth + 1;
		return temp_depth;
	}
}