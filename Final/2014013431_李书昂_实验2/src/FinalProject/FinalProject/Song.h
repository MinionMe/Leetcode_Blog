/**************************************************************************

Copyright:MyCompany

Author: 李书昂

Date:2015-11-04

Description:实现Song类以及基本操作

**************************************************************************/


#ifndef SONG_H
#define SONG_H
#include <iostream>
#include <fstream>
#include <string>
#include "CharString.h"
#include "CharStringLink.h"
#include "dictionary.h"
#include "Stack.h"
using namespace std;
class Stack;
class DicWords;
class Song
{
public:
	CharString m_title;           //题目
	CharString m_singer;          //歌手
	CharString m_lyrics;          //歌词
	CharString m_lyricist;        //作词
	CharString m_composer;        //编曲
	CharString m_laguage;
	CharString m_publishDate;     //发行日期
	CharString m_album;           //唱片   
	CharStringLink* m_divideLyrics;  //分词链表
	Song(){ m_divideLyrics = NULL; };
	~Song(){ delete m_divideLyrics; };
	void ExtractMusicInfoFromPage(string &in_loc);  //解析网页
	void GetTheWords(CharString *str);               //提取音乐信息
	void DealTheWords();                //处理song信息，提取作词，作曲
	int indexStr_KMP(CharString &str, char *des);             //字符串匹配
	void get_next(char *T, int *next);
	char* subStr(int a, char* str, int length);     //字符串截取 
	void PrintTheHtml(string &str, string &str1);   //输出song信息
	bool CompareLabel(char ch);                      //标签识别
	void divideWords(DicWords &mydic);
	void getTheDivideWords(DicWords &mydic, CharString *temp); //分词
	void PrintDivideWords(string &loc, string &name); //输出分词信息
};
#endif // !SONG_H