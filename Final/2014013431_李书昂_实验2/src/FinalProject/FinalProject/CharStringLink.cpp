#include "CharStringLink.h"


CharStringLink::CharStringLink(CharString &str)
{
	m_string = str;
	last = this->next;
	next = NULL;
}
void CharStringLink::insert_Link(int e, CharString &str)
{
	CharStringLink *p = NULL, *tempCsLink = NULL;
	tempCsLink = new CharStringLink;
	tempCsLink->m_string = str;
	tempCsLink->next = NULL;
	p = this;
	for (int i = 0; i < e - 1 && p != NULL; i++, p = p->next){}
	if (p != NULL)
	{
		tempCsLink->next = p->next;
		p->next = tempCsLink;
	}
	return;
}
void CharStringLink::insert_Link(CharString &str)
{
	CharStringLink *tempCsLink = NULL;
	if (this->m_string.m_ch == NULL)
		this->m_string = str;
	else if (this->next == NULL)
	{
		tempCsLink = new CharStringLink;
		tempCsLink->m_string = str;
		tempCsLink->next = NULL;
		last = this->next = tempCsLink;
	}
	else
	{
		tempCsLink = new CharStringLink;
		tempCsLink->m_string = str;
		tempCsLink->next = NULL;
		last->next = tempCsLink;
		last = tempCsLink;
	}
}
void CharStringLink::delete_Link(int e)
{
	CharStringLink *p = NULL, *tempCsLink = NULL;
	p = this;
	for (int i = 0; i < e - 2 && p != NULL; i++, p = p->next){}
	if (p != NULL)
	{
		tempCsLink = p->next;
		p->next = tempCsLink->next;
		tempCsLink->next = NULL;
		delete tempCsLink;
		tempCsLink = NULL;
	}
}
CharStringLink* CharStringLink::research_Link(CharString &str)
{
	CharStringLink *p = NULL;
	p = this;
	while (p)
	{
		if (p->m_string == str)
			return p;
		p = p->next;
	}
	return NULL;
}