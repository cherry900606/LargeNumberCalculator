#include "Decimal.h"
#include "InfixToPostfix.h"
map<string, Decimal>Decimal::allDecimal = {};

Decimal::Decimal()
{
	this->number = number;
}
Decimal::Decimal(string input)
{
	this->number = input;
}
string Decimal::pow(string base, string exp)
{
	string result = "1"; // 1.0 ??
	int n = 0;

	for (int i = 0; i < exp.size(); i++)
	{
		n = n * 10 + (exp[i] - '0');
	}
	for (int i = 0; i < n; i++)
	{
		// result = result * base;
	}
	return result;
}

ostream& operator<< (ostream& out, Decimal& d)
{
	out << d.number;
	return out;
}
istream& operator>> (istream& in, Decimal& d)
{
	in >> d.number;
	return in;
}
void Decimal::output()
{
	cout << *this;
}
Decimal::Decimal(const char input[])
{
	string str = string(input);
	str = Postorder(str);
	this->number = basicCalculate(str);
}