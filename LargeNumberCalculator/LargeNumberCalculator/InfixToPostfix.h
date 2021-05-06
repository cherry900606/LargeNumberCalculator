#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Integer.h"
#include "Decimal.h"
using namespace std;

int operatorPriorityInInput(char c);
int operatorPriorityInStack(char c);
bool isOperator(char c);
bool ispriority(char input, char stack);
string Postorder(string inorder);
bool chooseMode(string input);
string basicCalculate(string input);

class Calculate
{
public:
	Integer calculate(string input);
};
