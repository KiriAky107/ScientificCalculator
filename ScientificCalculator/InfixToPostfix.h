#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H

#include"Token.h"
#include<vector>
#include<stack>

using namespace std;

class InfixToPostfix {
public:
	//主转换函数：将中缀表达式转换为后缀表达式
	vector<Token> run(const vector<Token>& infix);

private:
	//返回指定运算符的优先级
	int precedence(const Token& token) const;

	//判断运算符的结合性（左/右）
	Associativity associativity(const Token& token) const;

	//遇到做右括号时，从栈中弹出操作符直到遇到左括号
	void pop_ULP(stack<Token>& opStack, vector<Token>& output);

};

#endif
