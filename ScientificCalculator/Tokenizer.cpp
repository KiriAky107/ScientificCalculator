#include"Tokenizer.h"
#include<cctype>
#include<stdexcept>

using namespace std;

vector<Token> Tokenizer::run(const string& expr) {

    expression = expr;
    pos = 0;
    vector<Token> tokens;

    // ��ѭ�������ַ���ȡ���ʽ
    while (pos < expression.length()) {

        skipWhitespace();// �����հ��ַ�
        if (pos >= expression.length()) break;

        char current = expression[pos];

        // ��������ֻ�һԪ���ſ�ͷ����ȡ��������
        if (is_dig(current) || (current == '-' && is_UMC(tokens)))
            tokens.push_back(readNumber());

        // �������ĸ����ȡ�����������
        else if (is_let(current))
            tokens.push_back(readIdentifier());

        // �����ȡ������������
        else
            tokens.push_back(readOperatorOrParen());
    }

    return tokens;
}

void Tokenizer::skipWhitespace() {
    // �������пո��Ʊ���ȿհ��ַ�
    while (pos < expression.length() && isspace(expression[pos]))
        ++pos;
}

Token Tokenizer::readNumber() {
    size_t start = pos;
    bool hasDecimal = false;// ���С�����Ƿ���ֹ�

    if (expression[pos] == '-')
        ++pos;  // ����һԪ���ţ�������

    while (pos < expression.length() && (is_dig(expression[pos]) || expression[pos] == '.')) {
        if (expression[pos] == '.') {
            if (hasDecimal)
                throw runtime_error("���ָ�ʽ��Ч�����С����");// С�����ظ�����
            hasDecimal = true;
        }
        ++pos;
    }

    string numberStr = expression.substr(start, pos - start);
    return Token(TokenType::Number, numberStr);// �������� Token
}

Token Tokenizer::readIdentifier() {
    size_t start = pos;

    // ��ȡ��������ĸ�ַ������������������
    while (pos < expression.length() && is_let(expression[pos]))
        ++pos;

    string name = expression.substr(start, pos - start);

    //ʶ����������������������������Ϊ����������Ϊ������
    skipWhitespace();
    if (pos < expression.length() && expression[pos] == '(')
        return Token(TokenType::Function, name);
    else
        return Token(TokenType::Variable, name);
}

Token Tokenizer::readOperatorOrParen() {
    if (expression[pos] == '/' && pos + 1 < expression.length() && expression[pos + 1] == '/') {
        pos += 2;  // ��������б��
        return Token(TokenType::Operator, "//", 2, Associativity::Left);
    }

    char c = expression[pos++];  // ��ȡ��ǰ�ַ�������ָ��

    // �ж��ַ����Ͳ�������Ӧ Token
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
        throw runtime_error(string("δ֪���� ") + c);  // δ֪�ַ�����
    }
}

bool Tokenizer::is_UMC(const vector<Token>& tokens) {
    // ����Ǳ��ʽ��ͷ����ǰһ����������������ţ���ǰ����ΪһԪ
    if (tokens.empty()) return true;
    Token last = tokens.back();
    return last.is_ope() || last.is_LP();
}

bool Tokenizer::is_dig(char c) const {
    // �ж��Ƿ�Ϊ�����ַ�
    return std::isdigit(static_cast<unsigned char>(c));
}

bool Tokenizer::is_let(char c) const {
    // �ж��Ƿ�ΪӢ����ĸ
    return std::isalpha(static_cast<unsigned char>(c));
}

bool Tokenizer::is_OpeCh(char c) const {
    // �ж��Ƿ�Ϊ�Ϸ���������ַ�
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}