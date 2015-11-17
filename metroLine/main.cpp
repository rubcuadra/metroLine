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

void main_menu()
{
    GraphicDoubleLinkedList<int> lineOne;
    int num, choice;
    do
    {
        choice = GUIChoice();
        switch (choice)
        {
            case 'a':
                std::cout << "Enter the Station to add: ";
                std::cin >> num;
                lineOne.insertTail(num);
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

/*
 
 
 
 else if (ans == 'r')
 {
 std::cout << "Enter the number to remove: ";
 std::cin >> num;
 num_tree.remove(num);
 }
 else if (ans == 's')
 {
 std::cout << "Enter the number to search for: ";
 std::cin >> num;
 if (num_tree.search(num))
 std::cout << "Found " << num << " in the tree" << std::endl;
 else
 std::cout << num << " is not in the tree" << std::endl;
 }
 else if (ans == 'f')
 {
 //int data[] = { 15, 7, 9, 20, 37, 3, 10, 17, 22, 12, 14, 13, 25, 34, 30, 2, 6, 11 };
 int data[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
 int size = sizeof data / sizeof data[0];
 for (int i = 0; i < size; i++)
 {
 num_tree.insertNode(data[i]);
 }
 }
 else if (ans == 'c')
 {
 num_tree.clear();
 }
 else if (ans == 'i')
 {
 num_tree.printInorder();
 }
 //else if (ans == 'b')
 //{
 //num_tree.printBreadthFirst();
 //}
 
 else if (ans == 'g')
 {
 num_tree.printGraphical();
 }
 else if (ans == 'q')
 {
 std::cout << "Good bye!" << std::endl;
 }

 }
 }

 
 
 Gilberto Echeverria
 
 Test of the Double Linked List data structure
 
 #include <iostream>
 #include "DoubleLinkedList.h"
 
 // Function prototypes

 char option = 'a';
 int value;
 bool found;
 DoubleLinkedList<int> double_list;
 
 while (option != 'q')
 {
 std::cout << "Main menu:" << std::endl;
 std::cout << "\ta. Insert item" << std::endl;
 std::cout << "\tb. Search for item" << std::endl;
 std::cout << "\tc. Print list" << std::endl;
 std::cout << "\td. Print current item" << std::endl;
 std::cout << "\tq. Quit the program" << std::endl;
 std::cout << "Select an option: ";
 std::cin >> option;
 
 if (option == 'a')
 {
 std::cout << "Enter value to insert: ";
 std::cin >> value;
 double_list.insertOrdered(value);
 }
 else if (option == 'b')
 {
 found = false;
 std::cout << "Enter value to search for: ";
 std::cin >> value;
 found = double_list.searchFor(value);
 if (found)
 {
 std::cout << "Item found in the list" << std::endl;
 }
 else
 {
 std::cout << "No such item in the list" << std::endl;
 }
 }
 else if (option == 'c')
 {
 double_list.printList();
 }
 else if (option == 'd')
 {
 std::cout << double_list.getCurrent()->getData() << std::endl;
 }

 */

