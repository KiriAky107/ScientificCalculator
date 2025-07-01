#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H

#include"Token.h"
#include<vector>
#include<stack>

using namespace std;

class InfixToPostfix {
public:
	//��ת������������׺���ʽת��Ϊ��׺���ʽ
	vector<Token> run(const vector<Token>& infix);

private:
	//����ָ������������ȼ�
	int precedence(const Token& token) const;

	//�ж�������Ľ���ԣ���/�ң�
	Associativity associativity(const Token& token) const;

	//������������ʱ����ջ�е���������ֱ������������
	void pop_ULP(stack<Token>& opStack, vector<Token>& output);

};

#endif
