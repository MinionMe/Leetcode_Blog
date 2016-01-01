#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution
{
public:
	stack<char> m_str;
	stack<int> m_answer;
	void transformPostfix(string &exp, string &post)
	{
		int i = 0;
		m_str.push('#');
		exp.push_back('#');
		while (!m_str.empty())
		{
			if (!isOp(exp[i]))
			{
				post += exp[i];
			}
			else
			{
				switch (exp[i]) 
				{    //表达式当前字符为运算符
				case '(': 
					m_str.push(exp[i]); 
					break;
				case ')':  
					while (m_str.top() != '(')  //弹出栈中( 之前的所有操作符
					{
						post += m_str.top();
						m_str.pop();
					}
					m_str.pop();
					break;
				default: //当前字符为+,-,×,/或＃
					if (exp[i] != '#')
					{
						post += ' ';
						while (priority(exp[i]) <= priority(m_str.top()))
						{
							// 当前的操作符小于等于栈顶操作符的优先级时，将栈顶操作符写入到后缀表达式，重复此过程
							post += m_str.top();
							m_str.pop();
						}
						m_str.push(exp[i]);   //当前字符优先数高,则进栈
					}
					break;
				} // switch
			}
			if (exp[i] != '#')
			{
				i++;
			}
			else
			{
				while (m_str.top() != '#')
				{
					post += m_str.top();
					m_str.pop();
				}
				break;
			}
		}
	} 
	void calculatingPostfix(string &post)
	{
		for (int i = 0; i < post.length();i++)
		{
			if (isOp(post[i]))
			{
				int num1, num2;
				num2 = m_answer.top();
				m_answer.pop();
				num1 = m_answer.top();
				m_answer.pop();
				m_answer.push(calculatingOp(num1, num2, post[i]));
			}
			else
			{
				int temp_answer = post[i] - '0';
				while (!isOp(post[i + 1]))
				{
					temp_answer = temp_answer * 10 + post[++i] - '0';
				}
				m_answer.push(temp_answer);
				if (post[i + 1] == ' ')
				{
					i++;
				}
			}
		}
		cout << m_answer.top() << endl;
		return;
	}
	int calculatingOp(int num1, int num2, char ch)
	{
		switch (ch)
		{
		case '+':
			return num1 + num2;
			break;
		case '-':
			return num1 - num2;
			break;
		case '*':
			return num1 * num2;
			break;
		case '/':
			return num1 / num2;
			break;
		default:
			break;
		}
	}
	bool isOp(char ch)
	{
		if (ch <= '9'&&ch >= '0' )
		{
			return false;
		}
		else return true;
	}
	int priority(char ch)
	{
		switch (ch)
		{
		case '#':
			return -1;
			break;
		case '(':
			return 0;
			break;
		case '+':
		case '-':
			return 1;
			break;
		case '*':
		case '/':
			return 2;
			break;
		default:
			return -1;
			break;
		}
	}
};

int main()
{
	string exp;
	string post;
	Solution solution;
	getline(cin, exp);
	solution.transformPostfix(exp, post);
	solution.calculatingPostfix(post);
	return 0;
}