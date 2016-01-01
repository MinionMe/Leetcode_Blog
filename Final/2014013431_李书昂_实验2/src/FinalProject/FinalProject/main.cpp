/**************************************************************************

Copyright:MyCompany

Author: 李书昂

Date:2015-11-04

Description:实现网页获取、解析、提取音乐信息、分词、打印等功能

**************************************************************************/


#include "Socket.h"
#include "CharString.h"
#include "Stack.h"
#include "CharStringLink.h"
#include "DoHtml.h"
#include "dictionary.h"
using namespace std;

int main()
{ 
/*	EnableMemLeakCheck();*/
	DicWords m_dic;
	Html m_html;
	int taskId = 3;
	clock_t start,end,c1,c2;
	start = clock();
	m_dic.initDictionaryInfo(); 
	m_html.getFilesName(m_dic.fileDir_String);
	m_html.getSonginfo(m_dic.fileDir_String,m_dic);
	m_html.buildInvertedDocument();
	switch (taskId)
	{
	case 1:
		c1 = clock();
		cout << "开始进行搜索功能" << endl;
		m_html.msearchBatch(); // 批量搜索
		c2 = clock();
		printf("搜索耗时:%fs\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
		break;
	case 2:
		c1 = clock();
		cout << "开始进行推荐功能" << endl;
		m_html.recommendBatch(); // 批量推荐
		c2 = clock();
		printf("推荐耗时:%fs\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
		break;
	case 3:
		ServeOn(m_html);
	default:
		break;
	}
	end = clock();
	printf("总计耗时:%fs\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}	

