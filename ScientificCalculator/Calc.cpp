#include "Calc.h"
#include <iostream>

// 静态成员初始化
Tokenizer Calc::tokenizer;
InfixToPostfix Calc::converter;
PostfixEval Calc::evaluator;

// 主计算接口：表达式字符串 -> 计算结果
double Calc::eval(const string& expression) {
    vector<Token> tokens = tokenizer.run(expression);
    vector<Token> postfix = converter.run(tokens);
    return evaluator.run(postfix);
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
