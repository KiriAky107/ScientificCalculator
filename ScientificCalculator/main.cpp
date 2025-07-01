#include <iostream>
#include<string>
#include "Calc.h"

using namespace std;

int main() {
    string input;
    cout << "科学计算器 (输入 q 退出)：\n";

    while (true) {
        cout << "表达式 > ";
        getline(cin, input);

        if (input == "q" || input == "quit")
            break;

        double result;
        if (Calc::safeEval(input, result)) {
            cout << "= " << result << endl;
        }
        else {
            cout << "[错误] 表达式无法计算\n";
        }
    }

    cout << "感谢使用，再见！" << endl;
    return 0;
}
