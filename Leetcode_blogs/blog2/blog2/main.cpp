#include <iostream>
#include <stack>
#include <string>
using namespace std;




class Solution
{
public:
	int calculate(string s)
	{
		stack<int> numbers;
		stack<char> ops;
		ops.push('(');
		s.push_back(')');
		for (int i = 0; i < s.length(); i++)
		{
			switch (s[i])
			{
			case ' ':
				break;
			case '(':
				ops.push(s[i]);
				break;
			case ')':
				while (ops.top() != '(')
				{
					int num_1, num_2;
					char temp_op;
					num_2 = numbers.top();
					numbers.pop();
					num_1 = numbers.top();
					numbers.pop();
					temp_op = ops.top();
					ops.pop();
					numbers.push(calculating(num_1, num_2, temp_op));
				}
				ops.pop();
				break;
			case '+':
			case '-':
				if (!ops.empty() && ops.top() != '(')
				{
					int num_1, num_2;
					char temp_op;
					num_2 = numbers.top();
					numbers.pop();
					num_1 = numbers.top();
					numbers.pop();
					temp_op = ops.top();
					ops.pop();
					numbers.push(calculating(num_1, num_2, temp_op));
				}
				ops.push(s[i]);
				break;
			default:
				int temp_answer = s[i] - '0';
				while (isDigit(s[i + 1]))
				{
					temp_answer = temp_answer * 10 + s[++i] - '0';
				}
				numbers.push(temp_answer);
				break;
			}
		}
		return numbers.top();
	}
	bool isDigit(char a)
	{
		if (a >= '0' && a <= '9')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int calculating(int num1, int num2, char op)
	{
		switch (op)
		{
		case '+':
			return num1 + num2;
			break;
		default:
			return num1 - num2;
			break;
		}
	}
};


int main()
{
	Solution solution;
	string s;
	cin >> s;
	cout << solution.calculate(s) << endl;
	return 0;
}