##Updata
更新反三角函数的定义域判定，取整函数floor、ceil和round和阶乘运算的支持，同时更新变量暂存计算

# 数据结构课设

## ——计算器的双栈类实现

## 一、总体架构

### 1.数据结构：

##### 双栈结构（操作数栈+运算符栈）

操作数栈：用于后缀表达式求值时的数据储存。

运算符栈：用于中缀表达式向后缀表达式转换时的运算符存储

### 2.基本框架：

中缀表达式->中缀转后缀->后缀表达式->后缀表达式求值

### 3.方法实现：

#### (1).表达式解析方法（Tokenizer类）

功能：将字符串形式的数学表达式拆解为基本单元（token），包括数字、运算符、括号、函数名等。

输出：Token序列（如["3","+","sin","(","2","*","5",")"]）

#### (2).表达式转换方法（InfixToPostfix类）

功能：基于逆波兰表示法，将中缀表达式（带优先级）转换为后缀表达式

核心：结合栈实现优先级比较、括号处理、函数名识别

输出：后缀表达式序列（如["3","2","5","*","sin","+"]）

#### (3).后缀表达式求值方法（PostfixEval类）

功能：使用操作数栈对后缀表达式逐步计算，得出最终结果。

支持：基础四则运算，基本初等函数，负号

输出：最终计算结果（double类型）

#### (4).总控协调方法(Calc类)

功能：统一调度调用表达式解析、转换、求职模块，作为对外唯一调用入口

接口：`double eval(string expression)`

支持debug、异常处理、扩展模块对接等功能



## 二、具体实现

### 0.0需要的STL库头文件

```cpp
#include <iostream>     // 标准输入输出（调试、主程序）
#include <string>       // 处理字符串表达式
#include <stack>        // 中缀转后缀、后缀求值都需用到栈
#include <vector>       // 储存 Token 序列
#include <cctype>       // isdigit, isalpha 等字符判断
#include <cmath>        // sin, cos, log 等函数计算（用于 PostfixEval）
#include <stdexcept>    // 抛出非法表达式等异常
```

### 0.1需要的自定义头文件

```cpp
#include "Token.h"             // Token 结构体
#include "Tokenizer.h"         // 表达式解析类
#include "InfixToPostfix.h"    // 中缀转后缀类
#include "PostfixEval.h"       // 后缀求值类
#include "Calc.h"              // 总控类（对外调用接口）
```



### 1.Token类

类型：数字、操作符、左括号、右括号、函数、变量

属性：

类型（enum）

内容（string）

优先级（仅运算符）

结合性（左/右）

```cpp
enum class TokenType{
    Number,
    Operator,
    LeftParen,
    RightParen,
    Function,
    Variable
};

enum class Associativity {
    Left,
    Right,
    None
};

struct Token {
    TokenType type;
    std::string value;

    // 以下属性仅对运算符或函数适用
    int precedence = -1;                     // 运算优先级（* > +）
    Associativity associativity = Associativity::None;

    // 构造函数
    Token(TokenType t, const std::string& v,
          int p = -1, Associativity assoc = Associativity::None)
        : type(t), value(v), precedence(p), associativity(assoc) {}

    // 工具函数：是否为数字
    bool isNumber() const { return type == TokenType::Number; }

    // 是否为操作符
    bool isOperator() const { return type == TokenType::Operator; }

    // 是否为函数
    bool isFunction() const { return type == TokenType::Function; }

    // 是否为左括号
    bool isLeftParen() const { return type == TokenType::LeftParen; }

    // 是否为右括号
    bool isRightParen() const { return type == TokenType::RightParen; }

    // 是否为变量（如 x、y）
    bool isVariable() const { return type == TokenType::Variable; }
};
```

### 2.Tokenizer类

方法：

`run(string expr) → vector<Token>`：表达式字符串解析主函数

`readNumber(string, int&)`：识别多位数字及小数点

`readFunction(string, int&)`：识别函数名称如 sin、cos

`handleUnaryMinus()`：识别一元负号

```cpp
class Tokenizer {
public:
    // 主函数：输入表达式字符串，输出 token 序列
    std::vector<Token> run(const std::string& expr);

private:
    // 当前处理的表达式和指针位置
    std::string expression;
    size_t pos = 0;

    // 工具函数：跳过空格
    void skipWhitespace();

    // 识别多位数字及小数点（支持负数符号）
    Token readNumber();

    // 识别函数名，如 sin, cos, log
    Token readFunction();

    // 识别变量名（可扩展，如 x, y, z）
    Token readVariable();

    // 识别符号、括号、运算符等
    Token readOperatorOrParen();

    // 判断是否需要处理一元负号
    bool isUnaryMinusContext(const std::vector<Token>& tokens);

    // 工具判断函数
    bool isDigit(char c) const;
    bool isLetter(char c) const;
    bool isOperatorChar(char c) const;
};

```

### 3.InfixToPostfix 类

方法：

run(vector<Token>) → vector<Token>：中缀转后缀主函数

precedence(Token)：判断运算符优先级

associativity(Token)：左结合/右结合判断

popUntilLeftParen()：用于处理括号结束时的栈弹出过程

```cpp
class InfixToPostfix {
public:
    // 主转换函数：将中缀表达式转换为后缀表达式
    std::vector<Token> run(const std::vector<Token>& infix);

private:
    // 返回指定运算符的优先级
    int precedence(const Token& token) const;

    // 判断运算符的结合性（左结合或右结合）
    Associativity associativity(const Token& token) const;

    // 遇到右括号时，从栈中弹出操作符直到遇到左括号
    void popUntilLeftParen(std::stack<Token>& opStack, std::vector<Token>& output);
};
```

### 4. PostfixEval 类

方法：

`run(vector<Token>) → double`：后缀表达式求值`

`applyBinaryOp(op, a, b)`：执行加减乘除幂

`applyUnaryFunction(func, x)`：执行函数（如 sin、sqrt）

```cpp
class PostfixEval {
public:
    // 主函数：对后缀表达式进行求值
    double run(const std::vector<Token>& postfix);

private:
    // 应用于二元操作符，如 +, -, *, /, ^
    double applyBinaryOp(const std::string& op, double a, double b);

    // 应用于一元基本初等函数，如 sin, cos, log
    double applyUnaryFunction(const std::string& func, double x);
};
```

包含的数学库函数

```cpp
sin();
cos();
log();
sqrt();
exp();
fabs();
pow();
```

### 5. Calc 类（对外接口）

方法：

`eval(string) → double`：用户主调用入口

`debug()`：调试辅助，可打印 token 列表、后缀表达式

`safeEval(string) → optional<double>`：异常捕获

```cpp
class Calc {
public:
    // 主接口函数：输入表达式字符串，返回计算结果
    static double eval(const std::string& expression);

    // 安全接口：带异常处理，返回 optional
    static std::optional<double> safeEval(const std::string& expression);
     // 调试函数：打印中间的 Token 序列和后缀表达式
    void debug(const std::string& expr);
};

```

### 6.main方法

```c++
#include <iostream>
#include <string>
#include "Calc.h"

int main() {
    std::string input;

    std::cout << "欢迎使用科学计算器（支持 + - * / ^ 和基本初等函数）\n";
    std::cout << "输入表达式（输入 q 退出）：\n";

    while (true) {
        std::cout << "\n>>> ";
        std::getline(std::cin, input);

        if (input == "q" || input == "Q") break;

        try {
            double result = Calc::eval(input);
            std::cout << "结果 = " << result << "\n";
        } catch (const std::exception& e) {
            std::cerr << "错误： " << e.what() << "\n";
        } catch (...) {
            std::cerr << "未知错误。\n";
        }
    }

    std::cout << "感谢使用，再见！\n";
    return 0;
}
```

