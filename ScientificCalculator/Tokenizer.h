#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<string>
#include<vector>
#include"Token.h"

using namespace std;

class Tokenizer {
public:
	//主解析函数：将表达式字符串转换为Token序列
	vector<Token> run(const string& expr);

private:
	string expression; //当前处理的表达式
	size_t pos = 0;   //当前指针位置

	//工具函数:跳过空格字符
	void skipWhitespace();

	//读取一个完整数字（含小数、小数点、可能的一元负号）
	Token readNumber();

	//读取函数名(如sin、cos、log等)或变量名（如x、y）
	Token readIdentifier();
	
	//读取运算符或括号
	Token readOperatorOrParen();

	//判断当前位置是否处于一元符号的上下文
	bool is_UMC(const vector<Token>& tokens);

	//字符判断辅助函数
	bool is_dig(char c)const;
	bool is_let(char c)const;
	bool is_OpeCh(char c)const;
};

#endif