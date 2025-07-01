#include "InfixToPostfix.h"
#include <stdexcept>

//主函数：使用逆波兰表示法将中缀表达式转换为后缀表达式
vector<Token> InfixToPostfix::run(const vector<Token>& infix) {
    vector<Token> output;// 运算符栈
    stack<Token> opStack;//输出后缀表达式

    for (const Token& token : infix) {
        if (token.is_num() || token.is_var()) 
            //数字或变量直接放入输出队列
            output.push_back(token);
        else if (token.is_fun()) 
            //函数压入运算符栈（函数优先级最高）
            opStack.push(token);
        else if (token.is_ope()) {
            //遇到运算符时，弹出栈中优先级更高或相同且结合性为左结合的运算符
            while (!opStack.empty() && opStack.top().is_ope() &&
                (precedence(opStack.top()) > precedence(token) ||
                    (precedence(opStack.top()) == precedence(token) && associativity(token) == Associativity::Left))) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            //当前运算符入栈
            opStack.push(token);
        }
        else if (token.is_LP()) 
            //遇到左括号，直接入栈
            opStack.push(token);
        else if (token.is_RP()) 
            //遇到右括号，弹出栈中运算符直到遇到左括号
            pop_ULP(opStack, output);
    }

    //遍历完输入后，弹出栈中所有运算符
    while (!opStack.empty()) {
        if (opStack.top().is_LP() || opStack.top().is_RP())
            throw runtime_error("括号不匹配");//左右括号不匹配时弹出错误
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;//返回后缀表达式序列
}

//返回运算符优先级，数字越大则优先级越高
int InfixToPostfix::precedence(const Token& token) const {
    return token.precedence;
}

//返回运算符结核性，左/右
Associativity InfixToPostfix::associativity(const Token& token) const {
    return token.associativity;
}

//处理右括号，弹出栈中运算符知道遇到左括号
void InfixToPostfix::pop_ULP(stack<Token>& opStack, vector<Token>& output) {
    //弹出直到遇到左括号
    while (!opStack.empty() && !opStack.top().is_LP()) {
        output.push_back(opStack.top());
        opStack.pop();
    }

    //如果为遇到左括号则抛出异常
    if (opStack.empty())
        throw runtime_error("括号不匹配：缺失左括号");
    opStack.pop(); // 弹出左括号

    //如果左括号之前是函数，则函数也出栈并加入输出
    if (!opStack.empty() && opStack.top().is_fun()) {
        output.push_back(opStack.top());
        opStack.pop();
    }
}