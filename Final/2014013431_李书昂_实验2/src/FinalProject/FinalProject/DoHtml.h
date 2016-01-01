/**************************************************************************

Copyright:MyCompany

Author: 李书昂

Date:2015-11-04

Description:实现Html类以及解析网页基本操作

**************************************************************************/


#ifndef DOHTML_H
#define DOHTML_H
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "Song.h"
#include <cstdlib>
#include <vector>
#include <io.h>
#include <map>
#include "BTree.h"
using namespace std;
typedef pair<CharString, int> PAIR;

//网页类，进行解析，分词，输出等操作
class Html
{
public:
	Song *m_song;                                       //音乐文件信息
	int num;                                           //待处理网页总数
	vector<string> files;                           //目标文件下的网页文件名
	BTree myTree;
	map<CharString, int> m_songID;
public:
	Html() :num(0), m_song(NULL){};
// 	~Html()
// 	{
// 		delete m_song;
// 	}
	void getFilesName(string path);      //获得网页个数，及文件名
	void getSonginfo(string &loc, DicWords &dic);      //解析网页，获得音乐信息
	void buildInvertedDocument();             //建立倒排文档
	void msearchBatch();                       //搜索功能
	void recommendBatch();                     //推荐功能
	void getsearchResult(fstream &outfile, string &s);       //获得搜索结果
	void getRecommendList(fstream &outfile, string &s);         //获得推荐结果
	void insertDivideWords(CharStringLink *pLink, int &_countWord, int i);     //加入分词链表
};

static bool CmpByValue(const PAIR& lhs, const PAIR& rhs);
#endif // !DOHTML_H