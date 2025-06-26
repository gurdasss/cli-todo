#include "Task.h"
#include <iostream>
#include <string>    // for std::string
#include <limits>    // for std::numeric_limits
#include <algorithm> // for std::transform
#include <cctype>    // for std::tolower
#include <optional>  // for std::optional

void ignoreLine();
bool hasUnextractedInput();

std::istream &operator>>(std::istream &in, Task::Status &status);
std::ostream &operator<<(std::ostream &out, Task::Status status);

void toLowerCase(std::string &string);

std::optional<Task::Status> getStatusFromChar(char statusChar);
std::string_view getStatusString(Task::Status status);

int main()
{

    while (true)
    {
        std::cout << "$ ";
        std::string command{};
        std::cin >> command;

        // Check for failed extraction
        // If the previous extraction failed
        if (!std::cin)
        {
            std::cerr << "std::cin is in failed state.\n";
            if (std::cin.eof()) // If the user entered an EOF
                std::exit(0);   // Shut down the program now
        }

        // convert the recent extracted input from the input buffer
        // to lower case
        toLowerCase(command);

        // WARNING: the user might add trailing whitespace(s) after
        // a valid input, which will satisfy the below condition
        if (command == "add" && hasUnextractedInput())
        {
            // extract and store extra inputs from the input buffer
            // on each call to std::cin
            std::string title{};
            std::cin >> title;

            // check if, after the last operation
            // the input buffer still have some
            // unextracted input left
            if (!hasUnextractedInput())
            {
                std::cout << "add: missing status and category\n";
                std::cout << "add [title] [status] [category]\n";
                continue;
            }

            Task::Status status{};
            std::cin >> status;

            // if last operation did'nt succeeded
            if (!std::cin)
            {
                std::cout << "Enter a valid status: [P]: Progress, "
                             "[I]: In Progress\n";

                // clear all the states of std::cin
                // and remove all the unextracted input
                // from the input buffer
                std::cin.clear();
                ignoreLine();
                continue;
            }

            // check if, after the last operation
            // the input buffer still have some
            // unextracted input left
            if (!hasUnextractedInput())
            {
                std::cout << "add: missing category\n";
                std::cout << "add [title] [status] [category]\n";
                continue;
            }

            std::string category{};
            std::cin >> category;

            std::cout << title << ' '
                      << status << ' '
                      << category << '\n';
        }
        else if (command == "exit")
            break;
        else if (command == "help")
            ;
        else
            std::cout << "invalid command! type help\n";

        // if there's still any unextrated input(s)
        // left in the input buffer clear all those extra inputs
        if (hasUnextractedInput())
            ignoreLine();
    }

    return 0;
}

void ignoreLine()
{
    // clear up to the largest value that can be stored
    // in a variable of type std::streamsize characters out of the buffer,
    // or until a '\n' character is removed
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if std::cin has unextracted input on the current line, false otherwise
bool hasUnextractedInput()
{
    return !std::cin.eof() && std::cin.peek() != '\n';
}

void toLowerCase(std::string &string)
{
    std::transform(
        string.begin(), // start from the first letter
        string.end(),   // stop at the end
        string.begin(), // where to put the result (back into the same string)

        // a unary lambda function that will convert an unsigned char
        // to lower case
        [](unsigned char c)
        { return std::tolower(c); } // rule: make lowercase
    );
}

std::istream &operator>>(std::istream &in, Task::Status &status)
{
    char statusChar{};
    in >> statusChar;

    statusChar = static_cast<char>(std::tolower(statusChar));

    std::optional<Task::Status> statusOPT{getStatusFromChar(statusChar)};

    if (statusOPT)
    {
        // dereference std::optional to get matching enumerator
        status = *statusOPT;
        return in;
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    return in;
}

std::ostream &operator<<(std::ostream &out, Task::Status status)
{
    out << getStatusString(status);
    return out;
}

std::optional<Task::Status> getStatusFromChar(char statusChar)
{
    switch (statusChar)
    {
    case 'p':
        return Task::pending;
    case 'i':
        return Task::inProgress;
    case 'd':
        return Task::done;

    default:
        return std::nullopt;
    }
}

std::string_view getStatusString(Task::Status status)
{
    switch (status)
    {
    case Task::pending:
        return "Pending";
    case Task::inProgress:
        return "In-Progress";
    case Task::done:
        return "Done";

    default:
        return "???";
    }
}