#include "InfixToPostfix.h"
#include "NumberObject.h"
#include <iomanip>
#include <sstream>

int operatorPriorityInInput(char c)
{
	if (c == '+' || c == '-')return 1;
	else if (c == '*' || c == '/')return 2;
	else if (c == '@')return 3;
	else if (c == '^')return 5;
	else if (c == '!')return 6;
	else if (c == ')')return 0;
	else if (c == '(')return 7;
	else return -1;
}

//中序轉後序的堆疊運算子優先度
int operatorPriorityInStack(char c)
{
	if (c == '+' || c == '-')return 1;
	else if (c == '*' || c == '/')return 2;
	else if (c == '@')return 3;
	else if (c == '^')return 4;
	else if (c == '!')return 6;
	else if (c == '(')return 0;
	else return -1;
}

//回傳是否為運算子
bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '!')
		return true;
	else
		return false;
}

//判斷兩運算子是否優先
bool ispriority(char input, char stack)
{
	if (operatorPriorityInInput(input) > operatorPriorityInStack(stack))
		return true;
	else
		return false;
}

//中序轉後序
string Postorder(string inorder)
{
	//去除多餘的空白鍵
	for (int i = 0; i < (int)inorder.length(); i++)
	{
		if (inorder[i] == ' ')
		{
			inorder.erase(i, 1);
			i--;
		}
	}
	string stack;	//堆疊運算子
	string ans;		//後序表示法
	bool isBlank = false;	//儲存是否已經輸出分隔符號用

	for (int i = 0; i < (int)inorder.length(); i++)
	{
		//如果是運算子...
		if (isOperator(inorder[i]))
		{
			isBlank = false;	//重設分隔符號

			//判別是正負號還是加減
			if (inorder[i] == '-' || inorder[i] == '+')
			{
				if (i == 0 || (isOperator(inorder[i - 1]) && inorder[i - 1] != ')' && inorder[i - 1] != '!'))
				{
					if (inorder[i] == '-')	//如果是負號就放入@代替，正號直接無視
						stack.push_back('@');
					continue;
				}
			}
			//若運算子堆疊為空，則push
			if (stack.size() == 0)
			{
				stack.push_back(inorder[i]);
			}
			//若遇到後括號需特別處理
			else if (inorder[i] == ')')
			{
				//直到前括號出現前，把堆疊都pop出來
				while (!(stack.back() == '('))
				{
					ans += stack.back();
					ans += " ";
					stack.pop_back();
				}
				//括號不用輸出，純pop
				stack.pop_back();
			}
			//若是優先度大於堆疊中的運算子，則push進去
			else if (ispriority(inorder[i], stack.back()))
			{
				stack.push_back(inorder[i]);
			}
			//若是皆不符合，則將運算子pop出一位，直到輸入運算子優先度大於堆疊
			else
			{
				if (stack.back() != '(' && stack.back() != ')')
				{
					ans += stack.back();
					ans += " ";
				}
				stack.pop_back();
				i--;
			}
		}
		//如果是運算元，直接輸出
		else
		{
			//如果還是同一個運算元，先把空白鍵拿掉
			if (isBlank)
				ans.pop_back();
			ans += inorder[i];
			ans += " ";
			isBlank = true;
		}
	}
	//當輸入結束，將堆疊中的運算子全pop出來
	for (; !stack.empty();)
	{
		if (stack.back() != '(' && stack.back() != ')')
		{
			ans += stack.back();
			ans += " ";
		}
		stack.pop_back();
	}
	//最後如果沒有空白鍵，補上
	if (ans[(int)ans.length() - 1] != ' ')
		ans += ' ';
	return ans;
}
bool chooseMode(string input) // 根據輸入運算式，決定用哪種calculate
{
	bool advanceOperator = 0, floatingPoint = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '^' || input[i] == '!')
			advanceOperator = 1;
		if (input[i] == '.')
			floatingPoint = 1;
	}

	if (advanceOperator) // 有 ^ 或 !
		return 1;
	if (floatingPoint) // 簡單版 & 浮點數
		return 0;
	else
		return 1;
}
string basicCalculate(string input)
{
	vector<long double> stack;
	string temp;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ')
		{
			if (temp.size() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				if (temp == "+")
				{
					stack[stack.size() - 2] += stack[stack.size() - 1];
					stack.pop_back();
				}
				else if (temp == "-")
				{
					stack[stack.size() - 2] -= stack[stack.size() - 1];
					stack.pop_back();
				}
				else if (temp == "*")
				{
					stack[stack.size() - 2] *= stack[stack.size() - 1];
					stack.pop_back();
				}
				else if (temp == "/")
				{
					stack[stack.size() - 2] /= stack[stack.size() - 1];
					stack.pop_back();
				}
				else if (temp == "@")
				{
					stack[stack.size() - 1] *= -1;
				}
			}
			else // not operator
			{
				if(isalpha(temp[0])) // 變數
				{
					Integer I;
					I = I.allInteger[temp];
					stack.push_back(stod(I.number));
				}
				else // 一般數字
				{
					stack.push_back(stod(temp));
				}
			}
			temp = "";
		}
		else
		{
			temp += input[i];
		}
	}
	stringstream ss;
	ss << fixed << setprecision(10) << stack[0];
	string result = ss.str();
	int pos = 0;
	for (int i = 0; i < result.size(); i++)
	{
		if (result[i] == '.')
		{
			pos = i;
			break;
		}
	}
	int l = result.size() - pos; // 目前有幾位
	for (int i = 0; i < 100 - l; i++) // 要小數點後一百位
	{
		result += "0";
	}
	return result;
}
Integer Calculate::calculate(string input)
{

	vector<Integer> stack;
	string temp;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ')
		{
			if (temp.size() == 1 && (isOperator(temp[0]) || temp == "@")) // operator
			{
				if (temp == "+")
				{
					if (stack.size() < 2)
					{
						Integer I;
						I.errorType = 3;
						return I;
					}
					stack[stack.size() - 2] = stack[stack.size() - 2] + stack[stack.size() - 1];
					stack.pop_back();
				}
				
				
				else if (temp == "-")
				{
					if (stack.size() < 2)
					{
						Integer I;
						I.errorType = 3;
						return I;
					}
					stack[stack.size() - 2] = stack[stack.size() - 2] - stack[stack.size() - 1];
					stack.pop_back();
				}
				else if (temp == "*")
				{
					if (stack.size() < 2)
					{
						Integer I;
						I.errorType = 3;
						return I;
					}
					stack[stack.size() - 2] = stack[stack.size() - 2] * stack[stack.size() - 1];
					stack.pop_back();
				}
				else if (temp == "/")
				{
					if (stack.size() < 2)
					{
						Integer I;
						I.errorType = 3;
						return I;
					}
					if (stack[stack.size() - 1].number == "0")
					{
						Integer I;
						I.errorType = 2;
						return I;
					}
					stack[stack.size() - 2] = stack[stack.size() - 2] / stack[stack.size() - 1];
					stack.pop_back();
				}
				else if (temp == "^")
				{
					if (stack.size() < 2)
					{
						Integer I;
						I.errorType = 3;
						return I;
					}
					if (stack[stack.size() - 1].number[0] == '0')
					{
						Integer I;
						I.errorType = 4;
						return I;
					}
					stack[stack.size() - 2] = stack[stack.size() - 2].pow(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
				}
				else if (temp == "!")
				{
					if (stack.size() < 1)
					{
						Integer I;
						I.errorType = 3;
						return I;
					}
					if (stack[stack.size() - 1].number == "0" || stack[stack.size() - 1].isNegative) // "錯誤，階乘須為正整數!!"
					{
						Integer I;
						I.errorType = 1;
						return I;
					}
					stack[stack.size() - 1] = stack[stack.size() - 1].factorial(stack[stack.size() - 1].number);
				}
				else if (temp == "@")
				{
					if (stack.size() < 1)
					{
						Integer I;
						I.errorType = 3;
						return I;
					}
					stack[stack.size() - 1].isNegative = !stack[stack.size() - 1].isNegative;
				}
			}
			else // not operator
			{
				if (isalpha(temp[0])) // 變數
				{
					Integer I;
					Decimal D;
					if (I.allInteger.count(temp))
					{
						I = I.allInteger[temp];
						stack.push_back(I);
					}
					else if (D.allDecimal.count(temp))
					{
						if (temp[0] == '-')
						{
							I.isNegative = true;
							temp.erase(0, 1);
						}
						I.number = D.allDecimal[temp].number;
						stack.push_back(I);
					}
					else if (!I.allInteger.count(temp)) // 變數不存在
					{
						I.errorType = 5;
						return I;
					}
					
				}
				else // 一般數字
				{
					Integer I(temp);
					stack.push_back(I);
				}
			}
			temp = "";
		}
		else
		{
			temp += input[i];
		}
	}
	return stack[0];
}