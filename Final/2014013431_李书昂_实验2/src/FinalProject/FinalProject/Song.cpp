#include "Song.h"


void Song::ExtractMusicInfoFromPage(string &in_loc)
{
	ifstream infile(in_loc, ios::in);
	CharString *content = new CharString;     //网页字符串
	string temp, str_content;
	while (!infile.eof())
	{
		getline(infile, temp);
		str_content += '\n';
		str_content += temp;
	}
	content->StringToCharString(str_content);
	infile.close();
	GetTheWords(content);
}
bool Song::CompareLabel(char ch)              //标签识别
{
	switch (ch)
	{
	case 'h':
	case 'l':
	case 't':
		return true;
		break;
	default:
		return false;
		break;
	}
}
void Song::GetTheWords(CharString *str)
{
	Stack staString;        //标签栈
	CharString temp1, temp2, *taget_area = NULL;  //需截取字符串
	CharString *temp_info = NULL;   //读取标签
	int a0, a1;              //截取字符串位置
	int label_flag = 0;      //标示当前栈内是否有标签
	int song_flag = 0;       //标示提取音乐信息的个数
	temp1.StringToCharString("song_info_area");
	a0 = str->Index_KMP(temp1);
	temp2.StringToCharString("music_list_area");
	a1 = str->Index_KMP(temp2);
	taget_area = str->subString(a0 - 1, a1 - a0);        //截取处理区域
	delete str;
	for (unsigned int i = 0; i < taget_area->size(); i++)            //通过栈解析网页
	{
		switch (taget_area->m_ch[i])
		{
		case '<':
			while (taget_area->m_ch[i] != '>')
			{
				staString.push(taget_area->m_ch[i++]);
				if (i == taget_area->size())
					break;
			}
			if (CompareLabel(staString.m_Bottom->next->next->m_str))    //识别标签
				label_flag++;
			while (staString.m_Bottom != staString.m_Top)
				staString.pop();
			break;
		case ' ':
			break;
		default:
			if (label_flag != 0)
			{
				temp_info = new CharString;
				int j = 0;
				switch (song_flag)                                    //读取m_song信息
				{
				case 0:
					temp_info->m_ch = new char[40];
					while (taget_area->m_ch[i] != '<')
					{
						temp_info->m_ch[j++] = taget_area->m_ch[i++];
						if (i == taget_area->size())
							break;
					}
					temp_info->m_ch[j] = '\0';
					temp_info->m_length = strlen(temp_info->m_ch);
					m_title.m_ch = temp_info->m_ch;
					m_title.m_length = strlen(temp_info->m_ch);
					break;
				case 1:
					temp_info->m_ch = new char[20];
					while (taget_area->m_ch[i++] != '>'){}
					while (taget_area->m_ch[i] != '<')
					{
						temp_info->m_ch[j++] = taget_area->m_ch[i++];
						if (i == taget_area->size())
							break;
					}
					temp_info->m_ch[j] = '\0';
					temp_info->m_length = strlen(temp_info->m_ch);
					m_singer.m_ch = temp_info->m_ch;
					m_singer.m_length = strlen(temp_info->m_ch);
					break;
				case 2:
					temp_info->m_ch = new char[10];
					while (taget_area->m_ch[i++] != '>'){}
					while (taget_area->m_ch[i] != '<')
					{
						temp_info->m_ch[j++] = taget_area->m_ch[i++];
						if (i == taget_area->size())
							break;
					}
					temp_info->m_ch[j] = '\0';
					temp_info->m_length = strlen(temp_info->m_ch);
					m_laguage.m_ch = temp_info->m_ch;
					m_laguage.m_length = strlen(temp_info->m_ch);
					break;
				case  3:
					temp_info->m_ch = new char[20];
					while (taget_area->m_ch[i++] != '>'){}
					while (taget_area->m_ch[i] != '<')
					{
						temp_info->m_ch[j++] = taget_area->m_ch[i++];
						if (i == taget_area->size())
							break;
					}
					temp_info->m_ch[j] = '\0';
					temp_info->m_length = strlen(temp_info->m_ch);
					m_album.m_ch = temp_info->m_ch;
					m_album.m_length = strlen(temp_info->m_ch);
					break;
				case 4:
					temp_info->m_ch = new char[20];
					while (taget_area->m_ch[i++] != '>'){}
					while (taget_area->m_ch[i] != '<')
					{
						temp_info->m_ch[j++] = taget_area->m_ch[i++];
						if (i == taget_area->size())
							break;
					}
					temp_info->m_ch[j] = '\0';
					temp_info->m_length = strlen(temp_info->m_ch);
					m_publishDate.m_ch = temp_info->m_ch;
					m_publishDate.m_length = strlen(temp_info->m_ch);
					break;
				case 5:
					temp_info->m_ch = new char[2000];
					while (taget_area->m_ch[i] != '<')
					{
						temp_info->m_ch[j++] = taget_area->m_ch[i++];
						if (i == taget_area->size())
							break;
					}
					temp_info->m_ch[j] = '\0';
					temp_info->m_length = strlen(temp_info->m_ch);
					m_lyrics.m_ch = temp_info->m_ch;
					m_lyrics.m_length = strlen(temp_info->m_ch);
					break;
				default:
					break;
				}
				song_flag++;
				label_flag--;
			}
			break;
		}
		if (song_flag == 6)
			break;
	}
	delete taget_area;
	DealTheWords();
}
void Song::DealTheWords()
{
	int seek_lyricist, seek_composer, seek_title, seek_wrong;
	for (int i = 0; i < m_title.m_length; i++)
	{
		if (m_title.m_ch[i] == '(' || m_title.m_ch[i] == '\n')
		{
			m_title.m_ch[i] = '\0';
			m_title.m_length = i;
			break;
		}
	}
	seek_title = indexStr_KMP(m_lyrics, m_title.m_ch);
	if (seek_title != -1)
	{
		int i;
		for (i = seek_title; m_lyrics.m_ch[i] != '\n'; i++){}
		m_lyrics.eraseLine(seek_title, i);
/*		seek_title = indexStr_KMP(m_lyrics, m_title.m_ch);*/
	}
	seek_lyricist = indexStr_KMP(m_lyrics, "词：");
	if (seek_lyricist == -1)
	{
		seek_lyricist = indexStr_KMP(m_lyrics, "词:");
		if (seek_lyricist != -1)
		{
			m_lyricist.m_ch = new char[20];
			int i, j = 0;
			for (i = m_lyrics.m_ch[seek_lyricist + 3] == ' ' ? seek_lyricist + 4 : seek_lyricist + 3; m_lyrics.m_ch[i] != '\n'; i++, j++)
				m_lyricist.m_ch[j] = m_lyrics.m_ch[i];
			m_lyricist.m_ch[j] = '\0';
			m_lyricist.m_length = strlen(m_lyricist.m_ch);
			m_lyrics.eraseLine(seek_lyricist, i);
		}
	}
	else
	{
		m_lyricist.m_ch = new char[20];
		int i, j = 0;
		for (i = m_lyrics.m_ch[seek_lyricist + 4] == ' ' ? seek_lyricist + 5 : seek_lyricist + 4; m_lyrics.m_ch[i] != '\n'; i++, j++)
			m_lyricist.m_ch[j] = m_lyrics.m_ch[i];
		m_lyricist.m_ch[j] = '\0';
		m_lyricist.m_length = strlen(m_lyricist.m_ch);
		m_lyrics.eraseLine(seek_lyricist, i);
	}
	seek_composer = indexStr_KMP(m_lyrics, "曲：");
	if (seek_composer == -1)
	{
		seek_composer = indexStr_KMP(m_lyrics, "曲:");
		if (seek_composer != -1)
		{
			m_composer.m_ch = new char[20];
			int i, j = 0;
			for (i = m_lyrics.m_ch[seek_composer + 3] == ' ' ? seek_composer + 4 : seek_composer + 3; m_lyrics.m_ch[i] != '\n'; i++, j++)
				m_composer.m_ch[j] = m_lyrics.m_ch[i];
			m_composer.m_ch[j] = '\0';
			m_composer.m_length = strlen(m_composer.m_ch);
			m_lyrics.eraseLine(seek_composer, i);
		}
	}
	else
	{
		m_composer.m_ch = new char[20];
		int i, j = 0;
		for (i = m_lyrics.m_ch[seek_composer + 4] == ' ' ? seek_composer + 5 : seek_composer + 4; m_lyrics.m_ch[i] != '\n'; i++, j++)
			m_composer.m_ch[j] = m_lyrics.m_ch[i];
		m_composer.m_ch[j] = '\0';
		m_composer.m_length = strlen(m_composer.m_ch);
		m_lyrics.eraseLine(seek_composer, i);
	}
	seek_wrong = indexStr_KMP(m_lyrics, "编曲");
	if (seek_wrong != -1)
	{
		int i;
		for (i = seek_wrong; m_lyrics.m_ch[i] != '\n'; i++){}
		m_lyrics.eraseLine(seek_wrong, i);
	}
	m_lyrics.m_ch[m_lyrics.m_length - 1] = '\0';
}
int Song::indexStr_KMP(CharString &str, char *des)
{
	//  1≤pos≤StrLength(S)
	int i = 0, j = 1, n = str.m_length, m = strlen(des);
	int next[100];
	get_next(des, next);
	while (i < n && j <= m)
	{
		if (j == 0 || str[i] == des[j - 1])
		{
			++i;
			++j;
		}
		// 继续比较后继字符
		else  j = next[j];         // 模式串向右移动,
		// 注意：i不变。
	}
	if (j > m)
		return  i - m;    // 匹配成功
	else
		return -1;
}
void Song::get_next(char *T, int *next) {
	// 求模式串T的next函数值并存入数组next。
	int j = 1, k = 0, m = strlen(T);
	next[1] = 0;
	while (j < m)
	{
		if (k == 0 || T[j - 1] == T[k])
		{
			++j;
			++k;
			next[j] = k;
		}
		else  k = next[k];
	}
} // get_next
char* Song::subStr(int a, char *str, int length)
{
	char *ch = NULL;
	int m_length = strlen(str);
	if (length > 0 && length < m_length - a + 1)
	{
		ch = new char[length + 1];
		for (int i = 0; i < length; i++)
			ch[i] = str[a + i];
		ch[length] = '\0';
	}
	return ch;
}
void Song::PrintTheHtml(string &str, string &str1)
{
	string temp(str1, 0, 4);
	fstream outfile(str + "\\" + temp + ".info", ios::out);
	outfile << m_title << endl;
	outfile << m_singer << endl;
	outfile << m_album << endl;
	outfile << m_publishDate << endl;
	if (m_lyricist.m_ch != NULL)
		outfile << m_lyricist << endl;
	if (m_composer.m_ch != NULL)
		outfile << m_composer << endl;
	outfile << m_lyrics << endl;
	outfile.close();
}
void Song::getTheDivideWords(DicWords &mydic, CharString *temp)
{
	int _count = 0;                       //当前分词位置
	int length = 0;                       //尾端字符个数
	CharString* s = NULL;
	int i;
	if (temp == NULL)
		return;
	while (_count < temp->m_length)
	{
		for (i = _count; i < temp->m_length; i++)                     //处理数字及西文字符
		{
			if (temp->m_ch[i] >= 48 && temp->m_ch[i] <= 126)
				continue;
			else
				break;
		}
		if (i != _count)
		{
			s = temp->subString(_count, i - _count);
			if (mydic.m_stopWords.find(s->m_ch) == mydic.m_stopWords.end())
				m_divideLyrics->insert_Link(*s);
			_count += s->m_length;
			length = 0;
			continue;
		}
		if (temp->m_length - _count - length < mydic.length_max)
		{
			if (temp->m_length - _count - length <= 0)
				return;
			s = temp->subString(_count, temp->m_length - length - _count);
			if (s->m_length == 2)                        //一个汉字，直接分词
			{
				if (mydic.m_stopWords.find(s->m_ch) == mydic.m_stopWords.end())
					m_divideLyrics->insert_Link(*s);
				_count += s->m_length;
				length = 0;
			}
			else
			{
				if (mydic.Search(mydic.rootNode, *s))
				{
					if (mydic.m_stopWords.find(s->m_ch) == mydic.m_stopWords.end())
						m_divideLyrics->insert_Link(*s);
					_count += s->m_length;
					length = 0;
				}
				else
				{
					if (s->m_ch[s->m_length - 1] >= 30 && s->m_ch[s->m_length - 1] <= 126)   //判断末尾字符是汉字还是英文
						length++;
					else
						length += 2;
					// 					delete s;
				}
			}
		}
		else
		{
			s = temp->subString(_count, mydic.length_max);
			if (mydic.Search(mydic.rootNode, *s))
			{
				if (mydic.m_stopWords.find(s->m_ch) == mydic.m_stopWords.end())
					m_divideLyrics->insert_Link(*s);
				_count += s->m_length;
			}
			else
			{
				if (s->m_ch[s->m_length - 1] >= 30 && s->m_ch[s->m_length - 1] <= 126)      //判断末尾字符是汉字还是英文
					length++;
				else
					length += 2;
				// 				delete s;
			}
		}
	}
}
void Song::divideWords(DicWords &mydic)
{
	int i, j;
	CharString* temp = NULL;
	m_divideLyrics = new CharStringLink;
	for (unsigned int i = 0; i < m_lyrics.size(); i++)
	{
		if (m_lyrics[i] == ' ')
		{
			m_lyrics[i] = '\n';
		}
	}
	for (i = 0, j = 0; i < m_lyrics.m_length; i++)
	{
		if (m_lyrics[i] == '\n')                    //对歌词逐句分词
		{
			temp = m_lyrics.subString(j, i - j);
			getTheDivideWords(mydic, temp);
			if (!temp)
				delete temp;
			j = i + 1;
		}
	}
	temp = m_lyrics.subString(j, i - 1 - j);
	getTheDivideWords(mydic, temp);
	if (!temp)
		delete temp;
}
void Song::PrintDivideWords(string &loc, string &name)
{
	string temp(name, 0, 4);
	fstream outfile(loc + "\\" + temp + ".txt", ios::out);
	CharStringLink *p;
	for (p = m_divideLyrics; p != NULL; p = p->next)
		outfile << p->m_string << endl;
	outfile.close();
}
