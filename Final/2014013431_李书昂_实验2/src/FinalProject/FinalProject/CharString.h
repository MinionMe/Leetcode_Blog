/**************************************************************************

Copyright:MyCompany

Author: ���鰺

Date:2015-11-04

Description:ʵ��CharString���Լ���������

**************************************************************************/

#ifndef CHARSTRING_H
#define CHARSTRING_H
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// CharString--����ʵ��string��Ļ�������
class CharString
{
public:
	CharString() :m_ch(NULL), m_length(0){};
	CharString(const CharString &other);                 //��ֵ���캯��(String)  
	CharString operator=(const CharString& other);       //operator=  
	CharString operator+(const CharString &other)const;  //operator+  
	bool operator==(const CharString&);              //operator==  
	bool operator<(const CharString&) const;
	char& operator[](int);              //operator[]  
	size_t size(){ return m_length; };  //�ַ����ĳ��Ⱥ���
	void charToCharString(char *ch);    //char* ת��Ϊ CharString
	void StringToCharString(string str);   //stringת��Ϊ CharString
	CharString* subString(int a, int length);  //�ַ�����ȡ����
	~CharString(){ delete[]m_ch; }
	// 	int Indexof(char *aimStr);               //�ַ���ƥ�亯��
	friend istream& operator>>(istream&, CharString&);          //�������������
	friend ostream& operator<<(ostream&, const CharString&);     //�������������
	void eraseLine(int a, int b);
	int Index_KMP(CharString &aimStr);
	void get_next(CharString &T, int next[]);
public:
	char *m_ch;               //�ַ���
	int m_length;             //����
};

#endif // !CHARSTRING_H