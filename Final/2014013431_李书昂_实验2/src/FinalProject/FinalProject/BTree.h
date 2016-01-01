/*************************************************************************
*
* Copyright (c) 2015 by LSA All Rights Reserved
*
* FILENAME:  BTree.h
*
* PURPOSE : B��
*
* AUTHOR  :  ���鰺
*
**************************************************************************/

#ifndef BTREE_H
#define BTREE_H
#include<iostream>
using namespace std;
#include "wordNode.h"
#include "CharString.h"
class CharString;

//�ַ������ĵ�����
typedef pair<CharString, wordNode*> mapNode;
// һ�� BTree �ڵ�
class BTreeNode
{
	mapNode *keys;  // �ؼ��ֵ�����
	BTreeNode **m_child; // ���ӽڵ�ָ������
	int n;     // ��ǰ�ڵ�ؼ��ֵ�����
	bool isLeaf; // �Ƿ���Ҷ�ӽڵ�
	int t;      //����
public:
	BTreeNode(int _t,bool _leaf);   // ���캯��
	// ����B��
	void traverse_sort();
	//��B���в��� k
	wordNode *searchWord(CharString &k);
	BTreeNode *searchNode(CharString &k);
	void splitChild(int i, BTreeNode *y);
	void insertNonFull(mapNode k);
	friend class BTree;
	~BTreeNode()
	{
		for (int i = 0; i <= n;i++)
		{
			delete m_child[i];
		}
		delete keys;
	}
};
// B����
class BTree
{
	BTreeNode *root; // ָ����ڵ�
	static const int T = 5;                  //B������С����  
	static const int KEY_MAX =  2 * T - 1;        //�ڵ�����ؼ��ֵ�������  
	static const int KEY_MIN = T - 1;          //�Ǹ��ڵ�����ؼ��ֵ���С����  
	static const int CHILD_MAX = KEY_MAX + 1;  //���ӽڵ��������  
	static const int CHILD_MIN = KEY_MIN + 1;  //���ӽڵ����С����  
public:
	// ���캯��
	BTree() :root(0){};
	// ������
	void traverse();
	// ����
	wordNode* searchWord(CharString &k);                   //����word
	void insert(mapNode k);                                 //����mapNode
	BTreeNode *BTree_delete(BTreeNode *root,CharString &target);            //b��ɾ��
	void BTree_delete_nonone(BTreeNode *root, CharString &target);          
	mapNode BTree_searchMax(BTreeNode *root);                           //�������Ľڵ�
	mapNode BTree_searchMin(BTreeNode *root);                          //������С�Ľڵ�
	BTreeNode *BTree_delete(CharString &target);                       
	void BTree_shiftToRight(BTreeNode *root, int pos, BTreeNode *y, BTreeNode *z);          
	void BTreeShiftToLeft(BTreeNode *root, int pos, BTreeNode *y, BTreeNode *z);
	void BTreeMergeChild(BTreeNode *root, int pos, BTreeNode *y, BTreeNode *z);
};


#endif // !BTREE_H
