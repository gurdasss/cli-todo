#include "Task.h"
#include <iostream>
#include <string> // for std::string

int main()
{

    while (true)
    {
        std::cout << "$ ";
        std::string command{};
        std::cin >> command;

        // TODO: NEED TO HANDLE EOF CHARACTERS

        if (command == "add")
        {
            // once we got the inputs from add command
            // in the input buffer
            // we need to extract each one of them individually
            std::string title{};
            std::cin >> title;

            std::string category{};
            std::cin >> category;

            std::cout << title << ' ' << category << '\n';
        }
        else if (command == "exit")
            break;
        else if (command == "help")
            ;
        else
            std::cout << "invalid command! type help\n";
    }

    return 0;
}