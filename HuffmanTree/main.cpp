#define _CRT_SECURE_NO_WARNINGS
#include <iostream>��
#include <string>
#include <fstream>  
#include "TreeNode.h"
#include "HuffmanTree.h"
#include "Heap.h"
#include "Word.h"

using namespace std;
void print_menu();//����˵�
void Compress(char* path);//ѹ��
void UnCompress(char* path);//��ѹ��
void Create_HuffmanCode(TreeNode* temp, string code);//����Huffman����
string Ten_To_Two(int num);//10����ת2�����ַ���
int Two_To_Ten(string num);//2�����ַ���ת10������
string Get_Line(FILE* filename);//�ļ���ȡһ��
bool isNode(TreeNode* node);//�Ƿ���Ҷ�ӽڵ�

//Ҫ���浽�ļ������Ϣ

struct info {
	unsigned char ch;
	long long count;
};
int child__num;
int word_num;
Word information[256];
extern TreeNode* null_node;
int code_length;//Huffman����ĳ���
std::map<string, unsigned char> huffman_map;
int main() {
	int choice = 0;
	int temp_child_num = 2;
	char file_path[] = "";
	word_num = 0;
	//��ʼ��
	for (int i = 0; i < 256; i++) {
		information[i].ch = i;
		information[i].count = 0;
	}
	//��ʼ����ѡ��
	while (true) {
		print_menu();
		cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "�������ļ���ַ:" << endl;
			cin >> file_path;
			std::cout << "������ĵ�ַΪ��" << file_path << endl;
			std::cout << "������Ϊ��Ԫ��:" << endl;
			cin >> child__num;
			std::cout << "������ĺ�����Ϊ��" << child__num << endl;
			code_length = ceil(log(child__num * 1.0) / log(2.0));//��ȡHuffman���볤��
			Compress(file_path);
			break;
		case 2:
			std::cout << "�������ļ���ַ:" << endl;
			cin >> file_path;
			std::cout << "������ĵ�ַΪ��" << file_path << endl;
			UnCompress(file_path);
			break;
		case 3:
			std::cout << "�������˳�" << endl;
			return 0;
		default:
			std::cout << "�������ѡ�����������" << endl;
			break;
		}
	}
	return 0;
}
//����˵�
void print_menu() {
	std::cout << "--------�˵�----------" << endl;
	std::cout << "|1.ѹ���ļ�" << endl;
	std::cout << "|2.��ѹ�ļ�" << endl;
	std::cout << "|3.�˳�" << endl;
	std::cout << "���������ѡ��:";
}
//ѹ��
void Compress(char* path) {
	//ͳ���ַ����ֵĴ���
	fstream file;
	file.open(path, ifstream::in | ios::binary);
	if (!file) {
		std::cout << "�ļ�Ϊ�գ�����" << endl;
		return;
	}
	unsigned char temp_ch;
	long long temp_count = 0;
	while (file.read((char*)&temp_ch, sizeof(temp_ch))) {
		information[temp_ch].count++;//���ַ���Ӧ�Ĵ���
		temp_count++;
	}
	Word invalid;
	invalid.count = 0;
	//����ļ���Ϣ
	for (int i = 0; i < 256; i++) {
		if (information[i] != invalid) {
			std::cout << (int)information[i].ch << ":" << information[i].count << "   ";
			word_num++;
		}
	}
	std::cout << endl;
	//����Huffman��
	HuffmanTree tree(information, 256, invalid);
	TreeNode* root = tree.root;//��ȡ���ڵ�
	//���Huffman��
	std::cout << "Huffman��Ϊ��" << std::endl;
	tree.ShowTree(tree.root);
	//��ȡHuffman����
	string code = "";
	Create_HuffmanCode(root, code);
	//����ļ���Ϣ
	for (int i = 0; i < 256; i++) {
		if (information[i] != invalid) {
			std::cout << (int)information[i].ch << ":" << information[i].count << ":" << information[i].huff_code << "   ";
		}
	}
	//��ʼѹ��
	file.close();
	file.open(path, ifstream::in | ios::binary);//���´�Դ�ļ�
	char final[7] = ".my";
	strcat(path, final);
	std::cout << "�����ļ���ַΪ��" << path << endl;
	fstream compress_file(path, ofstream::app | ios::binary | ofstream::out);
	//��д��������Ϣ
	string child_inf = to_string(child__num);//������ӽڵ�����
	compress_file << child_inf << '\n';
	compress_file << word_num << '\n';//�����ĸ����
	for (int i = 0; i < 256; i++) {
		if (information[i] != invalid) {
			compress_file.write((char*)&information[i].ch, sizeof(information[i].ch));
			compress_file << ":" << information[i].count << '\n';
		}
	}
	//��ѹ���ļ���д��Huffman����
	unsigned char ch1;//��Դ�ļ�����
	file.read((char*)&ch1, sizeof(ch1));
	unsigned char value = 0;
	int pos = 0;
	while (ch1 != EOF) {
		if (file.eof())
			break;
		string& code = information[ch1].huff_code;//ÿ���ַ���Huffman����
		for (size_t i = 0; i < code.size(); i++) {//һ��һ������λ�����з�
			value <<= 1;
			//������һλ�����codeΪ1�ͽ�������Ĵ��룬�ѵ�һλ��Ϊ1��Ϊ0�Ͳ�����
			if (code[i] == '1') {//�õ������Ƶ�1
				value |= 1;//�����ұ�Ϊ0��λ�ñ�Ϊ1��������д��1.
			}
			if (++pos == 8) {//��8λд���ļ�
				compress_file.write((char*)&value, sizeof(value));//��valueд��ȥ��������8��λ����HuffmanCode
				value = 0;//���ã�ѭ��д
				pos = 0;
			}
		}
		file.read((char*)&ch1, sizeof(ch1));
	}
	if (pos) {//���һ�����벻��8��λ
		value = value << (8 - pos);//����һ���ֽڣ������油0��д��fin�ļ�
		compress_file.write((char*)&value, sizeof(value));
	}
	//�ر��ļ�
	file.close();
	compress_file.close();
}
//��ѹ��
void UnCompress(char* path) {
	string soure_file_name = path;
	int pos_count = soure_file_name.find_last_of('.');//�ҵ����һ����
	string UnCompress_file_name = soure_file_name.substr(0, pos_count);
	std::cout << "��ѹ���ļ���ַΪ:" << UnCompress_file_name << endl;
	//������ѹ�ļ�
	fstream UnCompress_file(UnCompress_file_name, ofstream::app | ios::binary | ofstream::out);//�򿪽�ѹ�ļ�
	fstream Compress_file;
	Compress_file.open(soure_file_name, ifstream::in | ios::binary);//��ѹ�������ļ�
	string temp_string = "";
	getline(Compress_file, temp_string);//��ȡһ��
	child__num = atoi(temp_string.c_str());//��ȡchild__num
	getline(Compress_file, temp_string);//��ȡһ��
	word_num = atoi(temp_string.c_str());//��ȡ��ĸ����
	code_length = ceil(log(child__num * 1.0) / log(2.0));//��ȡHuffman���볤��
	std::cout << "��ȡ��child__num = " << child__num << endl;
	std::cout << "code_length = " << code_length << endl;
	unsigned char tempch;
	unsigned char uselessch;
	string temp_num = "";
	long long tempcount = 0;
	int inflag = 0;//��ȡ������Ϣ�Ƿ����
	int temp_word_num = 0;
	while (temp_word_num != word_num) {
		Compress_file.read((char*)&tempch, sizeof(tempch));
		temp_word_num++;
		Compress_file.read((char*)&uselessch, sizeof(uselessch));//��ȡð��
		Compress_file >> tempcount;
		information[tempch].count = tempcount;
		Compress_file.read((char*)&uselessch, sizeof(uselessch));//��ȡ�س�
	}
	//Compress_file.read((char*)&uselessch, sizeof(uselessch));//��ȡ�س�
	//�����ȡ����Ϣ,����ȡ�ַ�����
	long long charCount = 0;//�ַ�����
	std::cout << "��ȡ���ַ�Ϊ��" << endl;
	for (int i = 0; i < 256; i++) {
		if (information[i].count != 0) {
			std::cout << (int)information[i].ch << ":" << information[i].count << "  ";
			charCount += information[i].count;
		}
	}
	std::cout << endl;
	//����Huffman��
	Word invalid;
	invalid.count = 0;
	HuffmanTree tree(information, 256, invalid);
	TreeNode* root = tree.root;//��ȡ���ڵ�
	TreeNode* tempNode = root;//��ʱ�Ľڵ�ָ��
	//���Huffman��
	std::cout << "Huffman��Ϊ��" << endl;
	tree.ShowTree(tree.root);
	//��ʼ��ѹ
	string tempCode = "";//��ʱ��Huffman�ڵ�
	unsigned char tempChar;
	Compress_file.read((char*)&tempChar, sizeof(tempChar));
	int tempPos = 8;
	int tempBit = 0;
	clock_t startTime, endTime;//���Խ�ѹʱ��
	startTime = clock();//��ʼ
	std::cout << "���ڽ�ѹ�������ĵȴ�" << std::endl;
	//std::cout << "����ļ�Ϊ��" << endl;
	while (true) {
		//�õ�һλHuffmanCode�Ķ�����
		for (int i = 1; i <= code_length; i++) {
			if (tempPos == 0) {
				Compress_file.read((char*)&tempChar, sizeof(tempChar));
				tempPos = 8;
			}
			tempPos--;
			tempBit = (tempChar >> tempPos) & 1;
			tempCode += to_string(tempBit);
		}
		//��������תΪ10����
		tempNode = tempNode->child[Two_To_Ten(tempCode)];//�ƶ�һ��
		tempCode = "";//����
		if (isNode(tempNode) == true) {//�����Ҷ�ӽڵ�
			UnCompress_file.write((char*)&tempNode->pow.ch, sizeof(tempNode->pow.ch));//���뵽��ѹ���ļ�
			//std::cout << tempNode->pow.ch;
			charCount--;//�ַ�������һ
			tempNode = root;//�ص����ڵ�
		}
		if (charCount == 0) {//˵�����е��ַ����������
			break;
		}

	}
	//ʱ������汾
	/*
	string code = "";
	Create_HuffmanCode(root, code);//��ȡhuffman����

	map<string, unsigned char > ::iterator find_node;
	while (true) {
		//�õ�һλHuffmanCode�Ķ�����
		for (int i = 1; i <= code_length; i++) {
			if (tempPos == 0) {
				Compress_file.read((char*)&tempChar, sizeof(tempChar));
				tempPos = 8;
			}
			tempPos--;
			tempBit = (tempChar >> tempPos) & 1;
			tempCode += to_string(tempBit);
		}
		find_node = huffman_map.find(tempCode);
		if (find_node != huffman_map.end()) {//˵���ҵ���
			UnCompress_file.write((char*)&find_node->second, sizeof(find_node->second));//���뵽��ѹ���ļ�
			charCount--;//�ַ�������һ
			tempCode = "";
		}
		if (charCount == 0) {//˵�����е��ַ����������
			break;
		}
	}
	*/
	endTime = clock();
	std::cout << "����ʱ��Ϊ: " << (double)(endTime * 1.0 - startTime * 1.0) / (CLOCKS_PER_SEC * 1.0) << "s" << std::endl;
	std::cout << std::endl;
	//�ر��ļ�
	UnCompress_file.close();
	Compress_file.close();
}
//����Huffman����
void Create_HuffmanCode(TreeNode* temp, string code) {
	if (temp == null_node) {
		return;
	}
	else {
		int flag = 1;//�ж��Ƿ���Ҷ�ӽڵ�,1��ʾҶ�ӽڵ�
		for (int i = 0; i < child__num; i++) {
			if ((temp->child)[i] != null_node) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			information[(unsigned char)(temp->pow.ch)].huff_code = code;
			//huffman_map.insert(std::map <string, unsigned char> ::value_type(code, (unsigned char)(temp->pow.ch)));//temp
			return;
		}
		else {
			for (int i = 0; i < child__num; i++) {
				Create_HuffmanCode((temp->child)[i], code + Ten_To_Two(i));
			}
		}
	}
}
//10����ת2�����ַ���
string Ten_To_Two(int num) {
	string code = "";
	while (num > 0) {
		code = to_string(num % 2) + code;
		num = num / 2;
	}
	while (code.length() < code_length) {
		code = "0" + code;
	}
	return code;
}
//2�����ַ���ת10������
int Two_To_Ten(string num) {
	int result = 0;
	for (int i = num.length() - 1; i >= 0; i--) {
		result += (num[i] - '0') * pow(2.0, num.length() - 1 - i);
	}
	return result;
}
//�ļ���ȡһ��
string Get_Line(FILE* filename) {
	if (feof(filename)) {
		return "";
	}
	string line = "";
	unsigned char temp_char = fgetc(filename);
	while (temp_char != '\n') {
		line += temp_char;
		temp_char = fgetc(filename);
		if (feof(filename)) {
			line += temp_char;
			break;
		}
	}
	line += '\0';
	return line;
}
//�Ƿ���Ҷ�ӽڵ�
bool isNode(TreeNode* node) {
	if (node == NULL || node == null_node) {
		return false;
	}
	bool flag = true;
	for (int i = 0; i < child__num; i++) {
		if ((node->child)[i] != null_node) {
			flag = false;
			break;
		}
	}
	return flag;
}