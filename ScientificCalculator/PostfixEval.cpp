#include"PostfixEval.h"
#include<algorithm>
#include<cctype>

double PostfixEval::run(const std::vector<Token>& postfix, const unordered_map<string, double>& vars) {
	stack<double> stk;

	for (const auto& token : postfix) {
		if (token.is_num())
			//����ת��Ϊdouble��ջ
			stk.push(stod(token.value));
		else if (token.is_var()) {
			//���ұ���ӳ���
			auto it = vars.find(token.value);
			// ֧�����ó��� PAI �� e
			
			if (it == vars.end()) {
				if (token.value == "PAI")
					stk.push(2.0 * std::asin(1.0));  // �� = 2 * arcsin(1)
				else if (token.value == "e")
					stk.push(std::exp(1.0));         // e = exp(1)
				else
					throw runtime_error("����δ���壺" + token.value);
			}
			else stk.push(it->second);
		}
		else if (token.is_ope()) {
			//ȡ��������������ִ�ж�Ԫ����
			if (stk.size() < 2)	throw runtime_error("����������");
			double b = stk.top();
			stk.pop();
			double a = stk.top();
			stk.pop();
			double res = apply_BO(token.value, a, b);
			stk.push(res);
		}
		else if (token.is_fun()) {
			//ȡ��һ����������ִ��һԪ�������Ⱥ����ļ���
			if (stk.empty())	throw runtime_error("����������");
			double x = stk.top();
			stk.pop();
			double res = apply_UF(token.value, x);
			stk.push(res);
		}
		else
			throw runtime_error("δ֪Token����");
	}

	if (stk.size() != 1)
		throw runtime_error("���ʽ���󣬼�����ջ��Ψһ");

	return stk.top();
}

//���ж�Ԫ�����������
double PostfixEval::apply_BO(const string& op, double a, double b) {
	if (op == "+")	return a + b;
	if (op == "-")	return a - b;
	if (op == "*")	return a * b;
	if (op == "/") {
		if (b == 0) throw runtime_error("��������Ϊ0");
		return a / b;
	}
	if (op == "^")	return pow(a, b);
	if (op == "%") {
		if (b == 0) throw runtime_error("ģ��������Ϊ��");
		return std::fmod(a, b);
	}
	throw runtime_error("δ֪�������" + op);
}

//����һԪ�������Ⱥ���������
double PostfixEval::apply_UF(const string& func, double x) {
	string f = func;
	transform(f.begin(), f.end(), f.begin(), ::tolower);

	if (f == "sin")	return sin(x);
	if (f == "cos")	return cos(x);
	if (f == "tan")	return tan(x);
	if (f == "sqrt") {
		if (x < 0)	
			throw runtime_error("sqrt��������Ϊ��");
		return sqrt(x);
	}
	if (f == "log") {
		if (x <= 0)
			throw runtime_error("log�����������0");
		return log(x);
	}
	if (f == "exp")	return exp(x);
	if (f == "abs")	return fabs(x);
	if (f == "asin")	return asin(x);
	if (f == "acos")	return acos(x);
	if (f == "atan")	return atan(x);

	throw runtime_error("δ֪������" + func);
}
