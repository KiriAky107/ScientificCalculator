#include "Calc.h"
#include <iostream>
#include<algorithm>

// 静态成员初始化
Tokenizer Calc::tokenizer;
InfixToPostfix Calc::converter;
PostfixEval Calc::evaluator;

std::unordered_map<std::string, double> Calc::vars = {
    {"PAI", 2 * std::asin(1)},
    {"pi", 3.14159265358979},
    {"e", std::exp(1)}
};


// 主计算接口：表达式字符串 -> 计算结果
double Calc::eval(const string& expression) {
    std::string varName, rightExpr;

    // 判断是否为赋值表达式，例如 x = 3 + sin(2)
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

// 安全计算接口：带 try-catch 封装，返回 bool 标志
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

// 调试接口：打印中间结果（token 列表 和 后缀表达式）
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
        // 去除空格
        varName.erase(remove_if(varName.begin(), varName.end(), isspace), varName.end());
        rightExpr.erase(remove_if(rightExpr.begin(), rightExpr.end(), isspace), rightExpr.end());
        // 检查变量是否合法（只含字母）
        return !varName.empty() && std::all_of(varName.begin(), varName.end(), ::isalpha);
    }
    return false;
}

