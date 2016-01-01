/**************************************************************************

Copyright:MyCompany

Author: ���鰺

Date:2015-11-04

Description:ʵ��Document���Լ���������

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
	int MusicID;                   //�ļ�ID
	int times;                     //���ִ���
	int searchWord_Num;             //���ļ��������ؼ��ʵĸ���
	Document *next;
	Document() :MusicID(0), times(0), next(0), searchWord_Num(0){};
	Document& operator=(const Document& other);
	void printDocument(fstream &outfile);
// 	~Document(){ delete next; }
};
void swapDoc(Document &a, Document &b);            
Document* combineDocuments(Document *doc1, Document *doc2);    //�鲢����


#endif // !DOCUMENT_H