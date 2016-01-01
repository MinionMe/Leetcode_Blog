#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution
{
public:
	stack<char> m_str;
	void stringCompare(string s)
	{
		for (int i = 0; i < s.length();i++)
		{
			if (s[i] != '&')
			{
				this->m_str.push(s[i]);
			}
			else
			{
				while (s[++i] != '@'&& !this->m_str.empty())
				{
					if (s[i] == this->m_str.top())
					{
						this->m_str.pop();
					}
					else
					{
						cout << "false" << endl;
						return;
					}
				}
				if (s[i] == '@' && this->m_str.empty())
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
		}
		
	}
};

int main()
{
	Solution solution;
	string s;
	cin >> s;
	solution.stringCompare(s);
	return 0;
}