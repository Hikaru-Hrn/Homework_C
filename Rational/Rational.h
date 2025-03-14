#pragma once
#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include<iostream>
using namespace std;

class Rational
{
private:
	int number; //Числитель
	int denom; //Знаменатель

	void siplify(); //функция упращения

public:
	//3 конструктора
	Rational();
	Rational(int number);
	Rational(int number, int denom);

	//Операции прибавления и суммирования
	Rational& operator +=(const Rational& r);
	Rational operator +(const Rational& r) const;

	//Операции унарного минуса, минуса и убавления
	Rational& operator -=(const Rational& r);
	Rational operator -() const;
	Rational operator -(const Rational& r) const;

	//Операции умножения
	Rational& operator *=(const Rational& r);
	Rational operator *(const Rational& r);

	//Операции деления
	Rational& operator /=(const Rational& r);
	Rational operator /(const Rational& r) const;

	//Операции префексного и постфиксного инкремента
	Rational& operator ++();
	Rational operator ++(int);

	//Операции сравнения
	bool operator ==(const Rational& r) const;
	bool operator !=(const Rational& r) const;

	//Операции перевода в int и double
	operator int() const;
	operator double() const;

	//Операции ввода вывода
	friend istream& operator >>(istream& in, Rational& r);
	friend ostream& operator <<(ostream& out, const Rational& r);
};

#endif