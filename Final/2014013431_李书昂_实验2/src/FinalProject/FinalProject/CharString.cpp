#include "CharString.h"


int CharString::Index_KMP(CharString &aimStr)
{
	//  1≤pos≤StrLength(S)
	int i = 0, j = 1, n = m_length, m = aimStr.m_length;
	int *next = new int[aimStr.m_length + 1];
	get_next(aimStr, next);
	while (i < n && j <= m)
	{
		if (j == 0 || m_ch[i] == aimStr[j - 1])
		{
			++i;
			++j;
		}
		// 继续比较后继字符
		else  j = next[j];         // 模式串向右移动,
		// 注意：i不变。
	}
	delete[]next;
	if (j > m)
		return  i - m;    // 匹配成功
	else
		return 0;

} // Index_KMP
void CharString::get_next(CharString &T, int *next) {
	// 求模式串T的next函数值并存入数组next。
	int j = 1, k = 0, m = T.m_length;
	next[1] = 0;
	while (j < m)
	{
		if (k == 0 || T[j - 1] == T[k])
		{
			++j;
			++k;
			next[j] = k;
		}
		else  k = next[k];
	}
} // get_next
void CharString::eraseLine(int a, int b)
{
	for (int i = 0; b + i + 1 < m_length; i++)
		m_ch[a + i] = m_ch[b + i + 1];
	m_length = m_length - (b - a + 1);
}
CharString::CharString(const CharString &other)
{
	if (other.m_length == 0)
	{
		m_ch = NULL;
		m_length = 0;
	}
	else
	{
		m_length = other.m_length;
		m_ch = new char[m_length + 1];
		strcpy(m_ch, other.m_ch);
	}
}
CharString CharString::operator=(const CharString& other)
{
	if (this != &other)
	{
		delete[]m_ch;
		m_ch = NULL;
		if (!other.m_ch)
			m_ch = 0;
		else
		{
			m_ch = new char[other.m_length + 1];
			m_length = other.m_length;
			strcpy(m_ch, other.m_ch);
		}
	}
	return *this;
}
CharString CharString::operator+(const CharString &other)const
{
	CharString newString;
	if (!m_length)
		return other;
	else if (!other.m_length)
		return *this;
	else
	{
		newString.m_ch = new char[m_length + other.m_length + 1];
		strcpy(newString.m_ch, m_ch);
		strcat(newString.m_ch, other.m_ch);
	}
	return newString;
}
bool CharString::operator==(const CharString &other)
{
	if (m_length != other.m_length)
		return false;
	return strcmp(m_ch, other.m_ch) ? false : true;
}
bool CharString::operator<(const CharString &other) const
{
	int len = m_length > other.m_length ? other.m_length : m_length;
	for (int i = 0; i < len; i++)
	{
		if (int(m_ch[i]) < int(other.m_ch[i]))
			return true;
		else if (int(m_ch[i]) > int(other.m_ch[i]))
			return false;
		else continue;
	}
	if (m_length < other.m_length)
		return true;
	else
		return false;
}
char& CharString::operator[](int a)
{
	if (a >= 0 && a <= m_length)
		return m_ch[a];
	else
		return m_ch[0];
}
void CharString::StringToCharString(string str)
{
	if (str.empty())
		m_ch = NULL;
	else
	{
		if (this->m_ch != NULL)
			delete m_ch;
		m_length = str.length();
		m_ch = new char[m_length + 1];
		for (int i = 0; i < m_length; i++)
			m_ch[i] = str[i];
		m_ch[m_length] = '\0';
	}
};
void CharString::charToCharString(char *ch)
{
	if (!ch)
		m_ch = NULL;
	else
	{
		if (this->m_ch != NULL)
			delete m_ch;
		m_length = strlen(ch);
		m_ch = new char[m_length + 1];
		strcpy(m_ch, ch);
	}
}
CharString* CharString::subString(int a, int length)
{
	CharString* newString = NULL;
	if (length > 0 && length < m_length - a + 1)
	{
		newString = new CharString;
		newString->m_length = length;
		newString->m_ch = new char[length + 1];
		for (int i = 0; i < length; i++)
			newString->m_ch[i] = m_ch[a + i];
		newString->m_ch[length] = '\0';
	}
	return newString;
}
istream& operator>>(istream& is, CharString& str)
{
	char temp[255]; //用于存储输入流  
	is >> setw(255) >> temp;
	str.m_ch = new char[strlen(temp) + 1];
	strcpy(str.m_ch, temp); //使用赋值运算符  
	str.m_length = strlen(temp);
	return is; //使用return可以支持连续使用>>运算符 
}
ostream& operator<<(ostream& os, const CharString& str)
{
	os << str.m_ch;
	return os;
}