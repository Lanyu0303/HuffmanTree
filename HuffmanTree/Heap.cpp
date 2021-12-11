#include "Heap.h"
extern int child__num;
extern TreeNode* null_node;
Heap::Heap() {
	child_num = child__num;
	size = 0;
	node_p_array = new TreeNode * [256];
	memset(node_p_array, NULL, sizeof(node_p_array));
}

//��ȡ�ѵĴ�С
int Heap::Get_Size() {
	return size;
}
//��ȡͷԪ��
TreeNode* Heap::Get_Top() {
	if (size == 0) {
		cout << "heapΪ�գ�(Get_Top)" << endl;
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
//ɾ��ͷ
void Heap::Pop() {
	if (size == 0) {
		cout << "heapΪ�գ�(Pop)" << endl;
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
//չʾ��
void Heap::Show_Heap() {
	int empty_size = 0;//�սڵ�ĸ���
	for (int i = 0; i < size; i++) {
		if (node_p_array[i]->pow.count != 0) {
			cout << node_p_array[i]->pow << "   ";
		}
		else {
			empty_size++;
		}
	}
	cout << endl;
	cout << "����" << empty_size << "���սڵ�" << endl;
}
//��С��������
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
//�������ڵĽڵ�����������k����������
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
	Sort();//�������
	*/
}