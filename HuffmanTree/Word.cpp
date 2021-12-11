#include "Word.h"
using namespace std;

Word::Word() {
	ch = 0;
	count = 0;
	huff_code = "";
}

Word::Word(unsigned char ch, long long count, string huff_code) {
	this->ch = ch;
	this->count = count;
	this->huff_code = huff_code;
}
//����С�ں�
bool Word::operator<(const Word& word) {
	return this->count < word.count;
}
//���ش��ں�
bool Word::operator>(const Word& word) {
	return this->count > word.count;
}
//���ؼӺ�
Word Word::operator+(const Word& word) {
	Word tempWord;
	tempWord.count = this->count + word.count;
	return tempWord;
}
//���ز��Ⱥ�
bool Word::operator!=(const Word& word) {
	return this->count != word.count;
}
//���ظ�ֵ�Ⱥ�
Word& Word::operator=(const Word& word) {
	if (this == &word) {
		return *this;
	}
	this->ch = word.ch;
	this->count = word.count;
	this->huff_code = word.huff_code;
	return *this;
}
//������������
ostream& operator<<(ostream& os, Word& word) {
	os << (int)word.ch << ":" << word.count << "  ";
	return os;
}
