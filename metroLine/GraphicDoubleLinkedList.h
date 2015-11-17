//
//  GraphicDoubleLinkedList.h
//  metroLine
//
//  Created by Ruben Cuadra on 11/17/15.
//  Copyright © 2015 Estructuras. All rights reserved.
//

#pragma once 
/* GraphicDoubleLinkedList_h */
#include <iostream>
#include <iomanip>
#include "GraphicDoubleNode.h"
//#include "Queue.h"

#define DEBUG
#define CIRCLE_RADIUS 20
#define H_OFFSET 60
#define V_OFFSET 100

template <class T>
class GraphicDoubleLinkedList
{
protected:
    GraphicDoubleNode<T> * head = nullptr;
    GraphicDoubleNode<T> * tail = nullptr;
    GraphicDoubleNode<T> * current = nullptr;
    int length = 0;
    int recursivePrintGraphical(GraphicDoubleNode<T> * _root, int x, int y, sf::RenderWindow & window, const sf::Font & font);
public:
    ~GraphicDoubleLinkedList();
    GraphicDoubleLinkedList () {}
    GraphicDoubleLinkedList (GraphicDoubleNode<T> * item) { head = item; }
    int getLength() { return this->length; }
    int getPositionOf(GraphicDoubleNode<T> * item);
    GraphicDoubleNode<T> * getHead() { return this->head; }
    GraphicDoubleNode<T> * getTail() { return this->tail; }
    GraphicDoubleNode<T> * getCurrent() { return this->current; }
    GraphicDoubleNode<T> * getItemAt(int position);
    void insertOrdered(GraphicDoubleNode<T> * new_item);
    void insertOrdered(const T & data);
    void insertAtPosition(GraphicDoubleNode<T> * new_item, int position);
    void insertAtPosition(const T & data, int position);
    void insertHead(GraphicDoubleNode<T> * new_item);
    void insertHead(const T & data);
    void insertTail(GraphicDoubleNode<T> * new_item);
    void insertTail(const T & data);
    GraphicDoubleNode<T> * removeItemAt(int position);
    GraphicDoubleNode<T> * removeHead();
    GraphicDoubleNode<T> * removeTail();
    void removeNode(GraphicDoubleNode<T> item);
    bool searchFor(const T & data);
    void printList();
    void clear();
    void printGraphical();
};

template <class T>
GraphicDoubleLinkedList<T>::~GraphicDoubleLinkedList()
{
    this->clear();
}

// Add items to the list
template <class T>
void GraphicDoubleLinkedList<T>::insertTail(GraphicDoubleNode<T> * new_item)
{
    // Make sure to stop the pointer in the list
    new_item->setNext(nullptr);
    
    // If the list is empty, this node is the new head
    if (this->head == nullptr)
    {
        this->head = new_item;
        this->tail = new_item;
    }
    else
    {
        this->tail->setNext(new_item);
        new_item->setPrevious(this->tail);
        this->tail = new_item;
    }
    // Increment the size of the list
    this->length++;
}

template <class T>
void GraphicDoubleLinkedList<T>::insertTail(const T & data)
{
    GraphicDoubleNode<T> * item = new GraphicDoubleNode<T>(data);
    this->insertTail(item);
}

template <class T>
void GraphicDoubleLinkedList<T>::insertHead(GraphicDoubleNode<T> * new_item)
{
    // If the list was empty
    if (this->head == nullptr)
        this->tail = new_item;
    else
        // Make the previous head point to the new one
        this->head->setPrevious(new_item);
    
    // Make this node point to the previous head
    new_item->setNext(this->head);
    // The node becomes the head of the list
    this->head = new_item;
    // Increment the size of the list
    this->length++;
}

template <class T>
void GraphicDoubleLinkedList<T>::insertHead(const T & data)
{
    GraphicDoubleNode<T> * item = new GraphicDoubleNode<T>(data);
    this->insertHead(item);
}

/*
 Inserts node elements in their corresponding place, in increasing order of exponent
 */
template <class T>
void GraphicDoubleLinkedList<T>::insertOrdered(GraphicDoubleNode<T> * new_item)
{
    // Special case when the list is empty
    //  or the new item is the smallest
    if ( this->head == nullptr || new_item->getData() < this->head->getData() )
    {
        // Update the tail when necessary
        if (this->head == nullptr)
        {
            this->tail = new_item;
            // Update the current node
            this->current = new_item;
        }
        else
        {
            // Link the previous head to the new item
            this->head->setPrevious(new_item);
        }
        // Make the new item point to the current head
        new_item->setNext(this->head);
        // Update the head
        this->head = new_item;
    }
    // Check if the item should be inserted last
    else if (new_item->getData() >= this->tail->getData())
    {
        this->tail->setNext(new_item);
        new_item->setPrevious(this->tail);
        this->tail = new_item;
    }
    else
    {
        GraphicDoubleNode<T> * previous = this->head;
        GraphicDoubleNode<T> * item = static_cast<GraphicDoubleNode<T>*>(previous->getNext());
        // Loop to search for the item
        while (item != nullptr && new_item->getData() > item->getData())
        {
            previous = item;
            item = static_cast<GraphicDoubleNode<T>*>(item->getNext());
        }
        // Update the connections in the list
        new_item->setPrevious(previous);
        new_item->setNext(item);
        previous->setNext(new_item);
        if (item != nullptr)
            item->setPrevious(new_item);
    }
    // Increase the length of the list
    this->length++;
}

/*
 Inserts new terms in the polynomial list, in increasing order of exponent
 */
template <class T>
void GraphicDoubleLinkedList<T>::insertOrdered(const T & data)
{
    GraphicDoubleNode<T> * item = new GraphicDoubleNode<T>(data);
    this->insertOrdered(item);
}

template <class T>
void GraphicDoubleLinkedList<T>::insertAtPosition(GraphicDoubleNode<T> * new_item, int position)
{
    int index = 1;
    GraphicDoubleNode<T> * item = this->head;
    
    // Return nothing for invalid positions
    if (position > this->length || position < 0)
    {
        return;
    }
    // Position is the last item in the list
    if (position == this->length)
    {
        this->tail = new_item;
    }
    // Special case when adding at position 0
    if (position == 0)
    {
        // Make the new item point to the current head
        new_item->setNext(this->head);
        // Make the previous head point to the new one
        this->head->setPrevious(new_item);
        // Update the head
        this->head = new_item;
    }
    else
    {
        // Loop to search for the item
        while (index < position)
        {
            item = item->getNext();
            index++;
        }
        // Update the connections in the list
        new_item->setNext(item->getNext());
        new_item->setPrevious(item);
        item->getNext()->setPrevious(new_item);
        item->setNext(new_item);
    }
    // Increase the length of the list
    this->length++;
}


template <class T>
void GraphicDoubleLinkedList<T>::insertAtPosition(const T & data, int position)
{
    GraphicDoubleNode<T> * item = new GraphicDoubleNode<T>(data);
    this->insertAtPosition(item, position);
}

template <class T>
int GraphicDoubleLinkedList<T>::getPositionOf(GraphicDoubleNode<T> * search_item)
{
    int index = 0;
    GraphicDoubleNode<T> * item = this->head;
    
    while ( item != nullptr && search_item->getData() != item->getData() )
    {
        item = item->getNext();
        index++;
    }
    if (index == this->length)
        return -1;
    return index;
}

template <class T>
GraphicDoubleNode<T> * GraphicDoubleLinkedList<T>::getItemAt(int position)
{
    int index = 0;
    GraphicDoubleNode<T> * item = this->head;
    
    // Return nothing for invalid positions
    if (position > this->length || position < 0)
    {
        return nullptr;
    }
    // Loop to search for the item
    while (index < position && item != nullptr)
    {
        item = item->getNext();
        index++;
    }
    return item;
}

template <class T>
GraphicDoubleNode<T> * GraphicDoubleLinkedList<T>::removeHead()
{
    GraphicDoubleNode<T> * item = this->head;
    
    // Clear the tail also when the head is the only item in the list
    if (this->head == this->tail)
    {
        this->tail = nullptr;
    }
    // Check that the list is not empty
    if (this->head != nullptr)
    {
        // Make the head point to the second item
        this->head = item->getNext();
        // Make the item point to nothing
        item->setNext(nullptr);
        // Clear the previous of the new head
        this->head->setPrevious(nullptr);
        // Reduce the length of the list
        this->length--;
    }
    
    return item;
}

template <class T>
GraphicDoubleNode<T> * GraphicDoubleLinkedList<T>::removeTail()
{
    GraphicDoubleNode<T> * tail = this->tail;
    GraphicDoubleNode<T> * previous;
    
    if (this->head == nullptr)
    {
        return nullptr;
    }
    if (tail->getPrevious() == nullptr)
    {
        this->head = nullptr;
        this->tail = nullptr;
    }
    else
    {
        previous = tail->getPrevious();
        previous->setNext(nullptr);
        this->tail = previous;
    }
    tail->setPrevious(nullptr);
    this->length--;
    
    return tail;
}


template <class T>
GraphicDoubleNode<T> * GraphicDoubleLinkedList<T>::removeItemAt(int position)
{
    int index = 1;
    GraphicDoubleNode<T> * previous = this->head;
    GraphicDoubleNode<T> * item;
    
    if (position > this->length || position < 0)
        return nullptr;
    
    // If removing the last item, change the tail
    if (position == this->length-1)
    {
        this->tail = this->tail->getPrevious();
    }
    // Special case when removing the first item
    if (position == 0)
    {
        item = previous;
        this->head = item->getNext();
    }
    else
    {
        item = previous->getNext();
        while (index < position)
        {
            previous = item;
            item = item->getNext();
            index++;
        }
        previous->setNext(item->getNext());
        item->getNext()->setPrevious(previous);
    }
    
    item->setNext(nullptr);
    item->setPrevious(nullptr);
    this->length--;
    return item;
}

template <class T>
void GraphicDoubleLinkedList<T>::removeNode(GraphicDoubleNode<T> item)
{
    GraphicDoubleNode<T> * list_item = this->head;
    int index = 0;
    if (list_item == nullptr)
        return;
    while (list_item->getData() != item.getData())
    {
        list_item = list_item->getNext();
        index++;
    }
    if (index < getLength())
        removeItemAt(index);
}

template <class T>
bool GraphicDoubleLinkedList<T>::searchFor(const T & search_data)
{
    int count = 0;
    if (this->head == nullptr)
        return false;
    if (this->current == nullptr)
        this->current = this->head;
    if (search_data == this->current->getData())
        return true;
    else if (search_data > this->current->getData())
    {
        std::cout << "Searching forward" << std::endl;
        while (this->current != nullptr)
        {
            if (search_data == this->current->getData())
            {
                std::cout << "Found after " << count << " checks." << std::endl;
                return true;
            }
            this->current = static_cast<GraphicDoubleNode<T>*>(this->current->getNext());
            count++;
        }
        if (this->current == nullptr)
        {
            this->current = this->tail;
        }
    }
    else if (search_data < this->current->getData())
    {
        std::cout << "Searching backwards" << std::endl;
        while (this->current != nullptr)
        {
            if (search_data == this->current->getData())
            {
                std::cout << "Found after " << count << " checks." << std::endl;
                return true;
            }
            this->current = this->current->getPrevious();
            count++;
        }
        if (this->current == nullptr)
        {
            this->current = this->head;
        }
    }
    return false;
}

template <class T>
void GraphicDoubleLinkedList<T>::printList()
{
    GraphicDoubleNode<T> * item;
    int counter = 0;
    
    item = this->head;
    while (item != nullptr)
    {
        std::cout << "Item " << counter++ << " = " << item->getData() << std::endl;
        item = static_cast<GraphicDoubleNode<T>*>(item->getNext());
    }
}

template <class T>
void GraphicDoubleLinkedList<T>::clear()
{
    GraphicDoubleNode<T> * item;
    
    item = this->head;
    while (item != nullptr)
    {
        std::cout << "Deleting item " << item->getData() << std::endl;
        this->head = static_cast<GraphicDoubleNode<T>*>(item->getNext());
        delete item;
        item = this->head;
    }
    this->length = 0;
    this->head = nullptr;
}




template <class T>
void GraphicDoubleLinkedList<T>::printGraphical()
{
    if (this->length == 0)
        std::cout<<"Empty Metro\n";
        return;
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Metro Lines");
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf"))
        std::cout << "Could not load font!\n" << std::endl;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    break;
                default:
                    break;
            }

        }
        
        window.clear(sf::Color::White);
        recursivePrintGraphical(this->head, 50, 50, window, font);
        window.display();
    }
}

template <class T>
int GraphicDoubleLinkedList<T>::recursivePrintGraphical(GraphicDoubleNode<T> * node, int x, int y, sf::RenderWindow & window, const sf::Font & font)
{
    if(node != nullptr)
    {
        node->configure(font, sf::Color::Blue, CIRCLE_RADIUS);
        node->setPosition(sf::Vector2f(x, y));
        node->draw(window);
        if(node->getNext())
            recursivePrintGraphical(static_cast<GraphicDoubleNode<T>*>(node->getNext()), x+V_OFFSET,y, window, font);
        return x + V_OFFSET;
    }
    return 0;
}
/*
 sf::Text text;
 text.setFont(font);
 text.setString("Metro Map ITESM CSF");
 text.setCharacterSize(24);
 text.setColor(sf::Color::Black);
 text.setPosition(30, 30);
*/