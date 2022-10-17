#pragma once
#include<utility>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
using std::make_pair;
template<class K, class Y>
struct AVLTreeNode
{
    AVLTreeNode(const std::pair<K, Y>& pr) :_left(nullptr), _right(nullptr), _parent(nullptr), _bf(0),_kv(pr){ }
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

        Node* parent = _root;
        Node* cur = _root;
        //find the correct insert spot
        while (cur)
        {
            if (cur->_kv.first > kv.first)
            {
                parent = cur;
                cur = cur->_left;
            }
            else if (cur->_kv.first < kv.first)
            {
                parent = cur;
                cur = cur->_right;
            }
            else
            {
                std::cout << "data exist.\n";
                return false;
            }
        }

        //insert new node
        cur = new Node(kv);
        Node* newnode = cur;
        if (parent->_kv.first < kv.first)
        {
            parent->_right = cur;
            cur->_parent = parent;
        }
        else
        {
            parent->_left = cur;
            cur->_parent = parent;
        }

        //control balance factor
        //renew parent's bf, untill parent == null, which is _root->parent
        while (cur != _root)
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
            else if (parent->_bf == 2 || parent->_bf == -2)
            {
                if (parent->_bf == -2)
                {
                    if (cur->_bf == -1)
                    {
                        // ”“µ•–˝
                        RotateR(parent);
                    }
                    else // cur->_bf == 1
                    {
                        RotateLR(parent);
                    }
                }
                else // parent->_bf  == 2
                {
                    if (cur->_bf == 1)
                    {
                        // ◊Ûµ•–˝
                        RotateL(parent);
                    }
                    else // cur->_bf == -1
                    {
                        RotateRL(parent);
                    }
                }

                break;
            }
            else
            {
                std::cout << "balancing factor > 2, bug generated.\n";
                return false;
            }
        }
        return true;
    }

    Node* find(const K& key)
    {
        return _find(_root, key);
    }

    bool earase(const K& key)
    {

    }
    void inorder()
    {
        _inorder(_root);
    }

private:
    Node* _root;
    void RotateR(Node* parent)
    {
        //left side have more nodes, rorate to the right
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        Node* grandparent = parent->_parent;
        parent->_left = subLR;
        subL->_right = parent;
        parent->_parent = subL;
        if (subLR)
        {
            subLR->_parent = parent;
        }


        if (parent == _root)
        {
            _root = subL;
            _root->_parent = nullptr;
        }
        else
        {
            if (grandparent->_left == parent)
            {
                grandparent->_left = subL;
            }
            else
            {
                grandparent->_right = subL;
            }

            subL->_parent = grandparent;
        }
        
        subL->_bf = 0;
        parent->_bf = 0;

    }

    void RotateL(Node* parent)
    {
        //right side have more nodes, rorate to the left

        Node* grandparent = parent->_parent;
        Node* subR = parent->_right;
        Node* subRL = subR->_left;
        parent->_right = subRL;
        subR->_left = parent;
        parent->_parent = subR;
        if (subRL)
        {
            subRL->_parent = parent;
        }

        if (parent == _root)
        {
            _root = subR;
            _root->_parent = nullptr;
        }
        else
        {
            if (grandparent->_left == parent)
            {
                grandparent->_left = subR;
            }
            else
            {
                grandparent->_right = subR;
            }

            subR->_parent = grandparent;
        }

        subR->_bf = 0;
        parent->_bf = 0;
    }
    void RotateLR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        int bf = subLR->_bf;
        RotateL(parent->_left);
        RotateR(parent);
        if(bf == 1)
        {
            subL->_bf = -1;
            parent->_bf = 0;
            subLR->_bf = 0;
        }
        else if (bf == -1)
        {
            parent->_bf = 1;
            subL->_bf = 0;
            subLR->_bf = 0;
        }
        else
        {
        
            parent->_bf = 0;
            subL->_bf = 0;
            subLR->_bf = 0;
        }
    }
    void RotateRL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;
        int bf = subRL->_bf;
        RotateR(parent->_right);
        RotateL(parent);
        if(bf == 1)
        {
            subRL->_bf = 0;
            subR->_bf = 0;
            parent->_bf = -1;
        }
        else if(bf == -1)
        {
            subRL->_bf = 0;
            subR->_bf = 1;
            parent->_bf = 0;
        }
        else
        {
            subRL->_bf = 0;
            subR->_bf = 0;
            parent->_bf = 0;
        }
    }    Node* _find(Node* root, const K& key)
    {
        if (!root)
        {
            return nullptr;
        }
        if (root->_kv.first < key)
        {
            _find(root->_right);
        }
        else if (root->_kv.first > key)
        {
            _find(root->_left);
        }
        else
        {
            return root;
        }
    }

    void _inorder(const Node* root)
    {
        if (!root)
            return;
        cout << root->_kv.first << "->" << root->_kv.second << endl;
        cout<<"balance factor: "<<root->_bf<<endl;
        _inorder(root->_left);
        _inorder(root->_right);
    }

};
