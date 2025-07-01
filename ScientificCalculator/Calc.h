#ifndef CALC_H
#define CALC_H

#include"Tokenizer.h"
#include"InfixToPostfix.h"
#include"PostfixEval.h"
#include<optional>
#include<unordered_map>

using namespace std;

class Calc {
public:
	//主接口函数：输入表达式字符串，返回计算结果
	static double eval(const string& expresssion);

	//安全接口：带异常处理，返回optional
	static bool safeEval(const string& expr,double& res);

	//调试函数：打印token列表与后缀表达式
	static void debug(const string& expr);
private:
	static Tokenizer tokenizer;
	static InfixToPostfix converter;
	static PostfixEval evaluator;
};

#endif
