#pragma once
#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include<iostream>
using namespace std;

class Rational
{
private:
	int number; //���������
	int denom; //�����������

	void siplify(); //������� ���������

public:
	//3 ������������
	Rational();
	Rational(int number);
	Rational(int number, int denom);

	//�������� ����������� � ������������
	Rational& operator +=(const Rational& r);
	Rational operator +(const Rational& r) const;

	//�������� �������� ������, ������ � ���������
	Rational& operator -=(const Rational& r);
	Rational operator -() const;
	Rational operator -(const Rational& r) const;

	//�������� ���������
	Rational& operator *=(const Rational& r);
	Rational operator *(const Rational& r);

	//�������� �������
	Rational& operator /=(const Rational& r);
	Rational operator /(const Rational& r) const;

	//�������� ����������� � ������������ ����������
	Rational& operator ++();
	Rational operator ++(int);

	//�������� ���������
	bool operator ==(const Rational& r) const;
	bool operator !=(const Rational& r) const;

	//�������� �������� � int � double
	operator int() const;
	operator double() const;

	//�������� ����� ������
	friend istream& operator >>(istream& in, Rational& r);
	friend ostream& operator <<(ostream& out, const Rational& r);
};

#endif