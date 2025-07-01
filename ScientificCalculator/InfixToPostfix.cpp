#include "InfixToPostfix.h"
#include <stdexcept>

//��������ʹ���沨����ʾ������׺���ʽת��Ϊ��׺���ʽ
vector<Token> InfixToPostfix::run(const vector<Token>& infix) {
    vector<Token> output;// �����ջ
    stack<Token> opStack;//�����׺���ʽ

    for (const Token& token : infix) {
        if (token.is_num() || token.is_var()) 
            //���ֻ����ֱ�ӷ����������
            output.push_back(token);
        else if (token.is_fun()) 
            //����ѹ�������ջ���������ȼ���ߣ�
            opStack.push(token);
        else if (token.is_ope()) {
            //���������ʱ������ջ�����ȼ����߻���ͬ�ҽ����Ϊ���ϵ������
            while (!opStack.empty() && opStack.top().is_ope() &&
                (precedence(opStack.top()) > precedence(token) ||
                    (precedence(opStack.top()) == precedence(token) && associativity(token) == Associativity::Left))) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            //��ǰ�������ջ
            opStack.push(token);
        }
        else if (token.is_LP()) 
            //���������ţ�ֱ����ջ
            opStack.push(token);
        else if (token.is_RP()) 
            //���������ţ�����ջ�������ֱ������������
            pop_ULP(opStack, output);
    }

    //����������󣬵���ջ�����������
    while (!opStack.empty()) {
        if (opStack.top().is_LP() || opStack.top().is_RP())
            throw runtime_error("���Ų�ƥ��");//�������Ų�ƥ��ʱ��������
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;//���غ�׺���ʽ����
}

//������������ȼ�������Խ�������ȼ�Խ��
int InfixToPostfix::precedence(const Token& token) const {
    return token.precedence;
}

//�������������ԣ���/��
Associativity InfixToPostfix::associativity(const Token& token) const {
    return token.associativity;
}

//���������ţ�����ջ�������֪������������
void InfixToPostfix::pop_ULP(stack<Token>& opStack, vector<Token>& output) {
    //����ֱ������������
    while (!opStack.empty() && !opStack.top().is_LP()) {
        output.push_back(opStack.top());
        opStack.pop();
    }

    //���Ϊ�������������׳��쳣
    if (opStack.empty())
        throw runtime_error("���Ų�ƥ�䣺ȱʧ������");
    opStack.pop(); // ����������

    //���������֮ǰ�Ǻ���������Ҳ��ջ���������
    if (!opStack.empty() && opStack.top().is_fun()) {
        output.push_back(opStack.top());
        opStack.pop();
    }
}