/**************************************************************************

Copyright:MyCompany

Author: ���鰺

Date:2015-11-04

Description:ʵ��Song���Լ���������

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
	CharString m_title;           //��Ŀ
	CharString m_singer;          //����
	CharString m_lyrics;          //���
	CharString m_lyricist;        //����
	CharString m_composer;        //����
	CharString m_laguage;
	CharString m_publishDate;     //��������
	CharString m_album;           //��Ƭ   
	CharStringLink* m_divideLyrics;  //�ִ�����
	Song(){ m_divideLyrics = NULL; };
	~Song(){ delete m_divideLyrics; };
	void ExtractMusicInfoFromPage(string &in_loc);  //������ҳ
	void GetTheWords(CharString *str);               //��ȡ������Ϣ
	void DealTheWords();                //����song��Ϣ����ȡ���ʣ�����
	int indexStr_KMP(CharString &str, char *des);             //�ַ���ƥ��
	void get_next(char *T, int *next);
	char* subStr(int a, char* str, int length);     //�ַ�����ȡ 
	void PrintTheHtml(string &str, string &str1);   //���song��Ϣ
	bool CompareLabel(char ch);                      //��ǩʶ��
	void divideWords(DicWords &mydic);
	void getTheDivideWords(DicWords &mydic, CharString *temp); //�ִ�
	void PrintDivideWords(string &loc, string &name); //����ִ���Ϣ
};
#endif // !SONG_H