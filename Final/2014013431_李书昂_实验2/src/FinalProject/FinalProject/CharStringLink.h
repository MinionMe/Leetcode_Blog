/**************************************************************************

Copyright:MyCompany

Author: 李书昂

Date:2015-11-04

Description:实现CharStringLink类以及基本操作

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

// CharStringLink--实现字符串链表
class CharStringLink
{
public:
	CharString m_string;                 //数据域
	CharStringLink *next;                //后继
	CharStringLink *last;                //末端
public:
	CharStringLink():next(NULL),last(this){};
	CharStringLink(CharString &str);
	void insert_Link(int e, CharString &str);       //在第e个节点后插入新节点
	void insert_Link(CharString &str);              //在尾部插入新节点
	void delete_Link(int e);                        //删除第e个节点
	CharStringLink *research_Link(CharString &str);  //搜索节点，返回指针
	~CharStringLink()
	{
		delete next;
	}
};



#endif // !CHARSTRINGLINK_H