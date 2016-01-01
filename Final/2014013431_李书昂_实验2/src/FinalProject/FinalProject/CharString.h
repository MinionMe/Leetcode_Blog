/**************************************************************************

Copyright:MyCompany

Author: 李书昂

Date:2015-11-04

Description:实现CharString类以及基本操作

**************************************************************************/

#ifndef CHARSTRING_H
#define CHARSTRING_H
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// CharString--重新实现string类的基本功能
class CharString
{
public:
	CharString() :m_ch(NULL), m_length(0){};
	CharString(const CharString &other);                 //赋值构造函数(String)  
	CharString operator=(const CharString& other);       //operator=  
	CharString operator+(const CharString &other)const;  //operator+  
	bool operator==(const CharString&);              //operator==  
	bool operator<(const CharString&) const;
	char& operator[](int);              //operator[]  
	size_t size(){ return m_length; };  //字符串的长度函数
	void charToCharString(char *ch);    //char* 转化为 CharString
	void StringToCharString(string str);   //string转化为 CharString
	CharString* subString(int a, int length);  //字符串截取函数
	~CharString(){ delete[]m_ch; }
	// 	int Indexof(char *aimStr);               //字符串匹配函数
	friend istream& operator>>(istream&, CharString&);          //重载输入输出流
	friend ostream& operator<<(ostream&, const CharString&);     //重载输入输出流
	void eraseLine(int a, int b);
	int Index_KMP(CharString &aimStr);
	void get_next(CharString &T, int next[]);
public:
	char *m_ch;               //字符串
	int m_length;             //长度
};

#endif // !CHARSTRING_H