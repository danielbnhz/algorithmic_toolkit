
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <charconv>
#include <system_error>
#include <exception>

// --------------------------------------------------
// Algorithm module interface
// --------------------------------------------------
//
// Each algorithm implementation provides a function
// accepting an input stream and an output stream.
//
// This keeps the algorithms independent of main()
// and makes them easier to test later.
//
// Add new declarations as implementations are added.
//

void run_sliding_window(std::istream& input, std::ostream& output);
void run_binary_search(std::istream& input, std::ostream& output);
// --------------------------------------------------
// Algorithm registry
// --------------------------------------------------

struct Algorithm
{
    int id;
    std::string name;
    std::string description;

    void (*run)(std::istream&, std::ostream&);
};

const std::vector<Algorithm> algorithms =
{
    {
        1,
        "Sliding Window",
        "Maintains information about a moving contiguous range.",
        run_sliding_window
    },
    {
        2,
        "Binary Search",
        "Finds a target in a sorted array by repeatedly halving the search range.",
        run_binary_search
    }
};

// --------------------------------------------------
// Input handling
// --------------------------------------------------

bool read_integer(std::istream& input, int& value)
{
    std::string line;

    if (!std::getline(input, line))
    {
        return false;
    }

    const char* begin = line.data();
    const char* end = begin + line.size();

    auto result = std::from_chars(begin, end, value);

    return result.ec == std::errc{} && result.ptr == end;
}

// --------------------------------------------------
// Menu
// --------------------------------------------------

void print_menu()
{
    std::cout << "\n";
    std::cout << "====================================\n";
    std::cout << "       ALGORITHMIC TOOLKIT\n";
    std::cout << "====================================\n";

    for (const auto& algorithm : algorithms)
    {
        std::cout << algorithm.id << ". "
                  << algorithm.name << "\n";

        std::cout << "   "
                  << algorithm.description << "\n";
    }

    std::cout << "\n0. Exit\n";
    std::cout << "====================================\n";
    std::cout << "Select an algorithm: ";
}

// --------------------------------------------------
// Algorithm selection
// --------------------------------------------------

const Algorithm* find_algorithm(int selection)
{
    for (const auto& algorithm : algorithms)
    {
        if (algorithm.id == selection)
        {
            return &algorithm;
        }
    }

    return nullptr;
}

// --------------------------------------------------
// Main
// --------------------------------------------------

int main()
{
    std::cout << "Welcome to the Algorithmic Toolkit!\n";

    while (true)
    {
        print_menu();

        int selection{};

        if (!read_integer(std::cin, selection))        {
            if (std::cin.eof())
            {
                std::cout << "\nInput closed. Exiting.\n";
                break;
            }

            std::cout << "\nInvalid input. Enter an integer.\n";
            continue;
        }

        if (selection == 0)
        {
            std::cout << "\nExiting Algorithmic Toolkit.\n";
            break;
        }

        const Algorithm* selected = find_algorithm(selection);

        if (selected == nullptr)
        {
            std::cout << "\nNo algorithm exists with that ID.\n";
            continue;
        }

        std::cout << "\n====================================\n";
        std::cout << "Running: " << selected->name << "\n";
        std::cout << "====================================\n\n";

        try
        {
            selected->run(std::cin, std::cout);
        }
        catch (const std::exception& error)
        {
            std::cout << "\nAlgorithm terminated with an error: "
                      << error.what() << "\n";
        }
        catch (...)
        {
            std::cout << "\nAlgorithm terminated with an unknown error.\n";
        }

        std::cout << "\n====================================\n";
        std::cout << "Algorithm execution complete.\n";
        std::cout << "====================================\n";
    }

    return 0;
}
