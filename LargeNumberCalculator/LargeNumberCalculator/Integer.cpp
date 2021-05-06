#include "Integer.h"
#include "InfixToPostfix.h"
map<string, Integer>Integer::allInteger = {};



bool isNumber(string s) // check this string is only a number
{
	if (s[0] == '+' || s[0] == '-')
	{
		s.erase(0, 1);
	}
	for (int i = 0; i < s.size(); i++)
	{
		if (!isdigit(s[i]) && s[i] != '.')
			return false;
	}
	return true;
}
string toInt(string s) // Integer A = "17.455", A.number = "17"
{
	if (s[0] == '-')
	{
		s.erase(0, 1);
	}
	int pos = s.size(); // if pos doesn't change, it means string is integer
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '.')
		{
			pos = i;
		}
	}
	string result;
	result = result.assign(s, 0, pos); // only int part
	return result;
}
Integer::Integer()
{
	this->number = "0";
	this->isNegative = false;
	this->errorType = -1;
}
Integer::Integer(string input)
{
	// check input string is valid
	// if invalid, the print error message
	// else if input is expression statement
	// then call function to postfix and evalute
	// assign final input to this object
	this->errorType = -1;
	if (isNumber(input))
	{
		if (input[0] == '-')
			this->isNegative = true;
		else
			this->isNegative = false;
		this->number = toInt(input);
	}
	else
	{
		// input = infixToPostfix(input)
	}
}
Integer Integer::operator+(Integer& rhs)
{
	Integer result;
	
	// 負 + 正 (= 正 - 負)
	if (this->isNegative && !rhs.isNegative)
	{
		Integer tempThis(this->number);
		result = rhs - tempThis;
	}
	// 負 + 負 (= -( |負| + |負| ) )
	else if (!this->isNegative && rhs.isNegative)
	{
		Integer tempRhs(rhs.number);
		result = *this - tempRhs;
	}
	else
	{
		string a = this->number, b = rhs.number;
		if (b.size() > a.size())
			swap(a, b);
		for (int i = 0; i < b.size(); i++)
		{
			a[a.size() - 1 - i] += b[b.size() - 1 - i] - '0';
		}
		for (int i = a.size() - 1; i > 0; i--)
		{
			if (a[i] > '9')
			{
				a[i] -= 10;
				a[i - 1]++;
			}
		}
		if (a[0] > '9')
		{
			a[0] -= 10;
			a = "1" + a;
		}
		result.isNegative = this->isNegative;
		result.number = a;
	}
	return result;
}
Integer Integer::operator-(Integer& rhs)
{
	Integer result;
	// case 1: 負 - 正
	if (this->isNegative && !rhs.isNegative)
	{
		result = Integer(this->number) + rhs;
		result.isNegative = true;
	}
	// case 2: 正 - 負
	else if (!this->isNegative && rhs.isNegative)
	{
		Integer tempRhs(rhs.number);
		result = *this + tempRhs;
	}
	// case 3: 正 - 正
	else
	{
		if (!(*this > rhs)) // rhs > this
		{
			swap(*this, rhs);
			result.isNegative = !this->isNegative;
		}
		result.number = this->number;
		for (int i = 0; i < rhs.number.size(); i++) // substract
		{
			result.number[result.number.size() - 1 - i] -= rhs.number[rhs.number.size() - 1 - i] - '0';
		}
		for (int i = result.number.size() - 1; i >= 0; i--) // borrow
		{
			if (result.number[i] < '0')
			{
				result.number[i] += 10;
				result.number[i - 1]--;
			}
		}
		for (int i = 0; i < result.number.size(); i++) // 000 -> 0
		{
			if (result.number[i] == '0')
				result.number.erase(0, 1);
			else
				break;
		}
	}
	return result;
}
Integer Integer::operator*(Integer& rhs)
{
	vector<int> result(this->number.size() + rhs.number.size(), 0); // 答案可能大小為兩數位數和
	int i_n1 = 0, i_n2 = 0;

	for (int i = this->number.size() - 1; i >= 0; i--)
	{
		int carry = 0, n1 = this->number[i] - '0'; // convert to int
		i_n2 = 0;
		for (int j = rhs.number.size() - 1; j >= 0; j--)
		{
			int n2 = rhs.number[j] - '0';
			int sum = n1 * n2 + result[i_n1 + i_n2] + carry;
			carry = sum / 10;
			result[i_n1 + i_n2] = sum % 10;
			i_n2++;
		}
		if (carry > 0) // 進位
			result[i_n1 + i_n2] += carry;
		i_n1++;
	}

	Integer answer;

	int i = result.size() - 1;
	while (i >= 0 && result[i] == 0) // 去掉開頭多餘的零
		i--;
	if (i == -1)
		answer.number = "0";
	else // 去掉多餘的零
	{
		i = result.size() - 1;
		while (i >= 0)
			answer.number += to_string(result[i--]);
		while (answer.number[0] == '0')
			answer.number.erase(0, 1);
	}
	answer.isNegative = (this->isNegative ^ rhs.isNegative); // xor
	return answer;
}
Integer Integer::operator/(Integer& rhs)
{

	Integer result;
	result.isNegative = this->isNegative ^ rhs.isNegative;
	rhs.isNegative = false; // <------------------之後再來管正負號
	if (this->number == rhs.number)
	{
		result.number = "1";
		return result;
	}
	if (*this > rhs)
	{
		Integer dividend;

		// 模擬手算除法
		for (int i = 0; i < this->number.size(); i++) 
		{
			int count = 0;
			dividend.number += this->number[i];
			while (dividend.number[0] == '0') // 去掉多餘的零
				dividend.number.erase(0, 1);
			dividend.isNegative = false; // 修正錯誤，原因不明
			while (dividend >= rhs)
			{
				dividend = dividend - rhs;
				count++;
			}
			result.number += to_string(count); // 該位元數值
		}
		while (result.number[0] == '0')
			result.number.erase(0, 1);

	}
	else // 整數除法無條件捨去
		result.number = "0";

	return result;
}
ostream& operator<<(ostream& out, Integer& integer)
{
	if (integer.errorType != -1)
	{
		if (integer.errorType == 1)
			cout << "錯誤，階乘須為正整數!!";
		else if (integer.errorType == 2)
			cout << "錯誤，不可除以0!!";
		else if (integer.errorType == 3)
			cout << "運算式不合法!!";
		else if (integer.errorType == 4)
			cout << "次方數須為0.5的倍數!!";
		else if (integer.errorType == 5)
			cout << "輸入包含不存在的變數!!";
		return out;
	}
	if (integer.isNegative && integer.number != "0") // -0 -> 0
	{
		out << "-";
		
	}
	out << integer.number;
	return out;
}
istream& operator>>(istream& in, Integer& integer)
{
	in >> integer.number;
	return in;
}

// 給階乘用的乘法
int multiply(int x, vector<int>& res, int res_size)
{
	int carry = 0;

	for (int i = 0; i < res_size; i++)
	{
		int prod = res[i] * x + carry;
		res[i] = prod % 10;
		carry = prod / 10;
	}

	while (carry)
	{
		res.push_back(carry % 10);
		carry = carry / 10;
		res_size++;
	}
	return res_size;
}
Integer Integer::factorial(string s)
{
	int n = 0;
	for (int i = 0; i < s.size(); i++)
	{
		n = n * 10 + (s[i] - '0');
	}
	vector<int> res;

	res.push_back(1);
	int res_size = 1;

	for (int x = 2; x <= n; x++)
		res_size = multiply(x, res, res_size);

	string result;
	for (int i = res_size - 1; i >= 0; i--)
	{
		result += to_string(res[i]);
	}
	Integer answer(result);
	return answer;
}
string getCountAdd(string a, string b) // 大數整數加法
{
	if (b.size() > a.size())
		swap(a, b);
	for (int i = 0; i < b.size(); i++)
	{
		a[a.size() - 1 - i] += b[b.size() - 1 - i] - '0';
	}
	for (int i = a.size() - 1; i > 0; i--) // 進位
	{
		if (a[i] > '9')
		{
			a[i] -= 10;
			a[i - 1]++;
		}
	}
	if (a[0] > '9') // 首位進位的另外處理
	{
		a[0] -= 10;
		a = "1" + a;
	}
	return a;
}
Integer Integer::pow(Integer b, Integer e)
{
	string base = b.number, exp = e.number;
	int i = base.length() - 1;
	string temp = base; //temp一直变化
	string temp_2 = "0";
	int bitcount = 0; //當前位數
	int bit = -1;//是否進位
	string* arr = new string[base.length()];//每次計算的數
	int arr_i = 0;
	for (int x = 1; x < stoi(exp); x++)//看指數次方決定做幾次
	{
		while (i != -1)//乘數位數
		{
			//temp * base
			int t1 = base[i] - 48;
			int j = temp.length() - 1;
			for (int z = 0; z < bitcount; z++)
			{
				arr[arr_i].insert(0, 1, '0');
			}
			while (j != -1)//temp的位數
			{
				int t2 = temp[j] - 48;
				if (bit == -1)//要不要進位
				{
					if (t1 * t2 >= 10)
					{
						int d = (t1 * t2) % 10;
						arr[arr_i].insert(0, 1, d + 48);
						int d_2 = (t1 * t2) / 10;
						bit = d_2;
					}
					else
					{
						int d = t1 * t2;
						arr[arr_i].insert(0, 1, d + 48);
					}
				}
				else
				{
					if ((t1 * t2) + bit >= 10)
					{
						int d = ((t1 * t2) + bit) % 10;
						arr[arr_i].insert(0, 1, d + 48);
						int d_2 = ((t1 * t2) + bit) / 10;
						bit = d_2;
					}
					else
					{
						int d = (t1 * t2) + bit;
						arr[arr_i].insert(0, 1, d + 48);
						bit = -1;
					}
				}
				j--;
			}
			if (bit != -1)
			{
				arr[arr_i].insert(0, 1, bit + 48);
				bit = -1;
			}
			//走完一圈
			//计算每一位的数，最后相加
			//temp_2=temp_2+arr[arr_i];
			temp_2 = getCountAdd(temp_2, arr[arr_i]);   // <-------這裡之後用寫好的add function
			bitcount++;
			arr_i++;
			i--;
		}
		bitcount = 0;
		temp = temp_2;
		temp_2 = "0";
		for (int z = 0; z < arr_i; z++)
		{
			arr[z] = "";
		}
		arr_i = 0;
		i = base.length() - 1;
	}

	Integer result(temp);
	if (!b.isNegative)
		result.isNegative = false;
	else
	{
		if ((e.number[e.number.size() - 1] - '0') % 2 == 1)
			result.isNegative = true;
		else
			result.isNegative = false;
	}
	return result;
}

bool Integer::operator>(Integer rhs)
{
	if (this->number.size() > rhs.number.size())
	{
		return true;
	}
	else if (this->number.size() < rhs.number.size())
	{
		return false;
	}
	for (int i = 0; i < this->number.size(); i++)
	{
		if (this->number[i] > rhs.number[i])
			return true;
		if (this->number[i] < rhs.number[i])
			return false;
	}
	return false; // euqal
}
bool Integer::operator>=(Integer rhs)
{
	if (this->number.size() > rhs.number.size())
	{
		return true;
	}
	else if (this->number.size() < rhs.number.size())
	{
		return false;
	}
	for (int i = 0; i < this->number.size(); i++)
	{
		if (this->number[i] > rhs.number[i])
			return true;
		if (this->number[i] < rhs.number[i])
			return false;
	}
	return true; // euqal
}

void Integer::output()
{
	cout << *this;
}
//Integer& Integer::operator=(string& input)
//{
//	Calculate computer;
//	input = Postorder(input);
//	*this = computer.calculate(input);
//	return *this;
//}
Integer::Integer(const char input[])
{
	Calculate computer;
	string str(input);
	str = Postorder(str);
	*this = computer.calculate(str); // 處理運算式
}