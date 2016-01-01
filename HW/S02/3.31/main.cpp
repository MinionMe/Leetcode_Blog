#include <iostream>
#include <string>
using namespace std;

class Solution
{
private:
	string m_s;
public:
	void isPlalindrome()
	{
		int i, j;
		cin >> m_s;
		for (i = 0, j = m_s.length() - 2; i < j;i++,j--)
		{
			if (m_s[i] != m_s[j])
			{
				cout << "false" << endl;
				return;
			}
		}
		cout << "true" << endl;
		return;
	}
};

int main()
{
	Solution solution;
	solution.isPlalindrome();
	return 0;
}

