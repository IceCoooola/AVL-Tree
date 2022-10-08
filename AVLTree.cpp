#pragma once
#include<utility>
#include<iostream>
template<class K, class Y>
struct AVLTreeNode
{
	AVLTreeNode(const std::pair<K, Y>& pr) :_left(nullptr), _right(nullptr), _parent(nullptr), _bf(0)
	{ 
		_kv.first = pr.first;
		_kv.second = pr.second;
	}
	AVLTreeNode<K, Y>* _left;
	AVLTreeNode<K, Y>* _right;
	AVLTreeNode<K, Y>* _parent;

	int _bf;//balancing facotr
	std::pair<K, Y> _kv;
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree():_root(nullptr){}
	~AVLTree()
	{

	}

	bool insert(const std::pair<K, V>& kv)
	{
		if (!_root)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		//find the correct insert spot
		while (cur)
		{
			if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				std::cout << "data exist.\n";
				return false;
			}
		}

		//insert new node
		cur = new Node(kv);
		cur->_parent = parent;
		if (parent->_kv.first < cur->_kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		//control balance factor
		//renew parent's bf, untill parent == null, which is _root->parent
		while (parent)
		{
			//if new root is at parent's right, ++parent's bf
			if (parent->_right == cur)
			{
				++parent->_bf;
			}
			//if new root is at parent's left, --parent's bf
			else
			{
				--parent->_bf;
			}
			//if parent's balance factor == 0, meabs it is balanced so should not renew the upper balance factors
			if (parent->_bf == 0)
			{
				break;
			}
			// parent's bf == -1 or == 1 means need to renew the upper parent
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			//parent's bf == 2 means need to rotate
			else if (parent->_bf == -2)
			{
				//左边高，右单旋
				if (parent->_left == -1)
				{

				}
			}
			else if (parent->_bf == 2)
			{
				//左边高，右单旋
				//left side have more nodes, rorate to the right
				//把根按下去，根成为左子树的右边，所有在根->左边的->右边的数接在根的左边
			}
			else
			{
				std::cout << "balancing factor > 2, bug generated.\n";
				return false;
			}
		}
		
	}

	Node* find(const K& key)
	{

	}

	bool earase(const K& key)
	{

	}

private:
	Node* _root;
	void RotateR(Node* parent)
	{
		//left side have more nodes, rorate to the right
//把根按下去，根成为左子树的右边，所有在根->左边的->右边的数接在根的左边
		Node* grandparent = parent->_parent;
		Node* subR = parent->_left->_right;
		Node* newParent = parent->_left;

		if (grandparent)
		{
			if (grandparent->_left == parent)
			{
				grandparent->_left = newParent;
			}
			if (grandparent->_right == parent)
			{
				grandparent->_right = newParent;
			}
		}

		newParent->_right = parent;
		parent->_left = subR;
		newParent->_parent = grandparent;
		parent->_parent = newParent;
		if (subR)
		{
			subR->_parent = parent;
		}
		newParent->_bf = 0;
		parent->_bf = 0;

		if (parent == _root)
			_root = parent;
	}
};
