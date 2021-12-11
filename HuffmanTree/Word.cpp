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
//重载小于号
bool Word::operator<(const Word& word) {
	return this->count < word.count;
}
//重载大于号
bool Word::operator>(const Word& word) {
	return this->count > word.count;
}
//重载加号
Word Word::operator+(const Word& word) {
	Word tempWord;
	tempWord.count = this->count + word.count;
	return tempWord;
}
//重载不等号
bool Word::operator!=(const Word& word) {
	return this->count != word.count;
}
//重载赋值等号
Word& Word::operator=(const Word& word) {
	if (this == &word) {
		return *this;
	}
	this->ch = word.ch;
	this->count = word.count;
	this->huff_code = word.huff_code;
	return *this;
}
//重载输出运算符
ostream& operator<<(ostream& os, Word& word) {
	os << (int)word.ch << ":" << word.count << "  ";
	return os;
}
