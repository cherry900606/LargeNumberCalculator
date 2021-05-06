#pragma once
#include <iostream>
#include <map>
#include "NumberObject.h"
#include "Integer.h"
using namespace std;

class Decimal: public NumberObject, public Integer
{
public:
	Decimal();
	Decimal(string input);
	Decimal(const char input[]);

	Decimal operator+(Decimal& rhs);
	Decimal operator-(Decimal& rhs);
	Decimal operator*(Decimal& rhs);
	Decimal operator/(Decimal& rhs);

	friend ostream& operator<< (ostream& out, Decimal& d);
	friend istream& operator>> (istream& out, Decimal& d);
	virtual void output();

	string pow(string base, string exp);

	static map<string, Decimal> allDecimal;

	string number;
};