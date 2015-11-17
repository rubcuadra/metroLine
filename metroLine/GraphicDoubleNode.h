//
//  GraphicDoubleNode.h
//  metroLine
//
//  Created by Ruben Cuadra on 11/17/15.
//  Copyright © 2015 Estructuras. All rights reserved.
//

#pragma once
/* GraphicDoubleNode_h */
#include <SFML/Graphics.hpp>

template <class T>
class GraphicDoubleNode
{
private:
    sf::CircleShape circle;
    sf::Text text;
    sf::Vector2f position;
    T data;
    GraphicDoubleNode * next = nullptr;
    GraphicDoubleNode * previous = nullptr;
public:
    GraphicDoubleNode() {}
    ~GraphicDoubleNode();
    GraphicDoubleNode(const T & _data);
    GraphicDoubleNode(const T & _data, const sf::Font & _font, sf::Color _color = sf::Color::Yellow, int _radius = 50);
    void configure(const T & _data, const sf::Font & _font, sf::Color _color = sf::Color::Yellow, int _radius = 50);
    void configure(const sf::Font & _font, sf::Color _color = sf::Color::Yellow, int _radius = 50);
    void draw(sf::RenderWindow & _window);
    void setPosition(const sf::Vector2f & _position);
    sf::Vector2f getPosition();
    T getData(){return this->data;}
    void setData(T _item){this->data = _item;}
    GraphicDoubleNode * getNext(){return this->next;}
    void setNext(GraphicDoubleNode* next_node){this->next = next_node;}
    GraphicDoubleNode * getPrevious(){return this->previous;}
    void setPrevious(GraphicDoubleNode* prev_node){this->previous = prev_node;}
};

template <class T>
GraphicDoubleNode<T>::~GraphicDoubleNode()
{
    data.~T();
    next = nullptr;
    previous = nullptr;
}

template <class T>
GraphicDoubleNode<T>::GraphicDoubleNode(const T & _data)
{
    // Store the data for the TreeNode
    this->setData(_data);
}

template <class T>
GraphicDoubleNode<T>::GraphicDoubleNode(const T & _data, const sf::Font & _font, sf::Color _color, int _radius)
{
    configure(_data, _font, _color, _radius);
}

template <class T>
void GraphicDoubleNode<T>::configure(const T & _data, const sf::Font & _font, sf::Color _color, int _radius)
{
    // Store the data for the TreeNode
    this->setData(_data);
    // Configure the visual representation
    configure(_font, _color, _radius);
}
template <class T>
void GraphicDoubleNode<T>::configure(const sf::Font & _font, sf::Color _color, int _radius)
{
    circle.setRadius(_radius);
    circle.setFillColor(_color);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(1);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    
    text.setFont(_font);
    text.setCharacterSize(12);
    text.setColor(sf::Color::Black);
    
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
}

template <class T>
void GraphicDoubleNode<T>::draw(sf::RenderWindow & _window)
{
    _window.draw(circle);
    text.setString(this->getData());
    _window.draw(text);
}

template <class T>
void GraphicDoubleNode<T>::setPosition(const sf::Vector2f & _position)
{
    position = _position;
    circle.setPosition(position);
    text.setPosition(position);
}

template <class T>
sf::Vector2f GraphicDoubleNode<T>::getPosition()
{
    return position;
}