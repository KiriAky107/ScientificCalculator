#include"Tokenizer.h"
#include<cctype>
#include<stdexcept>

using namespace std;

vector<Token> Tokenizer::run(const string& expr) {

    expression = expr;
    pos = 0;
    vector<Token> tokens;

    // 主循环：逐字符读取表达式
    while (pos < expression.length()) {

        skipWhitespace();// 跳过空白字符
        if (pos >= expression.length()) break;

        char current = expression[pos];

        // 如果是数字或一元负号开头，读取完整数字
        if (is_dig(current) || (current == '-' && is_UMC(tokens)))
            tokens.push_back(readNumber());

        // 如果是字母，读取函数或变量名
        else if (is_let(current))
            tokens.push_back(readIdentifier());

        // 否则读取操作符或括号
        else
            tokens.push_back(readOperatorOrParen());
    }

    return tokens;
}

void Tokenizer::skipWhitespace() {
    // 跳过所有空格、制表符等空白字符
    while (pos < expression.length() && isspace(expression[pos]))
        ++pos;
}

Token Tokenizer::readNumber() {
    size_t start = pos;
    bool hasDecimal = false;// 标记小数点是否出现过

    if (expression[pos] == '-')
        ++pos;  // 若是一元负号，先跳过

    while (pos < expression.length() && (is_dig(expression[pos]) || expression[pos] == '.')) {
        if (expression[pos] == '.') {
            if (hasDecimal)
                throw runtime_error("数字格式无效：多个小数点");// 小数点重复错误
            hasDecimal = true;
        }
        ++pos;
    }

    string numberStr = expression.substr(start, pos - start);
    return Token(TokenType::Number, numberStr);// 构造数字 Token
}

Token Tokenizer::readIdentifier() {
    size_t start = pos;

    // 读取连续的字母字符（函数名或变量名）
    while (pos < expression.length() && is_let(expression[pos]))
        ++pos;

    string name = expression.substr(start, pos - start);

    //识别函数与变量（若后面紧跟‘（’则为函数，否则为变量）
    skipWhitespace();
    if (pos < expression.length() && expression[pos] == '(')
        return Token(TokenType::Function, name);
    else
        return Token(TokenType::Variable, name);
}

Token Tokenizer::readOperatorOrParen() {
    if (expression[pos] == '/' && pos + 1 < expression.length() && expression[pos + 1] == '/') {
        pos += 2;  // 跳过两个斜杠
        return Token(TokenType::Operator, "//", 2, Associativity::Left);
    }

    char c = expression[pos++];  // 读取当前字符并自增指针

    // 判断字符类型并创建相应 Token
    switch (c) {
    case '+': return Token(TokenType::Operator, "+", 1, Associativity::Left);
    case '-': return Token(TokenType::Operator, "-", 1, Associativity::Left);
    case '*': return Token(TokenType::Operator, "*", 2, Associativity::Left);
    case '/': return Token(TokenType::Operator, "/", 2, Associativity::Left);
    case '%': return Token(TokenType::Operator, "%", 2, Associativity::Left);
    case '^': return Token(TokenType::Operator, "^", 3, Associativity::Right);
    case '!': return Token(TokenType::Operator, "!", 4, Associativity::Right);
    case '(': return Token(TokenType::LeftParen, "(");
    case ')': return Token(TokenType::RightParen, ")");
    default:
        throw runtime_error(string("未知符号 ") + c);  // 未知字符错误
    }
}

bool Tokenizer::is_UMC(const vector<Token>& tokens) {
    // 如果是表达式开头，或前一个是运算符或左括号，则当前负号为一元
    if (tokens.empty()) return true;
    Token last = tokens.back();
    return last.is_ope() || last.is_LP();
}

bool Tokenizer::is_dig(char c) const {
    // 判断是否为数字字符
    return std::isdigit(static_cast<unsigned char>(c));
}

bool Tokenizer::is_let(char c) const {
    // 判断是否为英文字母
    return std::isalpha(static_cast<unsigned char>(c));
}

bool Tokenizer::is_OpeCh(char c) const {
    // 判断是否为合法的运算符字符
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}