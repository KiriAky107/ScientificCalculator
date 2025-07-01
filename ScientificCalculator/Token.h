#ifndef TOKEN_H
#define TOKEN_H

#include<string>

using namespace std;
//�Ǻ�����
enum class TokenType {
	Number,
	Operator,
	LeftParen,
	RightParen,
	Function,
	Variable
};

//����������
enum class Associativity {
	Left,
	Right,
	None
};

//Token�ṹ��
struct Token {
	TokenType type;//�Ǻ�����
	string value;  //ʵ���ַ���
	int precedence = -1; //���ȼ�������������ͺ�����Ч
	Associativity associativity = Associativity::None; //����ԣ�����������ͺ�����Ч
	
	//���캯��
	Token(TokenType t, const string& v,
		int p = -1, Associativity assoc = Associativity::None)
		:type(t), value(v), precedence(p), associativity(assoc) {}

	//�����жϷ���

	// �ж��Ƿ�Ϊ���֣����� "3.14", "42"��
	bool is_num() const { return type == TokenType::Number; }
	// �ж��Ƿ�Ϊ����������� "+", "-", "*", "/"��
	bool is_ope() const { return type == TokenType::Operator; }
	// �ж��Ƿ�Ϊ��ѧ���������� "sin", "cos", "log"��
	bool is_fun() const { return type == TokenType::Function; }
	// �ж��Ƿ�Ϊ������ "("�����ڱ��ʽ����
	bool is_LP() const { return type == TokenType::LeftParen; }
	// �ж��Ƿ�Ϊ������ ")"�����ڱ��ʽ�������
	bool is_RP() const { return type == TokenType::RightParen; }
	// �ж��Ƿ�Ϊ�������� "x", "y"������չ֧�ַ��Ŵ�����
	bool is_var()const { return type == TokenType::Variable; }

};
#endif