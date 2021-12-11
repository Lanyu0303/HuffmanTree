#include "Heap.h"
extern int child__num;
extern TreeNode* null_node;
Heap::Heap() {
	child_num = child__num;
	size = 0;
	node_p_array = new TreeNode * [256];
	memset(node_p_array, NULL, sizeof(node_p_array));
}

//获取堆的大小
int Heap::Get_Size() {
	return size;
}
//获取头元素
TreeNode* Heap::Get_Top() {
	if (size == 0) {
		cout << "heap为空！(Get_Top)" << endl;
		return null_node;
	}
	Sort();
	return node_p_array[0];
}

void Heap::Push(TreeNode* new_node) {
	node_p_array[size] = new_node;
	size++;
	Sort();
}
//删除头
void Heap::Pop() {
	if (size == 0) {
		cout << "heap为空！(Pop)" << endl;
		return;
	}
	else {
		Sort();
		for (int i = 0; i < size - 1; i++) {
			node_p_array[i] = node_p_array[i + 1];
		}
		size--;
		return;
	}
}
//展示堆
void Heap::Show_Heap() {
	int empty_size = 0;//空节点的个数
	for (int i = 0; i < size; i++) {
		if (node_p_array[i]->pow.count != 0) {
			cout << node_p_array[i]->pow << "   ";
		}
		else {
			empty_size++;
		}
	}
	cout << endl;
	cout << "还有" << empty_size << "个空节点" << endl;
}
//从小到大排序
void Heap::Sort() {
	int i, j;
	TreeNode* temp;
	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - i - 1; j++) {
			if (node_p_array[j]->pow > node_p_array[j + 1]->pow) {
				temp = node_p_array[j + 1];
				node_p_array[j + 1] = node_p_array[j];
				node_p_array[j] = temp;
			}
		}
	}
}
//让数组内的节点数量满足满k叉树的条件
void Heap::Be_Full() {
	/*
	double depth = 0.0;
	int true_depth = 0;
	int true_size = 0;
	depth = log((child_num - 1.0) * size + 1.0 ) / log(child_num);
	if (depth == floor(depth)) {
		return;
	}
	true_depth = ceil(depth);
	true_size = (pow(child_num, true_depth) - 1.0) / (child_num - 1.0);
	for (int i = size; i < true_size; i++) {
		Push(null_node);
	}
	Sort();//最后排序
	*/
}