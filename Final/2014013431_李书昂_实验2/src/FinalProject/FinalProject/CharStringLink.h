/**************************************************************************

Copyright:MyCompany

Author: ���鰺

Date:2015-11-04

Description:ʵ��CharStringLink���Լ���������

**************************************************************************/

#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H
#include <iostream> 
#include<cstring>  
#include<cstdlib>  
#include<cstdio>  
#include<climits>  
#include<algorithm>  
#include "CharString.h"

// CharStringLink--ʵ���ַ�������
class CharStringLink
{
public:
	CharString m_string;                 //������
	CharStringLink *next;                //���
	CharStringLink *last;                //ĩ��
public:
	CharStringLink():next(NULL),last(this){};
	CharStringLink(CharString &str);
	void insert_Link(int e, CharString &str);       //�ڵ�e���ڵ������½ڵ�
	void insert_Link(CharString &str);              //��β�������½ڵ�
	void delete_Link(int e);                        //ɾ����e���ڵ�
	CharStringLink *research_Link(CharString &str);  //�����ڵ㣬����ָ��
	~CharStringLink()
	{
		delete next;
	}
};



#endif // !CHARSTRINGLINK_H