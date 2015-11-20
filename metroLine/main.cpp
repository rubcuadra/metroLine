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


int GUIChoice()
{
    std::string ans = "0";
    std::cout << "Metro lines Menu" << std::endl;
    std::cout << "\ta. Add Station" << std::endl;
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

std::vector<std::string> parseStations()
{
    std::vector<std::string> stations;
    std::vector<std::string> aux;
    std::string filename = "/Users/luisgaji/Code/ProyectoItesm/stations.txt";
    //string to represent each line
    std::string line;
    std::ifstream txtfile(filename);
    if(txtfile.is_open())
    {
        //get each line
        while(getline(txtfile, line))
        {
            std::cout << line << std::endl;
            stations.push_back(line);
        }
        txtfile.close();
    }
    return stations;
}

void main_menu()
{
    parseStations();
    GraphicDoubleLinkedList<std::string> lineOne;
    std::string station;
    int choice;
    do
    {
        choice = GUIChoice();
        switch (choice)
        {
            case 'a':
                std::cout << "Enter the Station to add: ";
                std::cin >> station;
                lineOne.insertTail(station);
                break;
            case 'b': //Remove Station
                break;
            case 'c': //SearchForStation
                break;
            case 'd': //ClearLine
                break;
            case 'e': //Print Metro Lines
                lineOne.printList();
                break;
            case 'f': //Print Metro Map
                lineOne.printGraphical();
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