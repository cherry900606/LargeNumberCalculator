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
			// 削掉"Set "
			input.erase(0, 4);
			stringstream ss(input);
			// 字串切割
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
				cout << "輸入錯誤!" << endl;
			}
		}
		else if (input.find("=") != input.npos) // 輸入格式: A=1+5   (不要有空白，以防錯誤!!)
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
		else // 輸入為運算式
		{
			Calculate computer;
			input = Postorder(input);
			bool mode = chooseMode(input);
			if (mode == 1) // 比較複雜的情況
			{
				Integer result = computer.calculate(input);
				cout << result << endl;
			}
			else // 簡單版
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
	cout << "已儲存的Integer:" << endl;
	Integer I;
	Decimal D;
	for (auto it : I.allInteger)
		cout <<  it.first << " = " << it.second << endl;
	cout << endl;
	cout << "----------" << endl;
	cout << "已儲存的Decimal: " << endl;
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