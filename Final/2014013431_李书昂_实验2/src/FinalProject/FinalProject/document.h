/**************************************************************************

Copyright:MyCompany

Author: 李书昂

Date:2015-11-04

Description:实现Document类以及基本操作

**************************************************************************/

#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

class Document
{
public:
	int MusicID;                   //文件ID
	int times;                     //出现次数
	int searchWord_Num;             //此文件含搜索关键词的个数
	Document *next;
	Document() :MusicID(0), times(0), next(0), searchWord_Num(0){};
	Document& operator=(const Document& other);
	void printDocument(fstream &outfile);
// 	~Document(){ delete next; }
};
void swapDoc(Document &a, Document &b);            
Document* combineDocuments(Document *doc1, Document *doc2);    //归并链表


#endif // !DOCUMENT_H