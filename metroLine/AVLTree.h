/*
   Implementation of an AVL Tree
   Based on the algorithms at:
    http://kukuruku.co/hub/cpp/avl-trees
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <iomanip>
#include "TreeNode.h"
#include "Queue.h"

#define DEBUG

template <class T>
class AVLTree {
private:
	TreeNode<T> * root;
    Queue<TreeNode<T>*> queue;
    int height;

	void recursivePrintInorder(TreeNode<T> * _root);
    void recursivePrintTree(TreeNode<T> * _root, int indent=0);
	bool recursiveSearch(TreeNode<T> * _root, int _data);
	void recursiveClear(TreeNode<T> * _root);
	TreeNode<T> * recursiveInsert(TreeNode<T> * _root, TreeNode<T> * _node);
    TreeNode<T> * recursiveRemove(TreeNode<T> * _root, int _data);
    TreeNode<T> * getMin(TreeNode<T> * _root);
    TreeNode<T> * balance(TreeNode<T> * _root);
    TreeNode<T> * rotateRight(TreeNode<T> * _root);
    TreeNode<T> * rotateLeft(TreeNode<T> * _root);
    int recursiveFindHeight(TreeNode<T> * _root);
    void updateHeight(TreeNode<T> * _root);
    int getBalanceFactor(TreeNode<T> * _root);
public:
	AVLTree();
	~AVLTree();
	void insertNode(int _data);
	void insertNode(TreeNode<T> * _node);
	bool search(int _data);
	TreeNode<T> * getRoot();
	void setRoot(TreeNode<T> * _node);
	void printInorder();
    void printBreadthFirst();
    void printTree();
    void remove(int _data);
	void clear();
	int findHeight();
	int getHeight();
};

template <class T>
AVLTree<T>::AVLTree()
{
    this->root = nullptr;
}

template <class T>
AVLTree<T>::~AVLTree()
{
    this->clear();
}

template <class T>
TreeNode<T> * AVLTree<T>::getRoot()
{
	return this->root;
}

template <class T>
void AVLTree<T>::setRoot(TreeNode<T> * _node)
{
    this->root = _node;
}

//// PRINTING THE DATA IN THE TREE ////
template <class T>
void AVLTree<T>::printInorder()
{
	if (this->root == nullptr)
		return;
	recursivePrintInorder(this->root);
	std::cout << std::endl;
}

template <class T>
void AVLTree<T>::recursivePrintInorder(TreeNode<T> * _root)
{
	if (_root == nullptr)
		return;

	recursivePrintInorder(_root->getLeft());
	std::cout << _root->getData() << "\t";
	recursivePrintInorder(_root->getRight());
}

template <class T>
void AVLTree<T>::printTree()
{
	if (this->root == nullptr)
		return;
    recursivePrintTree(this->root, 2);
}

/*
   Print the tree with format, in a vertical way
   Prints as well the height of each node
*/
template <class T>
void AVLTree<T>::recursivePrintTree(TreeNode<T> * _root, int indent)
{
    if(_root != nullptr)
    {
        if(_root->getRight())
            recursivePrintTree(_root->getRight(), indent+4);
        if (indent)
        {
            std::cout << std::setw(indent) << ' ';
        }
        std::cout << _root->getData() << " (" << _root->getHeight() << ")" << std::endl;
        if(_root->getLeft())
            recursivePrintTree(_root->getLeft(), indent+4);
    }
}

template <class T>
void AVLTree<T>::printBreadthFirst()
{
    if (this->root == nullptr)
        return;
    TreeNode<T> * item;
    queue.insert(this->root);
    while (!queue.isEmpty())
    {
        item = queue.remove()->getData();
        std::cout << item->getData() << "\t";
        if (item->getLeft() != nullptr)
            queue.insert(item->getLeft());
        if (item->getRight() != nullptr)
            queue.insert(item->getRight());
    }
    std::cout << std::endl;
}

//// CLEAR THE TREE ////
template <class T>
void AVLTree<T>::clear()
{
    // Do nothing for an empty tree
    if (this->root == nullptr)
        return;
    // Clear recursively
    recursiveClear(this->root);
    // State that the tree is empty
    this->root = nullptr;
}

template <class T>
void AVLTree<T>::recursiveClear(TreeNode<T> * _root)
{
    if (_root == nullptr)
        return;
    recursiveClear(_root->getLeft());
    recursiveClear(_root->getRight());
    delete _root;
}

//// INSERT NEW NODES ////
template <class T>
void AVLTree<T>::insertNode(int _data)
{
	TreeNode<T> * new_node = new TreeNode<T>(_data);
	this->insertNode(new_node);
}

template <class T>
void AVLTree<T>::insertNode(TreeNode<T> * _node)
{
	if (this->root == nullptr)
	{
		this->root = _node;
	}
	else
	{
		this->root = recursiveInsert(this->root, _node);
	}
}

template <class T>
TreeNode<T> * AVLTree<T>::recursiveInsert(TreeNode<T> * _root, TreeNode<T> * _node)
{
	// Node goes on the left branch
	if (_node->getData() < _root->getData())
	{
		if (_root->getLeft() == nullptr)
		{
			_root->setLeft(_node);
		}
		else
		{
			_root->setLeft(recursiveInsert(_root->getLeft(), _node));
		}
	}
	// Node goes on the right branch
	else if (_node->getData() > _root->getData())
	{
		if (_root->getRight() == nullptr)
		{
			_root->setRight(_node);
		}
		else
		{
			_root->setRight(recursiveInsert(_root->getRight(), _node));
		}
	}
    // The node already exists in the tree
    else if (_root->getData() == _node->getData())
	{
		return _root;
	}
    // Rebalance the node after the insertion
    return balance(_root);
}

//// SEARCH THE TREE FOR THE GIVEN DATA ////
template <class T>
bool AVLTree<T>::search(int _data)
{
	if (this->root == nullptr)
		return false;
	else
		return recursiveSearch(this->root, _data);
}

template <class T>
bool AVLTree<T>::recursiveSearch(TreeNode<T> * _root, int _data)
{
	if (_root->getData() == _data)
		return true;
	else
	{
		if (_data < _root->getData())
		{
			if (_root->getLeft() == nullptr)
				return false;
			return recursiveSearch(_root->getLeft(), _data);
		}
		else
		{
			if (_root->getRight() == nullptr)
				return false;
			return recursiveSearch(_root->getRight(), _data);
		}
	}
}

//// REMOVING NODES FROM A TREE ////
template <class T>
TreeNode<T> * AVLTree<T>::getMin(TreeNode<T> * _root)
{
    if (_root->getLeft() == nullptr)
        return _root;
    else
        return getMin(_root->getLeft());
}

template <class T>
void AVLTree<T>::remove(int _data)
{
    if (this->root == nullptr)
        return;
    this->root = recursiveRemove(this->root, _data);
}

template <class T>
TreeNode<T> * AVLTree<T>::recursiveRemove(TreeNode<T> * _root, int _data)
{
    if (_root == nullptr)
        return nullptr;
    if (_data < _root->getData())
    {
        _root->setLeft( recursiveRemove(_root->getLeft(), _data) );
    }
    else if (_data > _root->getData())
    {
        _root->setRight( recursiveRemove(_root->getRight(), _data) );
    }
    // The data is found in the root
    else
    {
        // Node has no children
        if (_root->getLeft() == nullptr && _root->getRight() == nullptr)
        {
            std::cout << "Deleting leaf" << std::endl;
            delete _root;
            _root = nullptr;
        }
        // Node has only left child
        else if (_root->getRight() == nullptr)
        {
            std::cout << "Deleting with only left branch" << std::endl;
            TreeNode<T> * tmp = _root;
            _root = _root->getLeft();
            delete tmp;
        }
        // Node has only right child
        else if (_root->getLeft() == nullptr)
        {
            std::cout << "Deleting with only right branch" << std::endl;
            TreeNode<T> * tmp = _root;
            _root = _root->getRight();
            delete tmp;
        }
        // Node has both children
        else
        {
            std::cout << "Deleting with both branches" << std::endl;
            TreeNode<T> * tmp = getMin(_root->getRight());
            _root->setData(tmp->getData());
            _root->setRight(recursiveRemove(_root->getRight(), tmp->getData()));
        }
    }
    // Rebalance the node after the insertion
    return balance(_root);
}

//// COMPUTE THE HEIGHT OF THE TREE AND THE NODES ////
template <class T>
int AVLTree<T>::recursiveFindHeight(TreeNode<T> * _root)
{
    if (_root == nullptr)
        return 0;
    // Get the heights of the subtrees
    int left_height = recursiveFindHeight(_root->getLeft());
    int right_height = recursiveFindHeight(_root->getRight());
#ifdef DEBUG
    std::cout << "Node: " << _root->getData() << std::endl;
    std::cout << "Left Height: " << left_height << std::endl;
    std::cout << "Right Height: " << right_height << std::endl;
#endif
    // Obtain the height of this tree based on the largest height of the
    // subtrees
    height = 1 + (left_height > right_height ? left_height : right_height);
    // Store the height in the node
    _root->setHeight(height);
#ifdef DEBUG
    std::cout << "Height: " << height << std::endl << std::endl;
#endif
    return height;
}
   
template <class T>
int AVLTree<T>::findHeight()
{
    if (this->root == nullptr)
        return -1;
    return recursiveFindHeight(this->root); 
}

template <class T>
int AVLTree<T>::getHeight()
{
    return height;
}

template <class T>
void AVLTree<T>::updateHeight(TreeNode<T> * _root)
{
    int left_height = 0;
    int right_height = 0;
    if (_root->getLeft() != nullptr)
    {
        left_height = _root->getLeft()->getHeight();
    }
    if (_root->getRight() != nullptr)
    {
        right_height = _root->getRight()->getHeight();
    }
    _root->setHeight( std::max(left_height, right_height) + 1 );
#ifdef DEBUG
    std::cout << "New height of node: " << _root->getData() << " = " << _root->getHeight() << std::endl;
#endif
}

//// BALANCING THE TREE ////
template <class T>
int AVLTree<T>::getBalanceFactor(TreeNode<T> * _root)
{
    int balance_factor;
    int left_height = 0;
    int right_height = 0;

    // Base case
    if (_root == nullptr)
        return 0;

    // Get heights of branches
    if (_root->getLeft() != nullptr)
        left_height = _root->getLeft()->getHeight();
    if (_root->getRight() != nullptr)
        right_height = _root->getRight()->getHeight();
    // Compute balance factor
    balance_factor = left_height - right_height;
    return balance_factor;
}

template <class T>
TreeNode<T> * AVLTree<T>::balance(TreeNode<T> * _root)
{
    if (_root == nullptr)
        return _root;

#ifdef DEBUG
    std::cout << "Rebalancing the tree node: " << _root->getData() << std::endl;
#endif
    // Confirm that the heights are correct
    updateHeight(_root);
    // Right is heavier
    if (getBalanceFactor(_root) < -1)
    {
        // Left is heavier
        if (getBalanceFactor(_root->getLeft()) > 0)
        {
            // RL case
            _root->setRight(rotateRight(_root->getRight()));
        }
        // RR case
        _root = rotateLeft(_root);
    }
    // Left is heavier
    else if (getBalanceFactor(_root) > 1)
    {
        // Right is heavier
        if (getBalanceFactor(_root->getLeft()) < 0)
        {
            // LR case
            _root->setLeft(rotateLeft(_root->getLeft()));
        }
        // LL case
        _root = rotateRight(_root);
    }
    return _root;
}

template <class T>
TreeNode<T> * AVLTree<T>::rotateLeft(TreeNode<T> * _root)
{
#ifdef DEBUG
    std::cout << "Rotating LEFT node: " << _root->getData() << std::endl;
#endif
    TreeNode<T> * tmp;

    tmp = _root->getRight();
    _root->setRight(tmp->getLeft());
    tmp->setLeft(_root);
    updateHeight(_root);
    updateHeight(tmp);
    return tmp;
}

template <class T>
TreeNode<T> * AVLTree<T>::rotateRight(TreeNode<T> * _root)
{
#ifdef DEBUG
    std::cout << "Rotating RIGHT node: " << _root->getData() << std::endl;
#endif
    TreeNode<T> * tmp;

    tmp = _root->getLeft();
    _root->setLeft(tmp->getRight());
    tmp->setRight(_root);
    updateHeight(_root);
    updateHeight(tmp);
    return tmp;
}
#endif
