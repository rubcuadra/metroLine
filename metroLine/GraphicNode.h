#pragma once
#include <SFML/Graphics.hpp>
#include "TreeNode.h"

template <class T>
class GraphicNode : public TreeNode<T> {
private:
	sf::CircleShape circle;
	sf::Text text;
    sf::Vector2f position;
public:
    GraphicNode() {}
	GraphicNode(const T & _data);
	GraphicNode(const T & _data, const sf::Font & _font, sf::Color _color = sf::Color::Yellow, int _radius = 50);
    void configure(const T & _data, const sf::Font & _font, sf::Color _color = sf::Color::Yellow, int _radius = 50);
    void configure(const sf::Font & _font, sf::Color _color = sf::Color::Yellow, int _radius = 50);
	void draw(sf::RenderWindow & _window);
    void setPosition(const sf::Vector2f & _position);
    sf::Vector2f getPosition();
};

template <class T>
GraphicNode<T>::GraphicNode(const T & _data)
{
    // Store the data for the TreeNode
    this->setData(_data);
}

template <class T>
GraphicNode<T>::GraphicNode(const T & _data, const sf::Font & _font, sf::Color _color, int _radius)
{
    configure(_data, _font, _color, _radius);
}

template <class T>
void GraphicNode<T>::configure(const T & _data, const sf::Font & _font, sf::Color _color, int _radius)
{
    // Store the data for the TreeNode
    this->setData(_data);
    // Configure the visual representation
    configure(_font, _color, _radius);
}

template <class T>
void GraphicNode<T>::configure(const sf::Font & _font, sf::Color _color, int _radius)
{
    // Configure the circle
	circle.setRadius(_radius);
	circle.setFillColor(_color);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(5);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    // Configure the text object
	text.setFont(_font);
	text.setCharacterSize(24);
	text.setColor(sf::Color::Black);
    // Center the origin of the text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
}

template <class T>
void GraphicNode<T>::draw(sf::RenderWindow & _window)
{
	_window.draw(circle);
    // Set the string to be equal to the data
	text.setString(std::to_string(this->getData()));
	_window.draw(text);
}

template <class T>
void GraphicNode<T>::setPosition(const sf::Vector2f & _position)
{
    position = _position;
    circle.setPosition(position);
    text.setPosition(position);
}

template <class T>
sf::Vector2f GraphicNode<T>::getPosition()
{
    return position;
}
