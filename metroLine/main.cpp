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
#include "GraphicAVLTree.h"

void main_menu()
{
    GraphicAVLTree<int> num_tree;
    int num;
    
    char ans = 'a';
    while (ans != 'q')
    {
        std::cout << resourcePath() << std::endl;
        std::cout << "\nAVL TREE MENU" << std::endl;
        std::cout << "\ta. Add new number" << std::endl;
        std::cout << "\tr. Remove a number" << std::endl;
        std::cout << "\ts. Search for a number" << std::endl;
        std::cout << "\tf. Fill tree with preset data" << std::endl;
        std::cout << "\tc. Clear tree" << std::endl;
        std::cout << "\ti. Print the tree in order" << std::endl;
        //std::cout << "\tb. Print the tree breadth first" << std::endl;
        std::cout << "\tt. Print the tree as a tree" << std::endl;
        std::cout << "\tg. Print the tree graphically" << std::endl;
        std::cout << "\tq. Quit program" << std::endl;
        std::cout << "Select an option: ";
        std::cin >> ans;
        
        if (ans == 'a')
        {
            std::cout << "Enter the number to add: ";
            std::cin >> num;
            num_tree.insertNode(num);
        }
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
        else if (ans == 't')
        {
            num_tree.printTree();
        }
        else if (ans == 'g')
        {
            num_tree.printGraphical();
        }
        else if (ans == 'q')
        {
            std::cout << "Good bye!" << std::endl;
        }
        else
        {
            std::cout << "Incorrect option. Try again ..." << std::endl;
        }
    }
}

int main()
{
    main_menu();
    return 0;
    
}