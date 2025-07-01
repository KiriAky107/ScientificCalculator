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
	//主函数：对后缀表达式进行求值
	double run(const std::vector<Token>& postfix, const unordered_map<string, double>& vars = {});

private:
	//应用于二元操作符，如+，-，*，/，^
	double apply_BO(const string& op, double a, double b);

	//应用于医院基本初等函数，如sin, cos, log
	double apply_UF(const string& func, double x);

	//应用于一元后缀运算符,如！
	double apply_Fac(double x);
};

#endif
