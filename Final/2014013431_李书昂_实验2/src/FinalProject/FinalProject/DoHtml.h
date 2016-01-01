/**************************************************************************

Copyright:MyCompany

Author: ���鰺

Date:2015-11-04

Description:ʵ��Html���Լ�������ҳ��������

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

//��ҳ�࣬���н������ִʣ�����Ȳ���
class Html
{
public:
	Song *m_song;                                       //�����ļ���Ϣ
	int num;                                           //��������ҳ����
	vector<string> files;                           //Ŀ���ļ��µ���ҳ�ļ���
	BTree myTree;
	map<CharString, int> m_songID;
public:
	Html() :num(0), m_song(NULL){};
// 	~Html()
// 	{
// 		delete m_song;
// 	}
	void getFilesName(string path);      //�����ҳ���������ļ���
	void getSonginfo(string &loc, DicWords &dic);      //������ҳ�����������Ϣ
	void buildInvertedDocument();             //���������ĵ�
	void msearchBatch();                       //��������
	void recommendBatch();                     //�Ƽ�����
	void getsearchResult(fstream &outfile, string &s);       //����������
	void getRecommendList(fstream &outfile, string &s);         //����Ƽ����
	void insertDivideWords(CharStringLink *pLink, int &_countWord, int i);     //����ִ�����
};

static bool CmpByValue(const PAIR& lhs, const PAIR& rhs);
#endif // !DOHTML_H