#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution
{
public:
	stack<char> m_str;
	void isbracketsMatch(string s)
	{
		for (int i = 0; i < s.length(); i++)
		{
			switch (s[i])
			{
			case '(':
			case '[':
			case '{':
				m_str.push(s[i]);
				break;
			case ')':
			case ']':
			case '}':
				if (m_str.empty())
				{

				}
				if (isMatch(m_str.top(),s[i]))
				{
					m_str.pop();
					continue;
				}
				else
				{
					cout << "false" << endl;
					return;
				}
			default:
				break;
			}
		}
		if (m_str.empty())
		{
			cout << "true" << endl;
			return;
		}
		else
		{
			cout << "false" << endl;
			return;
		}
	}
	bool isMatch(char ch1, char ch2)
	{
		if ((ch1 == '('&&ch2 == ')') || (ch1 == '['&&ch2 == ']') || (ch1 == '{'&&ch2 == '}'))
		{
			return true;
		}
		else return false;
	}
};

int main()
{
	Solution solution;
	string s;
	getline(cin,s);
	solution.isbracketsMatch(s);
	return 0;
}