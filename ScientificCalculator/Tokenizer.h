#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<string>
#include<vector>
#include"Token.h"

using namespace std;

class Tokenizer {
public:
	//�����������������ʽ�ַ���ת��ΪToken����
	vector<Token> run(const string& expr);

private:
	string expression; //��ǰ����ı��ʽ
	size_t pos = 0;   //��ǰָ��λ��

	//���ߺ���:�����ո��ַ�
	void skipWhitespace();

	//��ȡһ���������֣���С����С���㡢���ܵ�һԪ���ţ�
	Token readNumber();

	//��ȡ������(��sin��cos��log��)�����������x��y��
	Token readIdentifier();
	
	//��ȡ�����������
	Token readOperatorOrParen();

	//�жϵ�ǰλ���Ƿ���һԪ���ŵ�������
	bool is_UMC(const vector<Token>& tokens);

	//�ַ��жϸ�������
	bool is_dig(char c)const;
	bool is_let(char c)const;
	bool is_OpeCh(char c)const;
};

#endif