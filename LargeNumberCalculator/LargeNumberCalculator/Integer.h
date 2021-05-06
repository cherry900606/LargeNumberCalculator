#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "NumberObject.h"
using namespace std;

// 整數就是分母為1的分數
class Integer : public NumberObject
{
public:
	Integer();
	Integer(string input);
	Integer(const char input[]);

	Integer operator+(Integer& rhs);
	Integer operator-(Integer& rhs);
	Integer operator*(Integer& rhs);
	Integer operator/(Integer& rhs);

	friend ostream& operator<< (ostream & out, Integer & integer);
	friend istream& operator>> (istream& out, Integer& integer);
	virtual void output();

	Integer pow(Integer base, Integer exp);

	// ref: https://www.geeksforgeeks.org/factorial-large-number/
	Integer factorial(string n); // n!
	friend int multiply(int x, int res[], int res_size);

	// sqrt(s)
	string squareRoot(string s);

	static map<string,Integer> allInteger;

	// only compare string number part, no sign compare
	bool operator>(Integer rhs);
	bool operator>=(Integer rhs);

	// data
	string number;
	bool isNegative;
	int errorType;
};