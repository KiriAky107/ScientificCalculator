#include <iostream>
#include<string>
#include "Calc.h"

using namespace std;

int main() {
    string input;
    cout << "��ѧ������ (���� q �˳�)��\n";

    while (true) {
        cout << "���ʽ > ";
        getline(cin, input);

        if (input == "q" || input == "quit")
            break;

        double result;
        if (Calc::safeEval(input, result)) {
            cout << "= " << result << endl;
        }
        else {
            cout << "[����] ���ʽ�޷�����\n";
        }
    }

    cout << "��лʹ�ã��ټ���" << endl;
    return 0;
}
