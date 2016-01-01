#include "dictionary.h"

string WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen <= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;
	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;
}
wstring GetProgramDir()
{
	TCHAR exeFullPath[MAX_PATH]; // Full path
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	wstring strPath = __TEXT("");
	strPath = (wstring)exeFullPath;    // Get full path of the file
	int pos = strPath.find_last_of(L'\\', strPath.length());
	return strPath.substr(0, pos);  // Return the directory without the file name
}
SBTree GetLeft(SBTree s)
{
	if (s == NULL)
		return NULL;
	else
		return s->lchild;
}
SBTree GetRight(SBTree s)
{
	if (s == NULL)
		return NULL;
	else
		return s->rchild;
}
int GetSize(SBTree s)
{
	if (s == NULL)
		return 0;
	else
		return s->m_size;
}
bool DicWords::compareStr(char *ch1, char *ch2)
{
	int len1 = strlen(ch1), len2 = strlen(ch2);
	int len = len1 > len2 ? len2 : len1;
	for (int i = 0; i < len; i++)
	{
		if (int(ch1[i]) > int(ch2[i]))
			return true;
		else if (int(ch1[i]) < int(ch2[i]))
			return false;
		else continue;
	}
	if (len1 <= len2)
		return false;
	else
		return true;
}
void DicWords::initDictionaryInfo()
{
	clock_t start, end;
	start = clock();
	string temp;
	SBTree tempNode;
	rootNode = new SBTNode;
	wstring fileDir = GetProgramDir();
	fileDir_String = WChar2Ansi(fileDir.c_str());
	fstream infile;
	infile.open(fileDir_String + "\\´Ê¿â\\´Ê¿â.dic", ios::in);
	getline(infile, temp);
	rootNode->m_data.StringToCharString(temp);
	cout << "¼ÓÔØ´ÊµäÖÐ..." << endl;
	while (!infile.eof())                                 //ÔØÈë´Ê¿â
	{
		tempNode = new SBTNode;
		getline(infile, temp);
		tempNode->m_data.StringToCharString(temp);
		length_max = length_max < tempNode->m_data.m_length ? tempNode->m_data.m_length : length_max;
		Insert(rootNode, tempNode);
	}
	infile.close();
	infile.open(fileDir_String + "\\´Ê¿â\\stop_words_ch.txt", ios::in);
	while (!infile.eof())
	{
		getline(infile, temp);
		m_stopWords.insert(temp);
	}
	cout << "´Êµä¼ÓÔØÍê³É£¡" << endl;
	end = clock();
	printf("¼ÓÔØ´ÊµäºÄÊ±:%fs\n", (double)(end - start) / CLOCKS_PER_SEC);
	infile.close();
}
void DicWords::Left_Rotate(SBTree &x)
{
	SBTree k = x->rchild;
	x->rchild = k->lchild;
	k->lchild = x;
	k->m_size = GetSize(x);
	x->m_size = GetSize(x->lchild) + GetSize(x->rchild) + 1;
	x = k;
}
void DicWords::Right_Rotate(SBTree &y)
{
	SBTree k = y->lchild;
	y->lchild = k->rchild;
	k->rchild = y;
	k->m_size = GetSize(y);
	y->m_size = GetSize(y->lchild) + GetSize(y->rchild) + 1;
	y = k;
}
void DicWords::Maintain(SBTree &u, bool flag)//Î¬»¤ 
{
	if (u == NULL || (u->lchild == NULL &&u->rchild == NULL))
		return;
	if (flag == false)
	{
		if (GetSize(GetLeft(u->lchild)) > GetSize(u->rchild))
			Right_Rotate(u);
		else if (GetSize(GetRight(u->lchild)) > GetSize(u->rchild))
		{

			Left_Rotate(u->lchild);
			Right_Rotate(u);
		}
		else return;
	}
	else
	{
		if (GetSize(GetRight(u->rchild)) > GetSize(u->lchild))
			Left_Rotate(u);
		else if (GetSize(GetLeft(u->rchild)) > GetSize(u->lchild))
		{
			Right_Rotate(u->rchild);
			Left_Rotate(u);
		}
		else return;
	}
	Maintain(u->lchild, false);
	Maintain(u->rchild, true);
	Maintain(u, false);
	Maintain(u, true);
}
void DicWords::Insert(SBTree &u, SBTree v)//²åÈë
{
	if (u == NULL)
	{
		u = v;
		u->m_size = 1;
	}
	else
	{
		u->m_size++;
		if (compareStr(u->m_data.m_ch, v->m_data.m_ch))
		{
			Insert(u->lchild, v);
			Maintain(u, false);
		}
		else
		{
			Insert(u->rchild, v);
			Maintain(u, true);
		}
	}
}
bool DicWords::Search(SBTree &x, CharString &k)//ËÑË÷
{
	if (x == NULL)
		return false;
	else if (k == x->m_data)
		return true;
	if (compareStr(x->m_data.m_ch, k.m_ch))
		return Search(x->lchild, k);
	else
		return Search(x->rchild, k);
}