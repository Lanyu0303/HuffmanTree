#define _CRT_SECURE_NO_WARNINGS
#include <iostream>　
#include <string>
#include <fstream>  
#include "TreeNode.h"
#include "HuffmanTree.h"
#include "Heap.h"
#include "Word.h"

using namespace std;
void print_menu();//输出菜单
void Compress(char* path);//压缩
void UnCompress(char* path);//解压缩
void Create_HuffmanCode(TreeNode* temp, string code);//构建Huffman编码
string Ten_To_Two(int num);//10进制转2进制字符串
int Two_To_Ten(string num);//2进制字符串转10进制数
string Get_Line(FILE* filename);//文件读取一行
bool isNode(TreeNode* node);//是否是叶子节点

//要保存到文件里的信息

struct info {
	unsigned char ch;
	long long count;
};
int child__num;
int word_num;
Word information[256];
extern TreeNode* null_node;
int code_length;//Huffman编码的长度
std::map<string, unsigned char> huffman_map;
int main() {
	int choice = 0;
	int temp_child_num = 2;
	char file_path[] = "";
	word_num = 0;
	//初始化
	for (int i = 0; i < 256; i++) {
		information[i].ch = i;
		information[i].count = 0;
	}
	//开始进行选择
	while (true) {
		print_menu();
		cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "请输入文件地址:" << endl;
			cin >> file_path;
			std::cout << "您输入的地址为：" << file_path << endl;
			std::cout << "请输入为几元树:" << endl;
			cin >> child__num;
			std::cout << "您输入的孩子数为：" << child__num << endl;
			code_length = ceil(log(child__num * 1.0) / log(2.0));//获取Huffman编码长度
			Compress(file_path);
			break;
		case 2:
			std::cout << "请输入文件地址:" << endl;
			cin >> file_path;
			std::cout << "您输入的地址为：" << file_path << endl;
			UnCompress(file_path);
			break;
		case 3:
			std::cout << "程序已退出" << endl;
			return 0;
		default:
			std::cout << "输入错误选项，请重新输入" << endl;
			break;
		}
	}
	return 0;
}
//输出菜单
void print_menu() {
	std::cout << "--------菜单----------" << endl;
	std::cout << "|1.压缩文件" << endl;
	std::cout << "|2.解压文件" << endl;
	std::cout << "|3.退出" << endl;
	std::cout << "请输入你的选择:";
}
//压缩
void Compress(char* path) {
	//统计字符出现的次数
	fstream file;
	file.open(path, ifstream::in | ios::binary);
	if (!file) {
		std::cout << "文件为空！出错" << endl;
		return;
	}
	unsigned char temp_ch;
	long long temp_count = 0;
	while (file.read((char*)&temp_ch, sizeof(temp_ch))) {
		information[temp_ch].count++;//此字符对应的次数
		temp_count++;
	}
	Word invalid;
	invalid.count = 0;
	//输出文件信息
	for (int i = 0; i < 256; i++) {
		if (information[i] != invalid) {
			std::cout << (int)information[i].ch << ":" << information[i].count << "   ";
			word_num++;
		}
	}
	std::cout << endl;
	//构建Huffman树
	HuffmanTree tree(information, 256, invalid);
	TreeNode* root = tree.root;//获取根节点
	//输出Huffman树
	std::cout << "Huffman树为：" << std::endl;
	tree.ShowTree(tree.root);
	//获取Huffman编码
	string code = "";
	Create_HuffmanCode(root, code);
	//输出文件信息
	for (int i = 0; i < 256; i++) {
		if (information[i] != invalid) {
			std::cout << (int)information[i].ch << ":" << information[i].count << ":" << information[i].huff_code << "   ";
		}
	}
	//开始压缩
	file.close();
	file.open(path, ifstream::in | ios::binary);//重新打开源文件
	char final[7] = ".my";
	strcat(path, final);
	std::cout << "现在文件地址为：" << path << endl;
	fstream compress_file(path, ofstream::app | ios::binary | ofstream::out);
	//先写入配置信息
	string child_inf = to_string(child__num);//输出孩子节点数量
	compress_file << child_inf << '\n';
	compress_file << word_num << '\n';//输出字母数量
	for (int i = 0; i < 256; i++) {
		if (information[i] != invalid) {
			compress_file.write((char*)&information[i].ch, sizeof(information[i].ch));
			compress_file << ":" << information[i].count << '\n';
		}
	}
	//向压缩文件里写入Huffman编码
	unsigned char ch1;//读源文件内容
	file.read((char*)&ch1, sizeof(ch1));
	unsigned char value = 0;
	int pos = 0;
	while (ch1 != EOF) {
		if (file.eof())
			break;
		string& code = information[ch1].huff_code;//每个字符的Huffman编码
		for (size_t i = 0; i < code.size(); i++) {//一个一个比特位来进行放
			value <<= 1;
			//先左移一位，如果code为1就进行下面的代码，把第一位变为1，为0就不处理
			if (code[i] == '1') {//得到二进制的1
				value |= 1;//把最右边为0的位置变为1，即就是写进1.
			}
			if (++pos == 8) {//满8位写入文件
				compress_file.write((char*)&value, sizeof(value));//把value写进去，里面存的8个位就是HuffmanCode
				value = 0;//重置，循环写
				pos = 0;
			}
		}
		file.read((char*)&ch1, sizeof(ch1));
	}
	if (pos) {//最后一个编码不足8个位
		value = value << (8 - pos);//不足一个字节，给后面补0再写进fin文件
		compress_file.write((char*)&value, sizeof(value));
	}
	//关闭文件
	file.close();
	compress_file.close();
}
//解压缩
void UnCompress(char* path) {
	string soure_file_name = path;
	int pos_count = soure_file_name.find_last_of('.');//找到最后一个点
	string UnCompress_file_name = soure_file_name.substr(0, pos_count);
	std::cout << "解压的文件地址为:" << UnCompress_file_name << endl;
	//创建解压文件
	fstream UnCompress_file(UnCompress_file_name, ofstream::app | ios::binary | ofstream::out);//打开解压文件
	fstream Compress_file;
	Compress_file.open(soure_file_name, ifstream::in | ios::binary);//打开压缩过的文件
	string temp_string = "";
	getline(Compress_file, temp_string);//读取一行
	child__num = atoi(temp_string.c_str());//获取child__num
	getline(Compress_file, temp_string);//读取一行
	word_num = atoi(temp_string.c_str());//获取字母数量
	code_length = ceil(log(child__num * 1.0) / log(2.0));//获取Huffman编码长度
	std::cout << "获取的child__num = " << child__num << endl;
	std::cout << "code_length = " << code_length << endl;
	unsigned char tempch;
	unsigned char uselessch;
	string temp_num = "";
	long long tempcount = 0;
	int inflag = 0;//获取配置信息是否结束
	int temp_word_num = 0;
	while (temp_word_num != word_num) {
		Compress_file.read((char*)&tempch, sizeof(tempch));
		temp_word_num++;
		Compress_file.read((char*)&uselessch, sizeof(uselessch));//读取冒号
		Compress_file >> tempcount;
		information[tempch].count = tempcount;
		Compress_file.read((char*)&uselessch, sizeof(uselessch));//读取回车
	}
	//Compress_file.read((char*)&uselessch, sizeof(uselessch));//读取回车
	//输出获取的信息,并获取字符总数
	long long charCount = 0;//字符总数
	std::cout << "读取的字符为：" << endl;
	for (int i = 0; i < 256; i++) {
		if (information[i].count != 0) {
			std::cout << (int)information[i].ch << ":" << information[i].count << "  ";
			charCount += information[i].count;
		}
	}
	std::cout << endl;
	//构建Huffman树
	Word invalid;
	invalid.count = 0;
	HuffmanTree tree(information, 256, invalid);
	TreeNode* root = tree.root;//获取根节点
	TreeNode* tempNode = root;//临时的节点指针
	//输出Huffman树
	std::cout << "Huffman树为：" << endl;
	tree.ShowTree(tree.root);
	//开始解压
	string tempCode = "";//临时的Huffman节点
	unsigned char tempChar;
	Compress_file.read((char*)&tempChar, sizeof(tempChar));
	int tempPos = 8;
	int tempBit = 0;
	clock_t startTime, endTime;//测试解压时间
	startTime = clock();//开始
	std::cout << "正在解压，请耐心等待" << std::endl;
	//std::cout << "输出文件为：" << endl;
	while (true) {
		//得到一位HuffmanCode的二进制
		for (int i = 1; i <= code_length; i++) {
			if (tempPos == 0) {
				Compress_file.read((char*)&tempChar, sizeof(tempChar));
				tempPos = 8;
			}
			tempPos--;
			tempBit = (tempChar >> tempPos) & 1;
			tempCode += to_string(tempBit);
		}
		//将二进制转为10进制
		tempNode = tempNode->child[Two_To_Ten(tempCode)];//移动一次
		tempCode = "";//清零
		if (isNode(tempNode) == true) {//如果是叶子节点
			UnCompress_file.write((char*)&tempNode->pow.ch, sizeof(tempNode->pow.ch));//输入到解压缩文件
			//std::cout << tempNode->pow.ch;
			charCount--;//字符总数减一
			tempNode = root;//回到根节点
		}
		if (charCount == 0) {//说明所有的字符都输出完了
			break;
		}

	}
	//时间更慢版本
	/*
	string code = "";
	Create_HuffmanCode(root, code);//获取huffman编码

	map<string, unsigned char > ::iterator find_node;
	while (true) {
		//得到一位HuffmanCode的二进制
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
		if (find_node != huffman_map.end()) {//说明找到了
			UnCompress_file.write((char*)&find_node->second, sizeof(find_node->second));//输入到解压缩文件
			charCount--;//字符总数减一
			tempCode = "";
		}
		if (charCount == 0) {//说明所有的字符都输出完了
			break;
		}
	}
	*/
	endTime = clock();
	std::cout << "运行时间为: " << (double)(endTime * 1.0 - startTime * 1.0) / (CLOCKS_PER_SEC * 1.0) << "s" << std::endl;
	std::cout << std::endl;
	//关闭文件
	UnCompress_file.close();
	Compress_file.close();
}
//构建Huffman编码
void Create_HuffmanCode(TreeNode* temp, string code) {
	if (temp == null_node) {
		return;
	}
	else {
		int flag = 1;//判断是否是叶子节点,1表示叶子节点
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
//10进制转2进制字符串
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
//2进制字符串转10进制数
int Two_To_Ten(string num) {
	int result = 0;
	for (int i = num.length() - 1; i >= 0; i--) {
		result += (num[i] - '0') * pow(2.0, num.length() - 1 - i);
	}
	return result;
}
//文件读取一行
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
//是否是叶子节点
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