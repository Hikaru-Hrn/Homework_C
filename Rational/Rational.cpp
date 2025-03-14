#include "Rational.h"

//Конструкторы
Rational::Rational()
{
	number = 0;
	denom = 1;
}

Rational::Rational(int number, int denom)
{
	this->number = number;
	this->denom = denom;
}

Rational::Rational(int number)
{
	this->number = number;
	denom = 1;
}

//Операции
Rational& Rational::operator +=(const Rational& r)
{
	number = (number * r.denom + denom * r.number);
	denom *= r.denom;
	siplify();
	return *this;
}

Rational Rational::operator +(const Rational& r) const
{
	Rational res(*this);
    res += r;
	res.siplify();
    return res;
}

Rational Rational::operator -() const
{
	Rational res(-number, denom);
	return res;
}

Rational Rational::operator -(const Rational& r) const
{
	Rational res(*this);
	res -= r;
	res.siplify();
	return res;
}

Rational& Rational::operator -=(const Rational& r) {
	return (*this += (-r));
}

Rational& Rational::operator *=(const Rational& r)
{
	number *= r.number;
	denom *= r.denom;
	siplify();
	return *this;
}

Rational Rational::operator *(const Rational& r)
{
	Rational res(*this);
	res *= r;
	res.siplify();
	return res;

}

Rational& Rational::operator /=(const Rational& r)
{
	if (r.number == 0) {
		throw runtime_error("Division by zero");
	}
	number *= r.denom;
	denom *= r.number;
	return *this;
}

Rational Rational::operator /(const Rational& r) const
{
	if (r.number == 0) {
		throw runtime_error("Division by zero");
	}
	Rational res(*this);
	res /= r;
	res.siplify();
	return res;
}

//Инкремент префиксный и постфиксный
Rational& Rational::operator ++()
{
	number += denom;
	siplify();
	return *this;
}
Rational Rational::operator ++(int)
{
	Rational r(*this);
	number += denom;
	siplify();
	return r;
}

//Операции сравнения
bool Rational::operator ==(const Rational& r) const
{
	return (number == r.number) && (denom == r.denom);
}
bool Rational::operator !=(const Rational& r) const
{
	return !(*this == r);
}

//Операции перевода
Rational::operator int() const
{
	return number / denom;
}
Rational::operator double() const
{
	return ((double)number) / denom;
}

//Операции ввода вывода
istream& operator >>(istream& in, Rational& r)
{
	in >> r.number >> r.denom;
	r.siplify();
	return in;
}
ostream& operator <<(ostream& out, const Rational& r) {
	Rational temp(r);
	temp.siplify();
	out << temp.number << "/" << temp.denom;
	return out;
}

//Функция упрощения
void Rational::siplify() {
	if (denom < 0)
	{
		number = -number;
		denom = -denom;
	}
	for (int i = 2; i <= abs(denom) && i <= abs(number); i++)
		if (number % i == 0 && denom % i == 0)
		{
			number /= i;
			denom /= i;
			i--;
		}
}