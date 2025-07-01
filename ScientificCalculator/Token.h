#ifndef TOKEN_H
#define TOKEN_H

#include<string>

using namespace std;
//记号类型
enum class TokenType {
	Number,
	Operator,
	LeftParen,
	RightParen,
	Function,
	Variable
};

//运算符结合性
enum class Associativity {
	Left,
	Right,
	None
};

//Token结构体
struct Token {
	TokenType type;//记号类型
	string value;  //实际字符串
	int precedence = -1; //优先级，仅对运算符和函数有效
	Associativity associativity = Associativity::None; //结合性，仅对运算符和函数有效
	
	//构造函数
	Token(TokenType t, const string& v,
		int p = -1, Associativity assoc = Associativity::None)
		:type(t), value(v), precedence(p), associativity(assoc) {}

	//辅助判断方法

	// 判断是否为数字（例如 "3.14", "42"）
	bool is_num() const { return type == TokenType::Number; }
	// 判断是否为运算符（例如 "+", "-", "*", "/"）
	bool is_ope() const { return type == TokenType::Operator; }
	// 判断是否为数学函数（例如 "sin", "cos", "log"）
	bool is_fun() const { return type == TokenType::Function; }
	// 判断是否为左括号 "("，用于表达式分组
	bool is_LP() const { return type == TokenType::LeftParen; }
	// 判断是否为右括号 ")"，用于表达式分组结束
	bool is_RP() const { return type == TokenType::RightParen; }
	// 判断是否为变量（如 "x", "y"，可扩展支持符号代数）
	bool is_var()const { return type == TokenType::Variable; }

};
#endif