#include"PostfixEval.h"
#include<algorithm>
#include<cctype>

double PostfixEval::run(const std::vector<Token>& postfix, const unordered_map<string, double>& vars) {
	stack<double> stk;

	for (const auto& token : postfix) {
		if (token.is_num())
			//数字转换为double入栈
			stk.push(stod(token.value));
		else if (token.is_var()) {
			//查找变量映射表
			auto it = vars.find(token.value);
			// 支持内置常量 PAI 和 e
			
			if (it == vars.end()) {
				if (token.value == "PAI")
					stk.push(2.0 * std::asin(1.0));  // π = 2 * arcsin(1)
				else if (token.value == "e")
					stk.push(std::exp(1.0));         // e = exp(1)
				else
					throw runtime_error("变量未定义：" + token.value);
			}
			else stk.push(it->second);
		}
		else if (token.is_ope()) {
			//取出两个操作数，执行二元运算
			if (stk.size() < 2)	throw runtime_error("操作数不足");
			double b = stk.top();
			stk.pop();
			double a = stk.top();
			stk.pop();
			double res = apply_BO(token.value, a, b);
			stk.push(res);
		}
		else if (token.is_fun()) {
			//取出一个操作数，执行一元基本初等函数的计算
			if (stk.empty())	throw runtime_error("操作数不足");
			double x = stk.top();
			stk.pop();
			double res = apply_UF(token.value, x);
			stk.push(res);
		}
		else
			throw runtime_error("未知Token类型");
	}

	if (stk.size() != 1)
		throw runtime_error("表达式错误，计算结果栈不唯一");

	return stk.top();
}

//进行二元运算符的运算
double PostfixEval::apply_BO(const string& op, double a, double b) {
	if (op == "+")	return a + b;
	if (op == "-")	return a - b;
	if (op == "*")	return a * b;
	if (op == "/") {
		if (b == 0) throw runtime_error("除数不能为0");
		return a / b;
	}
	if (op == "^")	return pow(a, b);
	if (op == "%") {
		if (b == 0) throw runtime_error("模除数不能为零");
		return std::fmod(a, b);
	}
	throw runtime_error("未知运算符：" + op);
}

//进行一元基本初等函数的运算
double PostfixEval::apply_UF(const string& func, double x) {
	string f = func;
	transform(f.begin(), f.end(), f.begin(), ::tolower);

	if (f == "sin")	return sin(x);
	if (f == "cos")	return cos(x);
	if (f == "tan")	return tan(x);
	if (f == "sqrt") {
		if (x < 0)	
			throw runtime_error("sqrt参数不能为负");
		return sqrt(x);
	}
	if (f == "log") {
		if (x <= 0)
			throw runtime_error("log参数必须大于0");
		return log(x);
	}
	if (f == "exp")	return exp(x);
	if (f == "abs")	return fabs(x);
	if (f == "asin")	return asin(x);
	if (f == "acos")	return acos(x);
	if (f == "atan")	return atan(x);

	throw runtime_error("未知函数：" + func);
}
