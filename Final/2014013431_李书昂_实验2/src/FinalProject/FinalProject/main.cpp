/**************************************************************************

Copyright:MyCompany

Author: ���鰺

Date:2015-11-04

Description:ʵ����ҳ��ȡ����������ȡ������Ϣ���ִʡ���ӡ�ȹ���

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
		cout << "��ʼ������������" << endl;
		m_html.msearchBatch(); // ��������
		c2 = clock();
		printf("������ʱ:%fs\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
		break;
	case 2:
		c1 = clock();
		cout << "��ʼ�����Ƽ�����" << endl;
		m_html.recommendBatch(); // �����Ƽ�
		c2 = clock();
		printf("�Ƽ���ʱ:%fs\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
		break;
	case 3:
		ServeOn(m_html);
	default:
		break;
	}
	end = clock();
	printf("�ܼƺ�ʱ:%fs\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}	

