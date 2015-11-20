//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GraphicDoubleLinkedList.h"
#include "GraphicDoubleNode.h"

void Draw(GraphicDoubleLinkedList<std::string> * metroCDMX, int length)
{
    if (length<=0)
        return;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Metro Lines");
    window.setKeyRepeatEnabled(false);
    sf::Font font;
    sf::Text text;
    text.setFont(font);
    text.setString("CDMX Metro Map\n Press Space to move trains");
    text.setCharacterSize(12);
    text.setColor(sf::Color::Black);
    text.setPosition(30, 30);
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
                    if (event.key.code == sf::Keyboard::Space) //Space moves current
                    {
                        for (int i=0;i<length;++i)
                            metroCDMX[i].moveCurrent();
                    }
                    break;
                case sf::Event::KeyReleased:
                    break;
                default:
                    break;
            }
        }
        window.clear(sf::Color::White);
        window.draw(text);
        for (int i = 0; i<length; ++i)
            metroCDMX[i].recursivePrintGraphical(metroCDMX[i].getHead(),window, font);
        window.display();
    }
}


int GUIChoice()
{
    std::string ans = "0";
    std::cout << "Metro lines Menu" << std::endl;
    //std::cout << "\ta. Add Station" << std::endl;
    std::cout << "\tb. Remove Station" << std::endl;
    std::cout << "\tc. Search for a Station" << std::endl;
    std::cout << "\td. Clear Line" << std::endl;
    std::cout << "\te. Print Metro Lines" << std::endl;
    std::cout << "\tf. Print Metro Map" << std::endl;
    std::cout << "\tq. Quit program" << std::endl;
    std::cout << "Select an option: ";
    std::cin >> ans;
    return ans.length()==1?ans[0]:'0';
}

void main_menu()
{
    GraphicDoubleLinkedList<std::string> lineOne;
    GraphicDoubleLinkedList<std::string> lineTwo;
    
    lineOne.insertTail(new GraphicDoubleNode<std::string>("Sevilla", *new sf::Vector2f(100,150)));
    lineOne.insertTail(new GraphicDoubleNode<std::string>("Hidalgo", *new sf::Vector2f(150,130)));
    lineOne.insertTail(new GraphicDoubleNode<std::string>("Pino Suarez", *new sf::Vector2f(200,200)));
    
    lineTwo.insertTail(new GraphicDoubleNode<std::string>("Balderas", *new sf::Vector2f(100,350)));
    lineTwo.insertTail(new GraphicDoubleNode<std::string>("Ojo Agua", *new sf::Vector2f(150,330)));
    lineTwo.insertTail(new GraphicDoubleNode<std::string>("Zocalo", *new sf::Vector2f(200,290)));
    lineTwo.insertTail(new GraphicDoubleNode<std::string>("Otra", *new sf::Vector2f(220,220)));
    
    int totalLines = 2;
    GraphicDoubleLinkedList<std::string> * metroCDMX = new GraphicDoubleLinkedList<std::string>[totalLines];
    metroCDMX[0] = lineOne;
    metroCDMX[1] = lineTwo;

    int choice;
    do
    {
        choice = GUIChoice();
        switch (choice)
        {
            case 'b': //Remove Station
                break;
            case 'c': //SearchForStation
                break;
            case 'd': //ClearLine
                break;
            case 'e': //Print Metro Lines
                for (int i=0; i<totalLines; ++i)
                {
                    metroCDMX[i].printList();
                }
                break;
            case 'f': //Print Metro Map
                Draw(metroCDMX,totalLines);
                break;
            case 'g': //Quit
                break;
            case 'q':
                break;
            default:
                std::cout << "Incorrect option. Try again ..." << std::endl;
                break;
        }
    }while (choice != 'q');
}
int main()
{
    main_menu();
    return 0;
}