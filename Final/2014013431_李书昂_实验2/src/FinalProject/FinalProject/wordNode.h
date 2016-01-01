/*************************************************************************
*
* Copyright (c) 2015 by LSA All Rights Reserved
*
* FILENAME:  WordNode.h
*
* PURPOSE : B树节点内部分词节点
*
* AUTHOR  :  李书昂
*
**************************************************************************/

#ifndef WORDNODE_H
#define WORDNODE_H
#include "document.h"

class wordNode
{
public:
	int m_ID;
	int m_fileNum;
	int m_occur;
	Document *m_document;
	Document *lastDoc;
	wordNode() :m_ID(0), m_fileNum(0), m_occur(0), m_document(0), lastDoc(0){};
	void sortDocument();
	void insertDocument(Document *doc);
};
void quickSort_Times(Document* h, Document* t);         //对链表进行快排
Document* GetPartion(Document* pBegin, Document* pEnd);
void QuickSort(Document* pBeign, Document* pEnd);
#endif // !WORDNODE_H
