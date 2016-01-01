#include "BTree.h"

BTreeNode::BTreeNode(int _t, bool _leaf)
{
	t = _t;
	isLeaf = _leaf;
	// 分配内存
	keys = new mapNode[2 * t - 1];
	m_child = new BTreeNode*[2 * t];
	for (int i = 0; i < 2 * t; i++)
		m_child[i] = NULL;
	// 初始关键字个数为0
	n = 0;
}
// 遍历当前节点和当前节点下的子树,进行排序
void BTreeNode::traverse_sort()
{
	int i;
	// n个关键字，和n+1个孩子
	for (i = 0; i < n; i++)
	{
		quickSort_Times(keys[i].second->m_document, keys[i].second->lastDoc);
		if (!isLeaf)
				m_child[i]->traverse_sort();
	}
	if (!isLeaf)
			m_child[i]->traverse_sort();
}
// 在当前节点下查找 k
wordNode *BTreeNode::searchWord(CharString &k)
{
	// 找到第一个大于或等于k的关键字
	int i = 0;
	while (i < n && keys[i].first < k)
		i++;
	//如果相等，就找到了
	if (keys[i].first == k)
		return keys[i].second;
	//如果是叶节点，未找到
	if (isLeaf == true)
		return NULL;
	// 否则可能在子树中
	return m_child[i]->searchWord(k);
}
void BTreeNode::insertNonFull(mapNode k)
{
	// 初始化为最右
	int i = n - 1;
	if (isLeaf == true)
	{
		//找到合适的位置插入,类似插入排序
		while (i >= 0 && k.first < keys[i].first)
		{
			keys[i + 1] = keys[i];
			i--;
		}
		keys[i + 1] = k;
		n = n + 1;
	}
	else // 不是根节点
	{
		// 在子节点插入
		while (i >= 0 && k.first < keys[i].first)
			i--;
		if (m_child[i + 1]->n == 2 * t - 1)
		{
			splitChild(i + 1, m_child[i + 1]);
			// 分裂后，C[i]的中间节点被提升，C[i]分成两部分
			//需要知道那一部分包含新的key
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
	// 复制
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
	// 找到第一个大于或等于k的关键字
	int i = 0;
	while (i < n && keys[i].first < k)
		i++;
	//如果相等，就找到了
	if (keys[i].first == k)
		return this;
	//如果是叶节点，未找到
	if (isLeaf == true)
		return NULL;
	// 否则可能在子树中
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
// 插入关键字k
void BTree::insert(mapNode k)
{
	if (root == NULL)
	{
		// 分配内存
		root = new BTreeNode(T, true);
		root->keys[0] = k;
		root->n = 1;  // 更新关键字个数
	}
	else
	{
		if (root->n == KEY_MAX)
		{ //如果关键字 已满
			//为新的根节点 分配内存
			BTreeNode *s = new BTreeNode(T, false);
			s->m_child[0] = root;
			// 分裂操作
			s->splitChild(0, root);
			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->m_child[i]->insertNonFull(k);
			// 更改根节点
			root = s;
		}
		else  // 不满
			root->insertNonFull(k);
	}
}
//重载mytree删除
BTreeNode *BTree::BTree_delete(CharString &target)
{
	// 特殊处理，当根只有两个子女，切两个子女的关键字个数都为M-1时，合并根与两个子女
	// 这是唯一能降低树高的情形
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
// 删除入口
BTreeNode *BTree::BTree_delete(BTreeNode *root,CharString &target)
{
	// 特殊处理，当根只有两个子女，切两个子女的关键字个数都为M-1时，合并根与两个子女
	// 这是唯一能降低树高的情形
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

// root至少有个t个关键字，保证不会回溯
void BTree::BTree_delete_nonone(BTreeNode *root, CharString &target)
{
	if (true == root->isLeaf)
	{  // 如果在叶子节点，直接删除
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
	{  // 在分支中
		int i = 0;
		BTreeNode *y = NULL, *z = NULL;
		while (i < root->n && root->keys[i].first < target) i++;
		if (i < root->n && target == root->keys[i].first) 
		{ // 如果在分支节点找到target
			y = root->m_child[i];
			z = root->m_child[i + 1];
			if (y->n > KEY_MIN) 
			{
				// 如果左分支关键字多于M-1，则找到左分支的最右节点prev，替换target
				// 并在左分支中递归删除prev,情况2（a)
				mapNode pre = BTree_searchMax(y);
				root->keys[i] = pre;
				BTree_delete_nonone(y, pre.first);
			}
			else if (z->n > KEY_MIN) 
			{
				// 如果右分支关键字多于M-1，则找到右分支的最左节点next，替换target
				// 并在右分支中递归删除next,情况2(b)
				mapNode next = BTree_searchMin(z);
				root->keys[i] = next;
				BTree_delete_nonone(z, next.first);
			}
			else {
				// 两个分支节点数都为M-1，则合并至y，并在y中递归删除target,情况2(c)
				BTreeMergeChild(root, i, y, z);
				BTree_delete(y, target);
			}
		}
		else 
		{   // 在分支没有找到，肯定在分支的子节点中
			y = root->m_child[i];
			if (i < root->n)
				z = root->m_child[i + 1];
			BTreeNode *p = NULL;
			if (i > 0)
				p = root->m_child[i - 1];
			if (y->n == KEY_MIN) 
			{
				if (i > 0 && p->n > KEY_MIN)
					// 左邻接节点关键字个数大于M-1
					BTree_shiftToRight(root, i - 1, p, y); //情况3(a)
				else if (i < root->n && z->n > KEY_MIN)
					// 右邻接节点关键字个数大于M-1
					BTreeShiftToLeft(root, i, y, z); // 情况3(b)
				else if (i > 0) 
				{
					BTreeMergeChild(root, i - 1, p, y);  // 情况3（c)
					y = p;
				}
				else
					BTreeMergeChild(root, i, y, z); // 情况3(c)
				BTree_delete_nonone(y, target);
			}
			else 
				BTree_delete_nonone(y, target);
		}

	}
}

//寻找rightmost，以root为根的最大关键字
mapNode BTree::BTree_searchMax(BTreeNode *root)
{
	BTreeNode *y = root;
	while (false == y->isLeaf) 
		y = y->m_child[y->n];
	return y->keys[y->n - 1];
}

// 寻找leftmost，以root为根的最小关键字
mapNode BTree::BTree_searchMin(BTreeNode *root)
{
	BTreeNode *z = root;
	while (false == z->isLeaf) 
		z = z->m_child[0];
	return z->keys[0];
}

// z向y借节点，将root->keys[pos]下降至z，将y的最大关键字上升至root的pos处
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

// y向借节点，将root->keys[pos]下降至y，将z的最小关键字上升至root的pos处
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

// 将y，root->keys[pos], z合并到y节点，并释放z节点，y,z各有M-1个节点
void BTree::BTreeMergeChild(BTreeNode *root, int pos, BTreeNode *y, BTreeNode *z)
{
	// 将z中节点拷贝到y的后半部分
	y->n = 2 * KEY_MIN;
	for (int i = T; i < 2 * KEY_MIN; i++)
		y->keys[i] = z->keys[i - T];
	y->keys[KEY_MIN] = root->keys[pos]; // keys[pos]下降为y的中间节点

	// 如果z非叶子，需要拷贝pointer
	if (false == z->isLeaf)
		for (int i = T; i < 2 * T; i++)
			y->m_child[i] = z->m_child[i - T];

	// keys[pos]下降到y中，更新keysey和pointer
	for (int j = pos + 1; j < root->n; j++) 
	{
		root->keys[j - 1] = root->keys[j];
		root->m_child[j] = root->m_child[j + 1];
	}
	root->n -= 1;
}