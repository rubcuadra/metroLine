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
#include <fstream>
#include <sstream>

std::vector<std::string> lineOneStations;
std::vector<std::string> lineTwoStations;
std::vector<int> lineOnexCoord;
std::vector<int> lineOneyCoord;
std::vector<int> lineTwoxCoord;
std::vector<int> lineTwoyCoord;
sf::Color pink = sf::Color::Color(253,99,171);
sf::Color brown = sf::Color::Color(76,39,21);

void Draw(GraphicDoubleLinkedList<std::string> * metroCDMX, int length)
{
    if (length<=0)
        return;
    //configure wndow
    sf::RenderWindow window(sf::VideoMode(1280, 768), "Metro Lines");
    window.setKeyRepeatEnabled(false);
    sf::Font font;
    //configure text
    sf::Text text;
    text.setFont(font);
    text.setString("CDMX Metro Map\n Press Space to move trains");
    text.setCharacterSize(20);
    text.setColor(sf::Color::Black);
    text.setPosition(30, 30);
    sf::Text lineOneText;
    lineOneText.setFont(font);
    lineOneText.setCharacterSize(12);
    lineOneText.setColor(pink);
    lineOneText.setPosition(30, 400);
    sf::Text lineTwoText;
    lineTwoText.setFont(font);
    lineTwoText.setCharacterSize(12);
    lineTwoText.setColor(brown);
    lineTwoText.setPosition(30, 420);
    //load font
    if (!font.loadFromFile("sansation.ttf"))
        std::cout << "Could not load font!\n" << std::endl;
    
    //window loop
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
                        for (int i=0;i<length;++i)
                            metroCDMX[i].moveCurrent();
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
        {
            metroCDMX[i].recursivePrintGraphical(metroCDMX[i].getHead(),window);
            if(i % 2 == 0)
                lineOneText.setString(metroCDMX[i].getCurrent()->getData());
            else
                lineTwoText.setString(metroCDMX[i].getCurrent()->getData());
        }
        window.draw(lineOneText);
        window.draw(lineTwoText);
        window.display();
    }
}


int GUIChoice()
{
    std::string ans = "0";
    std::cout << "Metro lines Menu" << std::endl;
    std::cout << "\ta) Search for a Station" << std::endl;
    std::cout << "\tb) Print Metro Lines" << std::endl;
    std::cout << "\tc) Print Metro Map" << std::endl;
    std::cout << "\td) Quit program" << std::endl;
    std::cout << "Select an option: ";
    std::cin >> ans;
    return ans.length()==1?ans[0]:'0';
}

void parseData()
{
    std::vector<std::string> stations;
    std::string filename = "stations.txt";
    std::string line;
    std::ifstream txtfile(filename);
    int line_index = 0;
    
    if(txtfile.is_open())
    {
        //get each line
        while(getline(txtfile, line))
        {
            int token_index = 0;
            std::istringstream ss(line);
            std::string token;
            bool first_line;
            
            if((line_index == 0) && (line[0] == '-'))
            {
                first_line = true;
            }
            else if(line_index != 0 && line[0] == '-')
            {
                first_line = false;
            }
            
            while(std::getline(ss, token, ','))
            {
                if(first_line == true)
                {
                    if(token_index == 0)
                    {
                        lineOneStations.push_back(token);
                        token_index++;
                    }
                    else if(token_index == 1)
                    {
                        lineOnexCoord.push_back(std::stoi(token,nullptr,10));
                        token_index++;
                    }
                    else if(token_index == 2)
                    {
                        lineOneyCoord.push_back(std::stoi(token,nullptr,10));
                        token_index++;
                    }
                }
                else if(first_line == false)
                {
                    if(token_index == 0)
                    {
                        lineTwoStations.push_back(token);
                        token_index++;
                    }
                    else if(token_index == 1)
                    {
                        lineTwoxCoord.push_back(std::stoi(token,nullptr,10));
                        token_index++;
                    }
                    else if(token_index == 2)
                    {
                        lineTwoyCoord.push_back(std::stoi(token,nullptr,10));
                        token_index++;
                    }
                }
            }
            line_index++;
        }
        txtfile.close();
    }
    return;
}

void main_menu()
{
    parseData();
    GraphicDoubleLinkedList<std::string> lineOne(pink);
    GraphicDoubleLinkedList<std::string> lineTwo(brown);
    
    for(int i = 1; i != lineOneStations.size(); i++)
    {
        lineOne.insertTail(new GraphicDoubleNode<std::string>(lineOneStations[i], *new sf::Vector2f(lineOnexCoord[i - 1],lineOneyCoord[i - 1])));
    }
    for(int j = 1; j != lineTwoStations.size(); j++)
    {
        lineTwo.insertTail(new GraphicDoubleNode<std::string>(lineTwoStations[j], *new sf::Vector2f(lineTwoxCoord[j - 1],lineTwoyCoord[j - 1])));
    }
    
    int totalLines = 2;
    GraphicDoubleLinkedList<std::string> * metroCDMX = new GraphicDoubleLinkedList<std::string>[totalLines];
    metroCDMX[0] = lineOne;
    metroCDMX[1] = lineTwo;
    std::string stationToSearch;
    int choice;bool stationSearch;
    do
    {
        choice = GUIChoice();
        switch (choice)
        {
            case 'a': //SearchForStation
                stationSearch=false;
                std::cout<<"Que estacion desea buscar?\n";
                std::cin>>stationToSearch;
                for (int i=0; i<totalLines; ++i)
                {
                    if(metroCDMX[i].searchFor(stationToSearch))
                    {
                        std::string msg="La estacion "+stationToSearch+" se encuentra en la linea "+std::to_string(i+1);
                        GraphicDoubleNode<std::string> *temp= metroCDMX[i].getCurrent();
                        if (temp->getPrevious())
                            msg= msg+" despues de la estacion "+temp->getPrevious()->getData()+" y"+(temp->getNext()?"":"es la ultima estacion");
                        if (temp->getNext())
                            msg= msg+" antes de la estacion "+temp->getNext()->getData();
                        stationSearch=true;
                        msg=msg+"\nSeleccione la opcion 'C' para ver la estacion en el mapa";
                        std::cout<<msg;
                        break;
                    }
                }
                std::cout<<(stationSearch?"\n":"No se encontro ninguna estacion con ese nombre\n");
                break;
            case 'b': //Print in console
                std::cout<<"\n";
                for (int i=0; i<totalLines; ++i)
                {
                    std::cout<<"Line "<<std::to_string(i+1)<<":\n";
                    metroCDMX[i].printList();
                }
                break;
            case 'c': //Print Graphical
                Draw(metroCDMX,totalLines);
                break;
            case 'd': //Quit
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Incorrect option. Try again ..." << std::endl;
                break;
        }
    }while (choice != 'd');
}
    
int main()
{
    main_menu();
    return 0;
}