#include "Rational.h"
#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");

    //�������� ���� ��������
    Rational a(5, 6), b(1, 6);
    cout << "a =" << a << "\t a++ =" << ++a << endl;
    cout << "a(" << a << ") *= b(" << b << ")" << endl;
    a *= b;
    cout << "a=" << a << " b=" << b << " a-b=" << a - b << endl;
    Rational c = 3;
    cout << "b=" << b << " c=" << c << " b/c=" << b / c << endl;
    Rational e(7, 8), f(5, 12);
    cout << "e=" << e << " f=" << f << " e+f=?" << endl;
    cout << "������� ��������� e/f � �������: m n" << endl;
    Rational g;
    cin >> g;
    if (e / f != g)
        cout << "�����������! e/f=" << e / f << endl << "�� �����: " << g;
    else
        cout << "���������!" << endl;
    return 0;
}