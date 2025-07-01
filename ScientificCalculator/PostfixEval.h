#ifndef POSTFIXEVAL_H
#define POSYFIXEVAL_H

#include "Token.h"
#include <vector>
#include <stack>
#include <cmath>
#include <stdexcept>
#include<unordered_map>

using namespace std;
class PostfixEval {
public:
	//���������Ժ�׺���ʽ������ֵ
	double run(const std::vector<Token>& postfix, const unordered_map<string, double>& vars = {});

private:
	//Ӧ���ڶ�Ԫ����������+��-��*��/��^
	double apply_BO(const string& op, double a, double b);

	//Ӧ����ҽԺ�������Ⱥ�������sin, cos, log
	double apply_UF(const string& func, double x);

	//Ӧ����һԪ��׺�����,�磡
	double apply_Fac(double x);
};

#endif
