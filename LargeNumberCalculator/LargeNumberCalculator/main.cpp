#include <iostream>
#include <sstream>
#include "Integer.h"
#include "Decimal.h"
#include "InfixToPostfix.h"
#include "NumberObject.h"
using namespace std;

void update();
void showNowVariable();
void welcome();
int main()
{

	//---------------------------//
	/*Integer i = "12345";
	Decimal d = "0.4 * 3";
	cout << i << endl << d << endl;*/
	//---------------------------//
	
	//--------------------------//
	//Integer i = "123 + 2*4";
	//Decimal d = "123.3";
	//vector<NumberObject*> nums;
	//nums.push_back(&i);
	//nums.push_back(&d);
	//for (const auto& num : nums)
	//	cout << *num << endl;

	//--------------------------//



	//welcome();
	string input;
	while (getline(cin, input))
	{
		if (input == "")
		{
			continue;
		}
		// Set Integer or Decimal
		if (input.substr(0, 3) == "Set")
		{
			string expression, variableName, type, ignore, temp;
			// �d��"Set "
			input.erase(0, 4);
			stringstream ss(input);
			// �r�����
			ss >> type;
			getline(ss, variableName, '=');
			ss >> expression;
			while (ss >> temp)
			{
				expression += temp;
			}
			variableName.erase(0, 1);
			if (variableName.back() == ' ')
				variableName.pop_back();
			if (type == "Integer")
			{
				Integer I(expression);
				expression = Postorder(expression);
				Calculate computer;
				I.allInteger[variableName] = basicCalculate(expression);
				
			}
			else if (type == "Decimal")
			{
				Decimal D(expression);
				D.allDecimal[variableName] = expression;
			}
			else
			{
				cout << "��J���~!" << endl;
			}
		}
		else if (input.find("=") != input.npos) // ��J�榡: A=1+5   (���n���ťաA�H�����~!!)
		{
			int assignmentPos = input.find_first_of("=");
			string variableName = input.substr(0, assignmentPos);
			input.erase(0, assignmentPos + 1);
			input = Postorder(input);
			Calculate computer;
			Integer result;
			result = basicCalculate(input);
			if (result.errorType == -1)
			{
				result.allInteger[variableName] = result;
			}
		}
		else // ��J���B�⦡
		{
			Calculate computer;
			input = Postorder(input);
			bool mode = chooseMode(input);
			if (mode == 1) // ������������p
			{
				Integer result = computer.calculate(input);
				cout << result << endl;
			}
			else // ²�檩
			{
				cout << basicCalculate(input) << endl;
			}

		}
		update();
	}

	
	return 0;
}

void update()
{
	system("pause");
	system("cls");
	showNowVariable();
}
void showNowVariable()
{
	cout << "�w�x�s��Integer:" << endl;
	Integer I;
	Decimal D;
	for (auto it : I.allInteger)
		cout <<  it.first << " = " << it.second << endl;
	cout << endl;
	cout << "----------" << endl;
	cout << "�w�x�s��Decimal: " << endl;
	for (auto it : D.allDecimal)
		cout <<  it.first << " = " << it.second << endl;
	cout << endl << endl;
}
void welcome()
{
	for (int i = 0; i < 50; i++)
	{
		cout << endl << endl << "\t";
		for (int j = 0; j < i; j+=2)
			cout << " ";
		cout << "~~~Welcome to the large number calculator~~~" << endl;
		system("cls");
	}
}