
#include <iostream>
#include <string>
#include <vector>
#include <charconv>
#include <system_error>
#include <utility>
#include "../utilities/input_utils.h"
// --------------------------------------------------
// Input handling
// --------------------------------------------------



// --------------------------------------------------
// Array visualization
// --------------------------------------------------

void print_array(
    const std::vector<int>& values,
    std::ostream& output)
{
    output << "[ ";

    for (const int value : values)
    {
        output << value << " ";
    }

    output << "]\n";
}

// --------------------------------------------------
// Partition
// --------------------------------------------------
//
// Lomuto partition scheme:
//
// 1. Select the final element as pivot.
// 2. Scan the subarray.
// 3. Move values <= pivot to the left.
// 4. Place pivot immediately after those values.
// 5. Return the pivot's final index.
//
// --------------------------------------------------

int partition(
    std::vector<int>& values,
    int low,
    int high,
    std::ostream& output,
    int depth)
{
    const std::string indent(depth * 2, ' ');

    const int pivot = values[high];
    int boundary = low;

    output << indent
           << "PARTITION [" << low << ", " << high << "]\n";

    output << indent
           << "Selected pivot: " << pivot
           << " at index " << high << "\n";

    for (int scan = low; scan < high; ++scan)
    {
        output << indent
               << "Compare " << values[scan]
               << " <= " << pivot << ": ";

        if (values[scan] <= pivot)
        {
            output << "TRUE\n";

            if (boundary != scan)
            {
                output << indent
                       << "Swap index " << boundary
                       << " (" << values[boundary] << ") with index "
                       << scan << " (" << values[scan] << ")\n";

                std::swap(
                    values[boundary],
                    values[scan]);
            }
            else
            {
                output << indent
                       << "No swap needed.\n";
            }

            ++boundary;
        }
        else
        {
            output << "FALSE\n";
        }

        output << indent << "Current array: ";
        print_array(values, output);
    }

    // Place pivot in its final position.

    output << indent
           << "Placing pivot at index "
           << boundary << "\n";

    if (boundary != high)
    {
        std::swap(
            values[boundary],
            values[high]);
    }

    output << indent << "Partition complete: ";
    print_array(values, output);

    return boundary;
}

// --------------------------------------------------
// Quicksort
// --------------------------------------------------

void quicksort(
    std::vector<int>& values,
    int low,
    int high,
    std::ostream& output,
    int depth)
{
    const std::string indent(depth * 2, ' ');

    output << indent
           << "QUICKSORT [" << low << ", " << high << "]\n";

    // Base case: zero or one element.

    if (low >= high)
    {
        output << indent
               << "Base case reached. Returning.\n";

        return;
    }

    // Partition and establish pivot position.

    const int pivot_index = partition(
        values,
        low,
        high,
        output,
        depth);

    output << indent
           << "Pivot " << values[pivot_index]
           << " fixed at index " << pivot_index << "\n";

    // Recursively sort left partition.

    output << indent
           << "Recursing LEFT: ["
           << low << ", " << pivot_index - 1 << "]\n";

    quicksort(
        values,
        low,
        pivot_index - 1,
        output,
        depth + 1);

    // Recursively sort right partition.

    output << indent
           << "Recursing RIGHT: ["
           << pivot_index + 1 << ", " << high << "]\n";

    quicksort(
        values,
        pivot_index + 1,
        high,
        output,
        depth + 1);

    output << indent
           << "Finished range ["
           << low << ", " << high << "]\n";
}

// --------------------------------------------------
// Public algorithm interface
// --------------------------------------------------

void run_quicksort(
    std::istream& input,
    std::ostream& output)
{
    int count{};

    output << "QUICKSORT - Lomuto Partitioning\n";
    output << "Enter sequence size (1-625): ";

    if (!read_integer(input, count))
    {
        output << "Invalid sequence size.\n";
        return;
    }

    if (count < 1 || count > 625)
    {
        output << "Sequence size must be between 1 and 625.\n";
        return;
    }

    std::vector<int> values;
    values.reserve(count);

    output << "\nEnter " << count << " elements:\n";

    for (int i = 0; i < count; ++i)
    {
        int value{};

        output << "Element " << i << ": ";

        if (!read_integer(input, value))
        {
            output << "\nInvalid or missing integer. "
                   << "Quicksort cancelled.\n";
            return;
        }

        values.push_back(value);
    }

    output << "\n========== INITIAL ARRAY ==========\n";

    print_array(values, output);

    output << "\n========== EXECUTION TRACE ==========\n";

    quicksort(
        values,
        0,
        static_cast<int>(values.size()) - 1,
        output,
        0);

    output << "\n========== FINAL RESULT ==========\n";

    print_array(values, output);
}
