#pragma once
#include <iostream>
#include <vector>
using namespace std;

class NumberObject
{
public:
	friend ostream& operator<<(ostream& out,NumberObject& object);
	virtual void output() = 0;

};