/**************************************************************************

Copyright:MyCompany

Author: 李书昂

Date:2015-11-04

Description:DicWords类存储词库信息，建立SBT树进行存储

**************************************************************************/


#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <wchar.h>
#include <set>
#include "CharString.h"
using namespace std;

class CharString;

//SBT(simple balanced tree)½ÚµãÀàÊµÏÖ
typedef class SBTNode
{
public:
	CharString m_data;
	int m_size;
	SBTNode *lchild, *rchild;           //lchild,rchild
	SBTNode() :lchild(NULL), rchild(NULL), m_size(1){};
	~SBTNode()
	{
		if (lchild)
		{
			delete lchild;
		}
		if (rchild)
		{
			delete rchild;
		}
	}
}SBTNode, *SBTree;
//´ÊµäÀà
class DicWords
{
public:
	SBTree rootNode; //SBT根节点
	int length_max;  //词的最大长度
	set<string> m_stopWords;   //停用词表
	string fileDir_String;
public:
	void initDictionaryInfo();        //载入词库
	DicWords() :length_max(0){};
	void Left_Rotate(SBTree &x);                //SBT左旋
	void Right_Rotate(SBTree &y);               //SBT右旋
	void Maintain(SBTree &u, bool flag);        //SBT维护
	void Insert(SBTree &u, SBTree v);           //SBT插入节点
	bool Search(SBTree &x, CharString &k);      //SBT搜索CharString k,找到返回true,否则false
	bool compareStr(char *ch1, char *ch2);      //比较ch1,ch2
	friend int GetSize(SBTree s);               //获取节点的size
	friend SBTree GetLeft(SBTree s);            //获取节点的左子树，节点为空，返回空
	friend SBTree GetRight(SBTree s);           //获取节点的右子树，节点为空，返回空
};
wstring GetProgramDir();                            //获取当前运行程序路径
string WChar2Ansi(LPCWSTR pwszSrc);                 //将wstring转化为string


#endif // !DICTIONARY_H