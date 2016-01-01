#include "wordNode.h"

void wordNode::insertDocument(Document *doc)
{
	if (m_document == NULL)
	{
		m_document = doc;
		lastDoc = m_document;
		return;
	}
	if (doc != NULL)
	{
		if (m_document->next == NULL)
			m_document->next = lastDoc = doc;
		else
		{
			lastDoc->next = doc;
			lastDoc = doc;
		}
	}
}
void quickSort_Times(Document* h, Document* t)
{
	if (h == t)
		return;
	//partition
	Document *i, *j;
	i = j = h;
	while (j != t->next)
	{
		if (j->times > h->times)
		{
			i = i->next;
			swapDoc(*i, *j);
		}
		j = j->next;
	}
	swapDoc(*i, *h);
	//µÝ¹é ÅÅÐò
	quickSort_Times(h, i);
	//·ÀÖ¹Ô½½ç
	if (i->next != t->next)
		quickSort_Times(i->next, t);
}
Document* GetPartion(Document* pBegin, Document* pEnd)
{
	Document* p = pBegin;
	Document* q = p->next;
	while (q != pEnd)
	{
		if (q->times > pBegin->times)
		{
			p = p->next;
			swapDoc(*p, *q);
		}
		q = q->next;
	}
	swap(*p, *pBegin);
	return p;
}
void QuickSort(Document* pBeign, Document* pEnd)
{
	if (pBeign != pEnd)
	{
		Document* partion = GetPartion(pBeign, pEnd);
		QuickSort(pBeign, partion);
		QuickSort(partion->next, pEnd);
	}
}