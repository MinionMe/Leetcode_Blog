/*************************************************************************
*
* Copyright (c) 2015 by LSA All Rights Reserved
*
* FILENAME:  BTree.h
*
* PURPOSE : B树
*
* AUTHOR  :  李书昂
*
**************************************************************************/

#ifndef BTREE_H
#define BTREE_H
#include<iostream>
using namespace std;
#include "wordNode.h"
#include "CharString.h"
class CharString;

//字符串和文档链表
typedef pair<CharString, wordNode*> mapNode;
// 一个 BTree 节点
class BTreeNode
{
	mapNode *keys;  // 关键字的数组
	BTreeNode **m_child; // 孩子节点指针数组
	int n;     // 当前节点关键字的数量
	bool isLeaf; // 是否是叶子节点
	int t;      //度数
public:
	BTreeNode(int _t,bool _leaf);   // 构造函数
	// 遍历B树
	void traverse_sort();
	//在B树中查找 k
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
// B树类
class BTree
{
	BTreeNode *root; // 指向根节点
	static const int T = 5;                  //B树的最小度数  
	static const int KEY_MAX =  2 * T - 1;        //节点包含关键字的最大个数  
	static const int KEY_MIN = T - 1;          //非根节点包含关键字的最小个数  
	static const int CHILD_MAX = KEY_MAX + 1;  //孩子节点的最大个数  
	static const int CHILD_MIN = KEY_MIN + 1;  //孩子节点的最小个数  
public:
	// 构造函数
	BTree() :root(0){};
	// 遍历树
	void traverse();
	// 查找
	wordNode* searchWord(CharString &k);                   //搜索word
	void insert(mapNode k);                                 //插入mapNode
	BTreeNode *BTree_delete(BTreeNode *root,CharString &target);            //b树删除
	void BTree_delete_nonone(BTreeNode *root, CharString &target);          
	mapNode BTree_searchMax(BTreeNode *root);                           //搜索最大的节点
	mapNode BTree_searchMin(BTreeNode *root);                          //搜索最小的节点
	BTreeNode *BTree_delete(CharString &target);                       
	void BTree_shiftToRight(BTreeNode *root, int pos, BTreeNode *y, BTreeNode *z);          
	void BTreeShiftToLeft(BTreeNode *root, int pos, BTreeNode *y, BTreeNode *z);
	void BTreeMergeChild(BTreeNode *root, int pos, BTreeNode *y, BTreeNode *z);
};


#endif // !BTREE_H
