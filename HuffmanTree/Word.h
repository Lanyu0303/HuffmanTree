#pragma once
#include <iostream>��
#include<bits/stdc++.h>
#include <string>
#include <fstream>  
#include <windows.h>
#include<stdlib.h>
using namespace std;
class Word {
public:
	unsigned char ch;//���ļ��г��ֵ��ַ�
	long long count;//���ļ��г��ֵĴ���
	string huff_code;//���ֵ�haffman����
	Word();//���캯��
	Word(unsigned char ch, long long count, string huff_code);
	//��������������Ƕ�count����
	bool operator < (const Word& word);//����С�ں�
	bool operator > (const Word& word);//���ش��ں�
	Word operator + (const Word& word);//���ؼӺ�
	bool operator != (const Word& word);//���ز��Ⱥ�
	Word& operator = (const Word& word);//���صȺ�
	friend ostream& operator<<(ostream& os, Word& word);//����<<��������
};

