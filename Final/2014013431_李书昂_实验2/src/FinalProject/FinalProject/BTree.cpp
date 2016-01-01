#include "BTree.h"

BTreeNode::BTreeNode(int _t, bool _leaf)
{
	t = _t;
	isLeaf = _leaf;
	// �����ڴ�
	keys = new mapNode[2 * t - 1];
	m_child = new BTreeNode*[2 * t];
	for (int i = 0; i < 2 * t; i++)
		m_child[i] = NULL;
	// ��ʼ�ؼ��ָ���Ϊ0
	n = 0;
}
// ������ǰ�ڵ�͵�ǰ�ڵ��µ�����,��������
void BTreeNode::traverse_sort()
{
	int i;
	// n���ؼ��֣���n+1������
	for (i = 0; i < n; i++)
	{
		quickSort_Times(keys[i].second->m_document, keys[i].second->lastDoc);
		if (!isLeaf)
				m_child[i]->traverse_sort();
	}
	if (!isLeaf)
			m_child[i]->traverse_sort();
}
// �ڵ�ǰ�ڵ��²��� k
wordNode *BTreeNode::searchWord(CharString &k)
{
	// �ҵ���һ�����ڻ����k�Ĺؼ���
	int i = 0;
	while (i < n && keys[i].first < k)
		i++;
	//�����ȣ����ҵ���
	if (keys[i].first == k)
		return keys[i].second;
	//�����Ҷ�ڵ㣬δ�ҵ�
	if (isLeaf == true)
		return NULL;
	// ���������������
	return m_child[i]->searchWord(k);
}
void BTreeNode::insertNonFull(mapNode k)
{
	// ��ʼ��Ϊ����
	int i = n - 1;
	if (isLeaf == true)
	{
		//�ҵ����ʵ�λ�ò���,���Ʋ�������
		while (i >= 0 && k.first < keys[i].first)
		{
			keys[i + 1] = keys[i];
			i--;
		}
		keys[i + 1] = k;
		n = n + 1;
	}
	else // ���Ǹ��ڵ�
	{
		// ���ӽڵ����
		while (i >= 0 && k.first < keys[i].first)
			i--;
		if (m_child[i + 1]->n == 2 * t - 1)
		{
			splitChild(i + 1, m_child[i + 1]);
			// ���Ѻ�C[i]���м�ڵ㱻������C[i]�ֳ�������
			//��Ҫ֪����һ���ְ����µ�key
			if (keys[i + 1] < k)
				i++;
		}
		m_child[i + 1]->insertNonFull(k);
	}
}
void BTreeNode::splitChild(int i, BTreeNode *y)
{
	BTreeNode *z = new BTreeNode(y->t, y->isLeaf);
	z->n = t - 1;
	// ����
	for (int j = 0; j < t - 1; j++)
		z->keys[j] = y->keys[j + t];
	if (y->isLeaf == false)
	{
		for (int j = 0; j < t; j++)
			z->m_child[j] = y->m_child[j + t];
	}
	y->n = t - 1;
	for (int j = n; j >= i + 1; j--)
		m_child[j + 1] = m_child[j];
	m_child[i + 1] = z;
	for (int j = n - 1; j >= i; j--)
		keys[j + 1] = keys[j];
	keys[i] = y->keys[t - 1];
	n++;
}
BTreeNode *BTreeNode::searchNode(CharString &k)
{
	// �ҵ���һ�����ڻ����k�Ĺؼ���
	int i = 0;
	while (i < n && keys[i].first < k)
		i++;
	//�����ȣ����ҵ���
	if (keys[i].first == k)
		return this;
	//�����Ҷ�ڵ㣬δ�ҵ�
	if (isLeaf == true)
		return NULL;
	// ���������������
	return m_child[i]->searchNode(k);
}

wordNode* BTree::searchWord(CharString &k)
{
	return (root == NULL) ? NULL : root->searchWord(k);
}
void BTree::traverse()
{
	if (root != NULL)
		root->traverse_sort();
}
// ����ؼ���k
void BTree::insert(mapNode k)
{
	if (root == NULL)
	{
		// �����ڴ�
		root = new BTreeNode(T, true);
		root->keys[0] = k;
		root->n = 1;  // ���¹ؼ��ָ���
	}
	else
	{
		if (root->n == KEY_MAX)
		{ //����ؼ��� ����
			//Ϊ�µĸ��ڵ� �����ڴ�
			BTreeNode *s = new BTreeNode(T, false);
			s->m_child[0] = root;
			// ���Ѳ���
			s->splitChild(0, root);
			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->m_child[i]->insertNonFull(k);
			// ���ĸ��ڵ�
			root = s;
		}
		else  // ����
			root->insertNonFull(k);
	}
}
//����mytreeɾ��
BTreeNode *BTree::BTree_delete(CharString &target)
{
	// ���⴦������ֻ��������Ů����������Ů�Ĺؼ��ָ�����ΪM-1ʱ���ϲ�����������Ů
	// ����Ψһ�ܽ������ߵ�����
	if (1 == root->n)
	{
		BTreeNode *y = root->m_child[0];
		BTreeNode *z = root->m_child[1];
		if (NULL != y && NULL != z && KEY_MIN == y->n && KEY_MIN == z->n)
		{
			BTreeMergeChild(root, 0, y, z);
			BTree_delete_nonone(y, target);
			return y;
		}
		else
		{
			BTree_delete_nonone(root, target);
			return root;
		}
	}
	else
	{
		BTree_delete_nonone(root, target);
		return root;
	}
}
// ɾ�����
BTreeNode *BTree::BTree_delete(BTreeNode *root,CharString &target)
{
	// ���⴦������ֻ��������Ů����������Ů�Ĺؼ��ָ�����ΪM-1ʱ���ϲ�����������Ů
	// ����Ψһ�ܽ������ߵ�����
	if (1 == root->n) 
	{
		BTreeNode *y = root->m_child[0];
		BTreeNode *z = root->m_child[1];
		if (NULL != y && NULL != z && KEY_MIN == y->n && KEY_MIN == z->n) 
		{
			BTreeMergeChild(root, 0, y, z);
			delete root;
			BTree_delete_nonone(y, target);
			return y;
		}
		else 
		{
			BTree_delete_nonone(root, target);
			return root;
		}
	}
	else 
	{
		BTree_delete_nonone(root, target);
		return root;
	}
}

// root�����и�t���ؼ��֣���֤�������
void BTree::BTree_delete_nonone(BTreeNode *root, CharString &target)
{
	if (true == root->isLeaf)
	{  // �����Ҷ�ӽڵ㣬ֱ��ɾ��
		int i = 0;
		while (i < root->n && root->keys[i].first < target) 
			i++;
		if (target == root->keys[i].first) 
		{
			for (int j = i + 1; j < root->n; j++)
				root->keys[j - 1] = root->keys[j];/* == NULL?root->keys[i]:NULL;*/
			root->n--;
		}
		else 
			printf("target not found\n");
	}
	else 
	{  // �ڷ�֧��
		int i = 0;
		BTreeNode *y = NULL, *z = NULL;
		while (i < root->n && root->keys[i].first < target) i++;
		if (i < root->n && target == root->keys[i].first) 
		{ // ����ڷ�֧�ڵ��ҵ�target
			y = root->m_child[i];
			z = root->m_child[i + 1];
			if (y->n > KEY_MIN) 
			{
				// ������֧�ؼ��ֶ���M-1�����ҵ����֧�����ҽڵ�prev���滻target
				// �������֧�еݹ�ɾ��prev,���2��a)
				mapNode pre = BTree_searchMax(y);
				root->keys[i] = pre;
				BTree_delete_nonone(y, pre.first);
			}
			else if (z->n > KEY_MIN) 
			{
				// ����ҷ�֧�ؼ��ֶ���M-1�����ҵ��ҷ�֧������ڵ�next���滻target
				// �����ҷ�֧�еݹ�ɾ��next,���2(b)
				mapNode next = BTree_searchMin(z);
				root->keys[i] = next;
				BTree_delete_nonone(z, next.first);
			}
			else {
				// ������֧�ڵ�����ΪM-1����ϲ���y������y�еݹ�ɾ��target,���2(c)
				BTreeMergeChild(root, i, y, z);
				BTree_delete(y, target);
			}
		}
		else 
		{   // �ڷ�֧û���ҵ����϶��ڷ�֧���ӽڵ���
			y = root->m_child[i];
			if (i < root->n)
				z = root->m_child[i + 1];
			BTreeNode *p = NULL;
			if (i > 0)
				p = root->m_child[i - 1];
			if (y->n == KEY_MIN) 
			{
				if (i > 0 && p->n > KEY_MIN)
					// ���ڽӽڵ�ؼ��ָ�������M-1
					BTree_shiftToRight(root, i - 1, p, y); //���3(a)
				else if (i < root->n && z->n > KEY_MIN)
					// ���ڽӽڵ�ؼ��ָ�������M-1
					BTreeShiftToLeft(root, i, y, z); // ���3(b)
				else if (i > 0) 
				{
					BTreeMergeChild(root, i - 1, p, y);  // ���3��c)
					y = p;
				}
				else
					BTreeMergeChild(root, i, y, z); // ���3(c)
				BTree_delete_nonone(y, target);
			}
			else 
				BTree_delete_nonone(y, target);
		}

	}
}

//Ѱ��rightmost����rootΪ�������ؼ���
mapNode BTree::BTree_searchMax(BTreeNode *root)
{
	BTreeNode *y = root;
	while (false == y->isLeaf) 
		y = y->m_child[y->n];
	return y->keys[y->n - 1];
}

// Ѱ��leftmost����rootΪ������С�ؼ���
mapNode BTree::BTree_searchMin(BTreeNode *root)
{
	BTreeNode *z = root;
	while (false == z->isLeaf) 
		z = z->m_child[0];
	return z->keys[0];
}

// z��y��ڵ㣬��root->keys[pos]�½���z����y�����ؼ���������root��pos��
void BTree::BTree_shiftToRight(BTreeNode *root, int pos,BTreeNode *y, BTreeNode *z)
{
	z->n += 1;
	for (int i = z->n - 1; i > 0; i--)
		z->keys[i] = z->keys[i - 1];
	z->keys[0] = root->keys[pos];
	root->keys[pos] = y->keys[y->n - 1];
	if (false == z->isLeaf)
	{
		for (int i = z->n; i > 0; i--)
			z->m_child[i] = z->m_child[i - 1];
		z->m_child[0] = y->m_child[y->n];
	}
	y->n -= 1;
}

// y���ڵ㣬��root->keys[pos]�½���y����z����С�ؼ���������root��pos��
void BTree::BTreeShiftToLeft(BTreeNode *root, int pos,BTreeNode *y, BTreeNode *z)
{
	y->n += 1;
	y->keys[y->n - 1] = root->keys[pos];
	root->keys[pos] = z->keys[0];
	for (int j = 1; j < z->n; j++) 
		z->keys[j - 1] = z->keys[j];
	if (false == z->isLeaf)
	{
		y->m_child[y->n] = z->m_child[0];
		for (int j = 1; j <= z->n; j++)
			z->m_child[j - 1] = z->m_child[j];
	}
	z->n -= 1;
}

// ��y��root->keys[pos], z�ϲ���y�ڵ㣬���ͷ�z�ڵ㣬y,z����M-1���ڵ�
void BTree::BTreeMergeChild(BTreeNode *root, int pos, BTreeNode *y, BTreeNode *z)
{
	// ��z�нڵ㿽����y�ĺ�벿��
	y->n = 2 * KEY_MIN;
	for (int i = T; i < 2 * KEY_MIN; i++)
		y->keys[i] = z->keys[i - T];
	y->keys[KEY_MIN] = root->keys[pos]; // keys[pos]�½�Ϊy���м�ڵ�

	// ���z��Ҷ�ӣ���Ҫ����pointer
	if (false == z->isLeaf)
		for (int i = T; i < 2 * T; i++)
			y->m_child[i] = z->m_child[i - T];

	// keys[pos]�½���y�У�����keysey��pointer
	for (int j = pos + 1; j < root->n; j++) 
	{
		root->keys[j - 1] = root->keys[j];
		root->m_child[j] = root->m_child[j + 1];
	}
	root->n -= 1;
}