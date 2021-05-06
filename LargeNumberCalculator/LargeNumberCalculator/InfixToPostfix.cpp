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

//�������Ǫ����|�B��l�u����
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

//�^�ǬO�_���B��l
bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '!')
		return true;
	else
		return false;
}

//�P�_��B��l�O�_�u��
bool ispriority(char input, char stack)
{
	if (operatorPriorityInInput(input) > operatorPriorityInStack(stack))
		return true;
	else
		return false;
}

//��������
string Postorder(string inorder)
{
	//�h���h�l���ť���
	for (int i = 0; i < (int)inorder.length(); i++)
	{
		if (inorder[i] == ' ')
		{
			inorder.erase(i, 1);
			i--;
		}
	}
	string stack;	//���|�B��l
	string ans;		//��Ǫ�ܪk
	bool isBlank = false;	//�x�s�O�_�w�g��X���j�Ÿ���

	for (int i = 0; i < (int)inorder.length(); i++)
	{
		//�p�G�O�B��l...
		if (isOperator(inorder[i]))
		{
			isBlank = false;	//���]���j�Ÿ�

			//�P�O�O���t���٬O�[��
			if (inorder[i] == '-' || inorder[i] == '+')
			{
				if (i == 0 || (isOperator(inorder[i - 1]) && inorder[i - 1] != ')' && inorder[i - 1] != '!'))
				{
					if (inorder[i] == '-')	//�p�G�O�t���N��J@�N���A���������L��
						stack.push_back('@');
					continue;
				}
			}
			//�Y�B��l���|���šA�hpush
			if (stack.size() == 0)
			{
				stack.push_back(inorder[i]);
			}
			//�Y�J���A���ݯS�O�B�z
			else if (inorder[i] == ')')
			{
				//����e�A���X�{�e�A����|��pop�X��
				while (!(stack.back() == '('))
				{
					ans += stack.back();
					ans += " ";
					stack.pop_back();
				}
				//�A�����ο�X�A��pop
				stack.pop_back();
			}
			//�Y�O�u���פj����|�����B��l�A�hpush�i�h
			else if (ispriority(inorder[i], stack.back()))
			{
				stack.push_back(inorder[i]);
			}
			//�Y�O�Ҥ��ŦX�A�h�N�B��lpop�X�@��A�����J�B��l�u���פj����|
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
		//�p�G�O�B�⤸�A������X
		else
		{
			//�p�G�٬O�P�@�ӹB�⤸�A����ť��䮳��
			if (isBlank)
				ans.pop_back();
			ans += inorder[i];
			ans += " ";
			isBlank = true;
		}
	}
	//���J�����A�N���|�����B��l��pop�X��
	for (; !stack.empty();)
	{
		if (stack.back() != '(' && stack.back() != ')')
		{
			ans += stack.back();
			ans += " ";
		}
		stack.pop_back();
	}
	//�̫�p�G�S���ť���A�ɤW
	if (ans[(int)ans.length() - 1] != ' ')
		ans += ' ';
	return ans;
}
bool chooseMode(string input) // �ھڿ�J�B�⦡�A�M�w�έ���calculate
{
	bool advanceOperator = 0, floatingPoint = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '^' || input[i] == '!')
			advanceOperator = 1;
		if (input[i] == '.')
			floatingPoint = 1;
	}

	if (advanceOperator) // �� ^ �� !
		return 1;
	if (floatingPoint) // ²�檩 & �B�I��
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
				if(isalpha(temp[0])) // �ܼ�
				{
					Integer I;
					I = I.allInteger[temp];
					stack.push_back(stod(I.number));
				}
				else // �@��Ʀr
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
	int l = result.size() - pos; // �ثe���X��
	for (int i = 0; i < 100 - l; i++) // �n�p���I��@�ʦ�
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
					if (stack[stack.size() - 1].number == "0" || stack[stack.size() - 1].isNegative) // "���~�A�������������!!"
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
				if (isalpha(temp[0])) // �ܼ�
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
					else if (!I.allInteger.count(temp)) // �ܼƤ��s�b
					{
						I.errorType = 5;
						return I;
					}
					
				}
				else // �@��Ʀr
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