#include "DoHtml.h"

bool CmpByValue(const PAIR& lhs, const PAIR& rhs) {
  return lhs.second > rhs.second;  
}  
void Html::recommendBatch()
{
	fstream infile("query2.txt");
	fstream outfile("result2.txt", ios::out);
	string s;
	while (!infile.eof())
	{
		getline(infile, s);
		if (s == "")
			break;
		getRecommendList(outfile, s);
	}
	infile.close();
	outfile.close();
	cout << "推荐完成！" << endl;
}
void Html::getRecommendList(fstream &outfile, string &s)
{
	CharString temp;
	wordNode node1, node2;
	temp.StringToCharString(s);
	int n;
	CharStringLink *p;
	if (m_songID.find(temp) != m_songID.end())
		n = m_songID[temp];
	else
	{
		outfile << "未找到输入音乐" << endl;
		return;
	}
	p = m_song[n - 1].m_divideLyrics;
	map<CharString, int> _wordNum;
	while (p)
	{
		if (_wordNum.find(p->m_string) != _wordNum.end())
			_wordNum[p->m_string]++;
		else
			_wordNum[p->m_string] = 1;
		p = p->next;
	}
	vector<PAIR> _wordNumVec(_wordNum.begin(), _wordNum.end());
	sort(_wordNumVec.begin(), _wordNumVec.end(), CmpByValue);
	int i;
	for (i = 0; i < _wordNumVec.size(); i++)
	{
		temp = _wordNumVec[i].first;
		if (i == 0)
		{
			if (myTree.searchWord(temp))
				node1 = *myTree.searchWord(temp);
		}
		else
		{
			if (myTree.searchWord(temp))
				node2 = *myTree.searchWord(temp);
			node1.m_document = combineDocuments(node1.m_document, node2.m_document);
		}
		if (i == 4)
		{
			break;
		}
	}
	if (node1.m_document != NULL)
	{
		QuickSort(node1.m_document, NULL);
		Document *d = node1.m_document;
		i = 0;
		while (d)
		{
			i++;
			if (i == 10)
			{
				outfile << "(" << d->MusicID << "," << m_song[d->MusicID - 1].m_title << ")" << endl;
				break;
			}
			if (d->MusicID == n)
			{
				i--;
				d = d->next;
				continue;
			}
			outfile << "(" << d->MusicID << "," << m_song[d->MusicID - 1].m_title << "),";
			d = d->next;
		}
	}
}
void Html::msearchBatch()
{
	fstream infile("query1.txt");
	fstream outfile("result1.txt", ios::out);
	string s;
	while (!infile.eof())
	{
		getline(infile, s);
		if (s == "")
			break;
		getsearchResult(outfile, s);
	}
	infile.close();
	outfile.close();
	cout << "搜索完成！" << endl;
}
void Html::getsearchResult(fstream &outfile, string &s)
{
	CharString temp;
	CharString *searchstr = NULL;
	wordNode node1, node2;
	temp.StringToCharString(s);
	int num = 0, i, j;
	for (i = 0, j = 0; i < temp.m_length; i++)
	{
		if (temp[i] == ' ')
		{
			num++;
			searchstr = temp.subString(j, i - j);
			if (num == 1)
			{
				if (myTree.searchWord(*searchstr))
					node1 = *myTree.searchWord(*searchstr);
			}
			else
			{
				if (myTree.searchWord(*searchstr))
					node2 = *myTree.searchWord(*searchstr);
				node1.m_document = combineDocuments(node1.m_document, node2.m_document);
			}
			delete searchstr;
			j = i + 1;
		}
	}
	num++;
	searchstr = temp.subString(j, i - j);
	if (num == 1)
	{
		if (myTree.searchWord(*searchstr))
			node1 = *myTree.searchWord(*searchstr);
	}
	else
	{
		if (myTree.searchWord(*searchstr))
			node2 = *myTree.searchWord(*searchstr);
		node1.m_document = combineDocuments(node1.m_document, node2.m_document);           //合并链表
	}
	delete searchstr;
	if (node1.m_document != NULL)
	{
		QuickSort(node1.m_document, NULL);
		node1.m_document->printDocument(outfile);
// 		Document *d = node1.m_document->next;
// 		while (d)
// 		{
// 			delete node1.m_document;
// 			node1.m_document = d;
// 			d = d->next;
// 		}
// 		delete node1.m_document;
	}
	else
		outfile << "未找到含这些词语的音乐文件" << endl;

}
void Html::buildInvertedDocument()
{
	clock_t start, end;
	start = clock();
	int _countWord = 0;
	for (int i = 0; i < 300; i++)
	{
		m_songID[m_song[i].m_title] = i + 1;
		CharStringLink *pLink = m_song[i].m_divideLyrics;	
		/*		cout << "正在加载第" << i + 1 << "音乐文件" << endl;*/
		insertDivideWords(pLink, _countWord, i);
	}
// 	CharString m;
// 	m.StringToCharString("蒲公英");
// 	myTree.BTree_delete(m);
	myTree.traverse();
	end = clock();
	printf("构建B-树耗时:%fs\n", (double)(end - start) / CLOCKS_PER_SEC);
}
void Html::insertDivideWords(CharStringLink *pLink, int &_countWord,int i)
{                                                     
	while (pLink != NULL)
	{
		mapNode node;
		node.first = pLink->m_string;
		node.second = myTree.searchWord(node.first);
		if (node.second != NULL)
		{
			node.second->m_occur++;
			if (node.second->lastDoc->MusicID != i + 1)
			{
				Document *curDoc = new Document;
				node.second->insertDocument(curDoc);
				node.second->lastDoc->MusicID = i + 1;
				node.second->m_fileNum++;
				node.second->lastDoc->times++;
			}
			else
				node.second->lastDoc->times++;
		}
		else
		{
			_countWord++;
			wordNode *temp = new wordNode;
			temp->m_ID = _countWord;
			temp->m_fileNum++;
			temp->m_occur++;
			Document *curDoc = new Document;
			temp->insertDocument(curDoc);
			temp->lastDoc->MusicID = i + 1;
			temp->lastDoc->times++;
			node.second = temp;
			myTree.insert(node);
		}
		pLink = pLink->next;
	}
}
void Html::getSonginfo(string &loc, DicWords &dic)
{
	clock_t  start, end;
	start = clock();
	loc += "\\pages_300\\";
	m_song = new Song[num];
	for (int i = 0; i < num; i++)
	{
// 		cout << "分析第" << i + 1 << "个网页" << endl;
		m_song[i].ExtractMusicInfoFromPage(loc + files[i]);
// 		cout << "对第" << i + 1 << "个网页进行分词" << endl;
		m_song[i].divideWords(dic);
		printf("\r解析网页中...... %.2f%%", (double)(i+1)/num * 100);
		fflush(stdout);  //记住 fflush，不然会缓冲。
	}
	end = clock();
	printf("\n处理网页耗时:%fs\n", (double)(end - start) / CLOCKS_PER_SEC);
}
void Html::getFilesName(string path)
{
	path += "\\pages_300";
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFilesName(p.assign(path).append("\\").append(fileinfo.name));
			}
			else
			{
				files.push_back(fileinfo.name);
				num++;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}