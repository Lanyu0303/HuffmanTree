#pragma once
#include <iostream>　
#include<bits/stdc++.h>
#include <string>
#include <fstream>  
#include <windows.h>
#include<stdlib.h>
using namespace std;
class Word {
public:
	unsigned char ch;//在文件中出现的字符
	long long count;//在文件中出现的次数
	string huff_code;//文字的haffman编码
	Word();//构造函数
	Word(unsigned char ch, long long count, string huff_code);
	//重载运算符，都是对count操作
	bool operator < (const Word& word);//重载小于号
	bool operator > (const Word& word);//重载大于号
	Word operator + (const Word& word);//重载加号
	bool operator != (const Word& word);//重载不等号
	Word& operator = (const Word& word);//重载等号
	friend ostream& operator<<(ostream& os, Word& word);//重载<<输出运算符
};

