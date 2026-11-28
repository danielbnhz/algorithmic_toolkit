
#include <iostream>
#include <string>
#include <vector>
#include <charconv>
#include <system_error>
#include "../utilities/input_utils.h"
// --------------------------------------------------
// Input handling
// --------------------------------------------------

namespace
{
    constexpr int MAX_ARRAY_SIZE = 625;



    bool is_sorted_ascending(const std::vector<int>& values)
    {
        for (std::size_t i = 1; i < values.size(); ++i)
        {
            if (values[i] < values[i - 1])
            {
                return false;
            }
        }

        return true;
    }
}

// --------------------------------------------------
// Binary search implementation
// --------------------------------------------------

int binary_search_trace(
    const std::vector<int>& values,
    int target,
    std::ostream& output)
{
    int low = 0;
    int high = static_cast<int>(values.size()) - 1;

    int iteration = 1;

    while (low <= high)
    {
        const int mid = low + (high - low) / 2;

        output << "\nIteration " << iteration << "\n";

        output << "Low:  " << low << "\n";
        output << "High: " << high << "\n";
        output << "Mid:  " << mid << "\n";

        output << "values[" << mid << "] = "
               << values[mid] << "\n";

        if (values[mid] == target)
        {
            output << "\nTarget found!\n";
            output << "Index: " << mid << "\n";

            return mid;
        }

        if (values[mid] < target)
        {
            output << "Comparison: "
                   << values[mid]
                   << " < "
                   << target << "\n";

            output << "Discarding left half.\n";

            low = mid + 1;
        }
        else
        {
            output << "Comparison: "
                   << values[mid]
                   << " > "
                   << target << "\n";

            output << "Discarding right half.\n";

            high = mid - 1;
        }

        ++iteration;
    }

    output << "\nTarget not found.\n";

    return -1;
}

// --------------------------------------------------
// Algorithm interface
// --------------------------------------------------

void run_binary_search(
    std::istream& input,
    std::ostream& output)
{
    int array_size{};

    output << "Enter array size (1-"
           << MAX_ARRAY_SIZE << "): ";

    if (!read_integer(input, array_size))
    {
        output << "\nInvalid array size input.\n";
        return;
    }

    if (array_size < 1 || array_size > MAX_ARRAY_SIZE)
    {
        output << "\nArray size must be between 1 and "
               << MAX_ARRAY_SIZE << ".\n";

        return;
    }

    std::vector<int> values;
    values.reserve(array_size);

    output << "\nEnter " << array_size
           << " elements in ascending order:\n";

    for (int i = 0; i < array_size; ++i)
    {
        int value{};

        output << "Element " << i << ": ";

        if (!read_integer(input, value))
        {
            output << "\nInvalid element input.\n";
            return;
        }

        values.push_back(value);
    }

    if (!is_sorted_ascending(values))
    {
        output << "\nError: Array must be sorted "
               << "in ascending order.\n";

        return;
    }

    int target{};

    output << "\nEnter target value: ";

    if (!read_integer(input, target))
    {
        output << "\nInvalid target input.\n";
        return;
    }

    output << "\n====================================\n";
    output << "BINARY SEARCH TRACE\n";
    output << "====================================\n";

    output << "\nTarget: " << target << "\n";
    output << "Array size: " << values.size() << "\n";

    const int result = binary_search_trace(
        values,
        target,
        output);

    output << "\n====================================\n";
    output << "SEARCH SUMMARY\n";
    output << "====================================\n";

    if (result != -1)
    {
        output << "Result: Found\n";
        output << "Index: " << result << "\n";
    }
    else
    {
        output << "Result: Not found\n";
    }

    output << "Time complexity: O(log n)\n";
    output << "Auxiliary space: O(1)\n";
}
