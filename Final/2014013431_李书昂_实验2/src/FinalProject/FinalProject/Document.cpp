#include "document.h"

Document* combineDocuments(Document *doc1, Document *doc2)
{
	Document *begin, *temp, *q;
	q = begin = temp = NULL;
	Document *p1 = doc1, *p2 = doc2;
	while (p1&&p2)
	{
		if (p1->MusicID == p2->MusicID)
		{
			if (begin == NULL)
			{
				temp = new Document;
				begin = q = temp;
				temp->MusicID = p1->MusicID;
				temp->times = p1->times + p2->times;
				temp->searchWord_Num++;
				temp = temp->next;
			}
			else
			{
				temp = new Document;
				temp->MusicID = p1->MusicID;
				temp->times = p1->times + p2->times;
				temp->searchWord_Num++;
				q->next = temp;
				q = temp;
				temp = temp->next;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		else
		{
			if (begin == NULL)
			{
				temp = new Document;
				begin = q = temp;
				if (p1->times > p2->times)
				{
					temp->times = p1->times;
					temp->MusicID = p1->MusicID;
					p1 = p1->next;
				}
				else
				{
					temp->times = p2->times;
					temp->MusicID = p2->MusicID;
					p2 = p2->next;
				}
			}
			else
			{
				temp = new Document;
				if (p1->times > p2->times)
				{
					temp->MusicID = p1->MusicID;
					temp->times = p1->times;
					p1 = p1->next;
				}
				else
				{
					temp->MusicID = p2->MusicID;
					temp->times = p2->times;
					p2 = p2->next;
				}
				q->next = temp;
				q = temp;
				temp = temp->next;
			}
		}
	}
	if (p1 == NULL && p2 != NULL)
		temp = p2;
	else if (p1 != NULL && p2 == NULL)
		temp = p1;
	q->next = temp;
	return begin;
}
void swapDoc(Document &a, Document &b)
{
	Document temp;
	temp = a;
	a = b;
	b = temp;
}
void Document::printDocument(fstream &outfile)
{
	Document *p = this;
	while (p)
	{
		outfile << "(" << p->MusicID << "," << p->times << ") ";
		p = p->next;
	}
	outfile << endl;
}
Document& Document::operator=(const Document& other)
{
	MusicID = other.MusicID;
	times = other.times;
	return *this;
}