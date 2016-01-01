#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node
{
    char m_data;
    struct node *next;
}linklist;

struct node*createlist()
{
    char m[200];
    linklist *head, *p, *q;
    head =  p = q =NULL;
    gets(m);
    int i = strlen(m) - 1;
    while (i >= 0)
    {
        p = (linklist*) malloc(sizeof(linklist));
        if (head==NULL)
        {
            q=head=p;
            p->m_data=m[i];
        }
        else
        {
            p->m_data=m[i];
            q->next=p;
        }
        q=p;
		i--;
    }
    q->next=NULL;
    return head;
}
void print(int p, int* untisum);
void print(int p, int* untisum)
{
	for (p = p - 1; p >= 0; p--)
		printf("%d", untisum[p]);
}
void add(linklist*head1,linklist*head2)
{
    int i=0;
    linklist *a,*b;
    int untisum[200]={0};
    a=head1;
    b=head2;
    while (a!=NULL||b!=NULL)
    {
    	if (a==NULL)
            untisum[i]=b->m_data-'0';
        else if (b==NULL)
			untisum[i] = a->m_data - '0';
        else
        {
            if (a->m_data-'0'+b->m_data-'0' + untisum[i]<=9)
                untisum[i]=untisum[i]+a->m_data-'0'+b->m_data-'0';
            else
            {
                untisum[i]=untisum[i]+a->m_data-'0'+b->m_data-'0'-10;
                untisum[i+1]=1;
            }
        }
		if (a != NULL)
			a=a->next;
		if (b != NULL)
			b = b->next;
        i++;
    }
    print(i,untisum);
}


int main()
{
    linklist *head1,*head2;
    head1=createlist();
    head2=createlist();
	add(head1,head2);
    return 0;
}