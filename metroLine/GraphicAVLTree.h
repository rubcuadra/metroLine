/*
   Implementation of an AVL Tree
   Based on the algorithms at:
    http://kukuruku.co/hub/cpp/avl-trees
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <iomanip>
#include "GraphicNode.h"
//#include "Queue.h"

#define DEBUG
#define CIRCLE_RADIUS 20
#define H_OFFSET 30
#define V_OFFSET 60

template <class T>
class GraphicAVLTree {
private:
	GraphicNode<T> * root;
    //Queue<GraphicNode<T>*> queue;
    int height;

	void recursivePrintInorder(GraphicNode<T> * _root);
    void recursivePrintTree(GraphicNode<T> * _root, int y=0);
    int recursivePrintGraphical(GraphicNode<T> * _root, int x, int y, sf::RenderWindow & window, const sf::Font & font);
	bool recursiveSearch(GraphicNode<T> * _root, int _data);
	void recursiveClear(GraphicNode<T> * _root);
	GraphicNode<T> * recursiveInsert(GraphicNode<T> * _root, GraphicNode<T> * _node);
    GraphicNode<T> * recursiveRemove(GraphicNode<T> * _root, int _data);
    GraphicNode<T> * getMin(GraphicNode<T> * _root);
    GraphicNode<T> * balance(GraphicNode<T> * _root);
    GraphicNode<T> * rotateRight(GraphicNode<T> * _root);
    GraphicNode<T> * rotateLeft(GraphicNode<T> * _root);
    int recursiveFindHeight(GraphicNode<T> * _root);
    void updateHeight(GraphicNode<T> * _root);
    int getBalanceFactor(GraphicNode<T> * _root);
public:
	GraphicAVLTree();
	~GraphicAVLTree();
	void insertNode(const T & _data);
	void insertNode(GraphicNode<T> * _node);
	bool search(int _data);
	GraphicNode<T> * getRoot();
	void setRoot(GraphicNode<T> * _node);
	void printInorder();
    //void printBreadthFirst();
    void printTree();
    void printGraphical();
    void remove(int _data);
	void clear();
	int findHeight();
	int getHeight();
};

template <class T>
GraphicAVLTree<T>::GraphicAVLTree()
{
    this->root = nullptr;
}

template <class T>
GraphicAVLTree<T>::~GraphicAVLTree()
{
    this->clear();
}

template <class T>
GraphicNode<T> * GraphicAVLTree<T>::getRoot()
{
	return this->root;
}

template <class T>
void GraphicAVLTree<T>::setRoot(GraphicNode<T> * _node)
{
    this->root = _node;
}

//// PRINTING THE DATA IN THE TREE ////
template <class T>
void GraphicAVLTree<T>::printInorder()
{
	if (this->root == nullptr)
		return;
	recursivePrintInorder(this->root);
	std::cout << std::endl;
}

template <class T>
void GraphicAVLTree<T>::recursivePrintInorder(GraphicNode<T> * _root)
{
	if (_root == nullptr)
		return;

	recursivePrintInorder(static_cast<GraphicNode<T>*>(_root->getLeft()));
	std::cout << _root->getData() << "\t";
	recursivePrintInorder(static_cast<GraphicNode<T>*>(_root->getRight()));
}

template <class T>
void GraphicAVLTree<T>::printTree()
{
	if (this->root == nullptr)
		return;
    recursivePrintTree(this->root, 2);
}

template <class T>
void GraphicAVLTree<T>::recursivePrintTree(GraphicNode<T> * _root, int indent)
{
    if(_root != nullptr)
    {
        if(_root->getRight())
            recursivePrintTree(static_cast<GraphicNode<T>*>(_root->getRight()), indent+4);
        if (indent)
        {
            std::cout << std::setw(indent) << ' ';
        }
        std::cout << _root->getData() << " (" << _root->getHeight() << ")" << std::endl;
        if(_root->getLeft())
            recursivePrintTree(static_cast<GraphicNode<T>*>(_root->getLeft()), indent+4);
    }
}


template <class T>
void GraphicAVLTree<T>::printGraphical()
{
	if (this->root == nullptr)
		return;

	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test application");
    // Create a font
    sf::Font font;
	// Load the font
	if (!font.loadFromFile("Akashi.ttf"))
	//if (!font.loadFromFile("heavy_data.ttf"))
	{
		std::cout << "Could not load font!\n" << std::endl;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
        // Call the recursive function to draw the tree
        recursivePrintGraphical(this->root, 50, 50, window, font);
		window.display();
	}
}

template <class T>
int GraphicAVLTree<T>::recursivePrintGraphical(GraphicNode<T> * _root, int x, int y, sf::RenderWindow & window, const sf::Font & font)
{
    if(_root != nullptr)
    {
        // Draw left branch
        if(_root->getLeft())
            x += recursivePrintGraphical(static_cast<GraphicNode<T>*>(_root->getLeft()), x, y+H_OFFSET, window, font);
        // Draw the node
        _root->configure(font, sf::Color::Blue, CIRCLE_RADIUS);
        _root->setPosition(sf::Vector2f(x, y));
        //std::cout << "Drawing node: " << _root->getData() << " at position: " << x << ", " << y << std::endl;
        _root->draw(window);
        // Draw right branch
        if(_root->getRight())
            recursivePrintGraphical(static_cast<GraphicNode<T>*>(_root->getRight()), x+V_OFFSET, y+H_OFFSET, window, font);
        // Draw links betwen nodes
        if(_root->getLeft())
        {

        }
        if(_root->getRight())
        {

        }
        return x + V_OFFSET;
    }
    return 0;
}


/*
template <class T>
void GraphicAVLTree<T>::printBreadthFirst()
{
    if (this->root == nullptr)
        return;
    GraphicNode<T> * item;
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
*/

//// CLEAR THE TREE ////
template <class T>
void GraphicAVLTree<T>::clear()
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
void GraphicAVLTree<T>::recursiveClear(GraphicNode<T> * _root)
{
    if (_root == nullptr)
        return;
    recursiveClear(static_cast<GraphicNode<T>*>(_root->getLeft()));
    recursiveClear(static_cast<GraphicNode<T>*>(_root->getRight()));
    delete _root;
}

//// INSERT NEW NODES ////
template <class T>
void GraphicAVLTree<T>::insertNode(const T & _data)
{
	GraphicNode<T> * new_node = new GraphicNode<T>(_data);
	this->insertNode(new_node);
}

template <class T>
void GraphicAVLTree<T>::insertNode(GraphicNode<T> * _node)
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
GraphicNode<T> * GraphicAVLTree<T>::recursiveInsert(GraphicNode<T> * _root, GraphicNode<T> * _node)
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
			_root->setLeft(recursiveInsert(static_cast<GraphicNode<T>*>(_root->getLeft()), _node));
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
			_root->setRight(recursiveInsert(static_cast<GraphicNode<T>*>(_root->getRight()), _node));
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
bool GraphicAVLTree<T>::search(int _data)
{
	if (this->root == nullptr)
		return false;
	else
		return recursiveSearch(this->root, _data);
}

template <class T>
bool GraphicAVLTree<T>::recursiveSearch(GraphicNode<T> * _root, int _data)
{
	if (_root->getData() == _data)
		return true;
	else
	{
		if (_data < _root->getData())
		{
			if (_root->getLeft() == nullptr)
				return false;
			return recursiveSearch(static_cast<GraphicNode<T>*>(_root->getLeft()), _data);
		}
		else
		{
			if (_root->getRight() == nullptr)
				return false;
			return recursiveSearch(static_cast<GraphicNode<T>*>(_root->getRight()), _data);
		}
	}
}

//// REMOVING NODES FROM A TREE ////
template <class T>
GraphicNode<T> * GraphicAVLTree<T>::getMin(GraphicNode<T> * _root)
{
    if (_root->getLeft() == nullptr)
        return _root;
    else
        return getMin(static_cast<GraphicNode<T>*>(_root->getLeft()));
}

template <class T>
void GraphicAVLTree<T>::remove(int _data)
{
    if (this->root == nullptr)
        return;
    this->root = recursiveRemove(this->root, _data);
}

template <class T>
GraphicNode<T> * GraphicAVLTree<T>::recursiveRemove(GraphicNode<T> * _root, int _data)
{
    if (_root == nullptr)
        return nullptr;
    if (_data < _root->getData())
    {
        _root->setLeft( recursiveRemove(static_cast<GraphicNode<T>*>(_root->getLeft()), _data) );
    }
    else if (_data > _root->getData())
    {
        _root->setRight( recursiveRemove(static_cast<GraphicNode<T>*>(_root->getRight()), _data) );
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
            GraphicNode<T> * tmp = _root;
            _root = static_cast<GraphicNode<T>*>(_root->getLeft());
            delete tmp;
        }
        // Node has only right child
        else if (_root->getLeft() == nullptr)
        {
            std::cout << "Deleting with only right branch" << std::endl;
            GraphicNode<T> * tmp = _root;
            _root = static_cast<GraphicNode<T>*>(_root->getRight());
            delete tmp;
        }
        // Node has both children
        else
        {
            std::cout << "Deleting with both branches" << std::endl;
            GraphicNode<T> * tmp = getMin(static_cast<GraphicNode<T>*>(_root->getRight()));
            _root->setData(tmp->getData());
            _root->setRight(recursiveRemove(static_cast<GraphicNode<T>*>(_root->getRight()), tmp->getData()));
        }
    }
    // Rebalance the node after the insertion
    return balance(_root);
}

//// COMPUTE THE HEIGHT OF THE TREE AND THE NODES ////
template <class T>
int GraphicAVLTree<T>::recursiveFindHeight(GraphicNode<T> * _root)
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
int GraphicAVLTree<T>::findHeight()
{
    if (this->root == nullptr)
        return -1;
    return recursiveFindHeight(this->root); 
}

template <class T>
int GraphicAVLTree<T>::getHeight()
{
    return height;
}

template <class T>
void GraphicAVLTree<T>::updateHeight(GraphicNode<T> * _root)
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
int GraphicAVLTree<T>::getBalanceFactor(GraphicNode<T> * _root)
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
GraphicNode<T> * GraphicAVLTree<T>::balance(GraphicNode<T> * _root)
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
        if (getBalanceFactor(static_cast<GraphicNode<T>*>(_root->getLeft())) > 0)
        {
            // RL case
            _root->setRight(rotateRight(static_cast<GraphicNode<T>*>(_root->getRight())));
        }
        // RR case
        _root = rotateLeft(_root);
    }
    // Left is heavier
    else if (getBalanceFactor(_root) > 1)
    {
        // Right is heavier
        if (getBalanceFactor(static_cast<GraphicNode<T>*>(_root->getLeft())) < 0)
        {
            // LR case
            _root->setLeft(rotateLeft(static_cast<GraphicNode<T>*>(_root->getLeft())));
        }
        // LL case
        _root = rotateRight(_root);
    }
    return _root;
}

template <class T>
GraphicNode<T> * GraphicAVLTree<T>::rotateLeft(GraphicNode<T> * _root)
{
#ifdef DEBUG
    std::cout << "Rotating LEFT node: " << _root->getData() << std::endl;
#endif
    GraphicNode<T> * tmp;

    tmp = static_cast<GraphicNode<T>*>(_root->getRight());
    _root->setRight(static_cast<GraphicNode<T>*>(tmp->getLeft()));
    tmp->setLeft(_root);
    updateHeight(_root);
    updateHeight(tmp);
    return tmp;
}

template <class T>
GraphicNode<T> * GraphicAVLTree<T>::rotateRight(GraphicNode<T> * _root)
{
#ifdef DEBUG
    std::cout << "Rotating RIGHT node: " << _root->getData() << std::endl;
#endif
    GraphicNode<T> * tmp;

    tmp = static_cast<GraphicNode<T>*>(_root->getLeft());
    _root->setLeft(static_cast<GraphicNode<T>*>(tmp->getRight()));
    tmp->setRight(_root);
    updateHeight(_root);
    updateHeight(tmp);
    return tmp;
}
#endif
