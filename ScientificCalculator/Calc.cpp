#include "Calc.h"
#include <iostream>
#include<algorithm>

// ��̬��Ա��ʼ��
Tokenizer Calc::tokenizer;
InfixToPostfix Calc::converter;
PostfixEval Calc::evaluator;

std::unordered_map<std::string, double> Calc::vars = {
    {"PAI", 2 * std::asin(1)},
    {"pi", 3.14159265358979},
    {"e", std::exp(1)}
};


// ������ӿڣ����ʽ�ַ��� -> ������
double Calc::eval(const string& expression) {
    std::string varName, rightExpr;

    // �ж��Ƿ�Ϊ��ֵ���ʽ������ x = 3 + sin(2)
    if (is_assign(expression, varName, rightExpr)) {
        vector<Token> tokens = tokenizer.run(rightExpr);
        vector<Token> postfix = converter.run(tokens);
        double val = evaluator.run(postfix, vars);
        vars[varName] = val;
        return val;
    }

    vector<Token> tokens = tokenizer.run(expression);
    vector<Token> postfix = converter.run(tokens);
    return evaluator.run(postfix,vars);
}

// ��ȫ����ӿڣ��� try-catch ��װ������ bool ��־
bool Calc::safeEval(const string& expr, double& res) {
    try {
        res = eval(expr);
        return true;
    }
    catch (const exception& e) {
        cerr << "[Error] " << e.what() << endl;
        return false;
    }
}

// ���Խӿڣ���ӡ�м�����token �б� �� ��׺���ʽ��
void Calc::debug(const string& expr) {
    try {
        vector<Token> tokens = tokenizer.run(expr);
        cout << "[Token List]" << endl;
        for (const auto& t : tokens) cout << t.value << " ";
        cout << endl;

        vector<Token> postfix = converter.run(tokens);
        cout << "[Postfix]" << endl;
        for (const auto& t : postfix) cout << t.value << " ";
        cout << endl;
    }
    catch (const exception& e) {
        cerr << "[Debug Error] " << e.what() << endl;
    }
}

bool Calc::is_assign(const std::string& expr, std::string& varName, std::string& rightExpr) {
    size_t eqPos = expr.find('=');
    if (eqPos != std::string::npos) {
        varName = expr.substr(0, eqPos);
        rightExpr = expr.substr(eqPos + 1);
        // ȥ���ո�
        varName.erase(remove_if(varName.begin(), varName.end(), isspace), varName.end());
        rightExpr.erase(remove_if(rightExpr.begin(), rightExpr.end(), isspace), rightExpr.end());
        // �������Ƿ�Ϸ���ֻ����ĸ��
        return !varName.empty() && std::all_of(varName.begin(), varName.end(), ::isalpha);
    }
    return false;
}

