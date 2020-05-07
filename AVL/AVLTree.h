#pragma once

#include <vector>
#include <stack>

namespace dg {

template <class T>
class TreeNode
{
	int m_bf;
	T m_data;
	TreeNode<T>* m_left;
	TreeNode<T>* m_right;
	TreeNode<T>* m_parent;
public:
	TreeNode(const T& val = T()) :
		m_bf(0),
		m_data(val),
		m_left(nullptr),
		m_right(nullptr),
		m_parent(nullptr)
	{}

	template <class T>
	friend class AVLTree;
};

template <class T>
class AVLTree
{
public:
	TreeNode<T>* m_root;

	void destroy(TreeNode<T>* root)
	{
		if (root)
		{
			destroy(root->m_left);
			destroy(root->m_right);
			delete root;
		}
	}

	// �������������������������
	void lRound(TreeNode<T>* pre)
	{
		TreeNode<T>* parent = pre->m_parent;
		TreeNode<T>* cur = pre->m_right;

		cur->m_parent = parent;
		if (parent)
		{
			if (parent->m_left == pre)
			{
				parent->m_left = cur;
			}
			else
			{
				parent->m_right = cur;
			}
		}
		else
		{
			m_root = cur;
		}

		pre->m_right = cur->m_left;
		if (cur->m_left)
		{
			cur->m_left->m_parent = pre;
		}

		cur->m_left = pre;
		pre->m_parent = cur;

		cur->m_bf = pre->m_bf = 0;
	}

	// ����������������������ҵ���
	void rRound(TreeNode<T>* pre)
	{
		TreeNode<T>* parent = pre->m_parent; //B���
		TreeNode<T>* cur = pre->m_left;

		cur->m_parent = parent;
		if (parent)
		{
			if (parent->m_left == pre)
			{
				parent->m_left = cur;
			}
			else
			{
				parent->m_right = cur;
			}
		}
		else
		{
			m_root = cur;
		}

		pre->m_left = cur->m_right;
		if (cur->m_right)
		{
			cur->m_right->m_parent = pre;
		}

		cur->m_right = pre;
		pre->m_parent = cur;

		cur->m_bf = pre->m_bf = 0;
	}

	void rlRound(TreeNode<T>* pre)
	{
		TreeNode<T>* right = pre->m_right;
		TreeNode<T>* newroot = right->m_left;

		int flag = newroot->m_bf;

		rRound(pre->m_right);
		lRound(pre);

		if (flag == -1)
		{
			right->m_bf = 1;
		}
		else if(flag == 1)
		{
			pre->m_bf = -1;
		}
	}

	void lrRound(TreeNode<T>* pre)
	{
		TreeNode<T>* left = pre->m_left;
		TreeNode<T>* newroot = left->m_right;

		int flag = newroot->m_bf;

		lRound(pre->m_left);
		rRound(pre);

		if (flag == -1)
		{
			pre->m_bf = 1;
		}
		else if (flag == 1)
		{
			left->m_bf = -1;
		}
	}
public:
	AVLTree() :
		m_root(nullptr)
	{}

	~AVLTree()
	{
		destroy(m_root);
	}

	bool insert(const T& val)
	{
		if (m_root == nullptr)
		{
			m_root = new TreeNode<T>(val);
			return true;
		}

		TreeNode<T>* cur = m_root;
		TreeNode<T>* pre = nullptr;

		while (cur)
		{
			if (val < cur->m_data)
			{
				pre = cur;
				cur = cur->m_left;
			}
			else if (val > cur->m_data)
			{
				pre = cur;
				cur = cur->m_right;
			}
			else
			{
				return false;
			}
		}

		cur = new TreeNode<T>(val);
		if (val < pre->m_data)
		{
			pre->m_left = cur;
		}
		else
		{
			pre->m_right = cur;
		}

		cur->m_parent = pre;

		while (pre)
		{
			if (pre->m_left == cur)
			{
				pre->m_bf--;
			}
			else
			{
				pre->m_bf++;
			}

			if (pre->m_bf == 0)
			{
				break;
			}
			else if (pre->m_bf == 1 || pre->m_bf == -1)
			{
				cur = pre;
				pre = pre->m_parent;
			}
			else
			{
				if (pre->m_bf == 2)
				{
					if (cur->m_bf == 1)
					{
						lRound(pre);
					}
					else
					{
						rlRound(pre);
					}
				}
				else
				{
					if (cur->m_bf == 1)
					{
						lrRound(pre);
					}
					else
					{
						rRound(pre);
					}
				}
				break;
			}
		}
		return true;
	}

	std::vector<T> InOrder()
	{
		std::stack<TreeNode<T>*> s;
		std::vector<T> res;
		TreeNode<T>* cur = m_root;

		while (cur || !s.empty())
		{
			for (; cur; cur = cur->m_left)
			{
				s.push(cur);
			}

			if (!s.empty())
			{
				cur = s.top();
				res.push_back(cur->m_data);
				s.pop();

				cur = cur->m_right;
			}
		}

		return res;
	}

	int _Height(TreeNode<T>* root) {
		if (root == NULL)
		{
			return 0;
		}
		int depth = 0;
		//���������ĸ߶�
		int leftDepth = _Height(root->m_left);
		//���������ĸ߶�
		int rightDepth = _Height(root->m_right);
		//��������ĸ߶�
		depth = leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
		return depth;
	}

	bool _IsBalanceTree(TreeNode<T>* pRoot) {
		// ����Ҳ��AVL��
		if (nullptr == pRoot)
			return true;
		// ����pRoot�ڵ��ƽ������:��pRoot���������ĸ߶Ȳ� 
		int leftHeight = _Height(pRoot->m_left);
		int rightHeight = _Height(pRoot->m_right);
		int diff = rightHeight - leftHeight;
		// ����������ƽ��������pRoot��ƽ�����Ӳ���ȣ����� 
		// pRootƽ�����ӵľ���ֵ����1����һ������AVL��
		if (diff != pRoot->m_bf || (diff > 1 || diff < -1))
			return false;
		// pRoot��������������AVL���������һ����AVL��
		return _IsBalanceTree(pRoot->m_left) && _IsBalanceTree(pRoot->m_right);
	}

};

};