#include "Calc.h"
#include <iostream>

// ��̬��Ա��ʼ��
Tokenizer Calc::tokenizer;
InfixToPostfix Calc::converter;
PostfixEval Calc::evaluator;

// ������ӿڣ����ʽ�ַ��� -> ������
double Calc::eval(const string& expression) {
    vector<Token> tokens = tokenizer.run(expression);
    vector<Token> postfix = converter.run(tokens);
    return evaluator.run(postfix);
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
