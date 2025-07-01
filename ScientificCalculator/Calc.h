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
	//���ӿں�����������ʽ�ַ��������ؼ�����
	static double eval(const string& expresssion);

	//��ȫ�ӿڣ����쳣��������optional
	static bool safeEval(const string& expr,double& res);

	//���Ժ�������ӡtoken�б����׺���ʽ
	static void debug(const string& expr);
private:
	static Tokenizer tokenizer;
	static InfixToPostfix converter;
	static PostfixEval evaluator;
};

#endif
