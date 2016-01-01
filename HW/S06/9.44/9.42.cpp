#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

typedef enum { Leaf, Branch }NodeKind;
class TrieNode{
public:
	NodeKind kind;
	union{
		struct { char* key;}lf;
		struct { TrieNode *ptr[27]; int num; }bh;
	};
};
typedef TrieNode* TrieTree;
void InitTrieTree(TrieTree &Tr);
bool InsertNode(TrieTree &Tr, string s,int _depth);
void PrintTree(TrieTree &Tr,string &_output);
void InitBranchNode(TrieTree &Tr);
void GetOutput(string &str);
int main()
{
	TrieTree Tr;
	string _output;
	InitTrieTree(Tr);
	PrintTree(Tr,_output);
	GetOutput(_output);
	cout << _output << endl;
	return 0;
}
void InitTrieTree(TrieTree &Tr)
{
	string temp,sub_str;
	int j = 0;
	Tr = NULL;
	getline(cin, temp);
	if (temp.empty())
	{
		return;
	}
	for (int i = 0; i <= temp.length(); ++i)
	{
		if (i == temp.length()||temp[i] == ',')
		{
			sub_str = temp.substr(j,i-j);
			if (InsertNode(Tr, sub_str, 0))
				Tr->bh.num++;
			j = i + 1;
		}
	}
	for (int i = 0; i < 3;i++)
	{
		cin >> temp;
		if (InsertNode(Tr, temp, 0))
			Tr->bh.num++;
	}
}
bool InsertNode(TrieTree &Tr, string s,int _depth)
{
	TrieTree temp = new TrieNode;
	string str;
	if (Tr == NULL)
	{
		InitBranchNode(Tr);
	}
	if (_depth == s.length())
	{
		Tr->bh.ptr[0] = new TrieNode;
		temp = Tr->bh.ptr[0];
		temp->kind = Leaf;
		temp->lf.key = new char[s.length() + 1];
		for (int i = 0; i < s.length();i++)
		{
			temp->lf.key[i] = s[i];
		}
		temp->lf.key[s.length()] = '\0';
		return true;
	}
	if (Tr->bh.ptr[s[_depth] - 'A' + 1] == 0)
	{
		Tr->bh.ptr[s[_depth] - 'A' + 1] = new TrieNode;
		temp = Tr->bh.ptr[s[_depth] - 'A' + 1];
		temp->kind = Leaf;
		temp->lf.key = new char[s.length() + 1];
		for (int i = 0; i < s.length(); i++)
		{
			temp->lf.key[i] = s[i];
		}
		temp->lf.key[s.length()] = '\0';
		return true;
	}
	else if (Tr->bh.ptr[s[_depth] - 'A' + 1]->kind == Leaf)
	{
		if (Tr->bh.ptr[s[_depth] - 'A' + 1]->lf.key == s)
			return false;
		str = Tr->bh.ptr[s[_depth] - 'A' + 1]->lf.key;
		delete Tr->bh.ptr[s[_depth] - 'A' + 1];
		InitBranchNode(Tr->bh.ptr[s[_depth] - 'A' + 1]);
		temp = Tr->bh.ptr[s[_depth] - 'A' + 1];
		if (InsertNode(temp, str, _depth + 1))
			Tr->bh.ptr[s[_depth] - 'A' + 1]->bh.num++;
		temp = Tr->bh.ptr[s[_depth] - 'A' + 1];
		if (InsertNode(temp, s, _depth + 1))
		{
			Tr->bh.ptr[s[_depth] - 'A' + 1]->bh.num++;
			return true;
		}
		else
			return false;
	}
	else
	{
		if (InsertNode(Tr->bh.ptr[s[_depth] - 'A' + 1], s, _depth + 1))
		{
			Tr->bh.ptr[s[_depth] - 'A' + 1]->bh.num++;
			return true;
		}
		else
			return false;
	}
}
void PrintTree(TrieTree &Tr,string& _output)
{
	if (!Tr)
	{
		return;
	}
	else if (Tr->kind == Leaf)
	{
		_output += Tr->lf.key;
	}
	else
	{
		int flag = 0;
		_output += "(";
		for (int i = 0; i < 27;i++)
		{
			if (Tr->bh.ptr[i])
			{
				PrintTree(Tr->bh.ptr[i],_output);
				flag++;
				if (flag != Tr->bh.num)
				{
					_output += ",";
				}
			}
		}
		_output += ")";
	}
}
void InitBranchNode(TrieTree &Tr)
{
	Tr = new TrieNode;
	Tr->kind = Branch;
	for (int i = 0; i < 27; i++)
	{
		Tr->bh.ptr[i] = 0;
	}
	Tr->bh.num = 0;
}
void GetOutput(string &str)
{
	for (int i = 0; i < str.length();i++)
	{
		if (((str[i] == ')')|| (str[i] <= 'Z' && str[i] >= 'A')) && str[i + 1] == ',' && str[i + 2] == ')')
		{
			str.erase(i + 1,1);
		}
	}
}