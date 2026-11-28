
#include <iostream>
#include <vector>
#include <string>
#include <charconv>
#include <limits>
#include <cctype>
#include <system_error>
#include "../utilities/input_utils.h"
// --------------------------------------------------
// Configuration
// --------------------------------------------------

namespace
{
    constexpr int MAX_SEQUENCE_SIZE = 625; // 5^4
    constexpr int MAX_TRACE_STEPS = 100;


    // --------------------------------------------------
    // Display helper
    // --------------------------------------------------

    void print_window(
        const std::vector<int>& values,
        int start,
        int window_size,
        std::ostream& output)
    {
        output << "[";

        for (int i = start; i < start + window_size; ++i)
        {
            output << values[i];

            if (i < start + window_size - 1)
            {
                output << ", ";
            }
        }

        output << "]";
    }
}

// --------------------------------------------------
// Sliding Window Implementation
// --------------------------------------------------

void run_sliding_window(
    std::istream& input,
    std::ostream& output)
{
    output << "\n";
    output << "====================================\n";
    output << "       FIXED-SIZE SLIDING WINDOW\n";
    output << "====================================\n";

    output << "\nObjective:\n";
    output << "Find the maximum sum of consecutive elements.\n";

    // --------------------------------------------------
    // Step 1: Collect input
    // --------------------------------------------------

    int sequence_size{};

    if (!read_integer(
            input,
            output,
            "\nEnter sequence size (1-625): ",
            sequence_size))
    {
        output << "Invalid input or input closed.\n";
        return;
    }

    if (sequence_size < 1 ||
        sequence_size > MAX_SEQUENCE_SIZE)
    {
        output << "Sequence size must be between 1 and "
               << MAX_SEQUENCE_SIZE << ".\n";
        return;
    }

    int window_size{};

    if (!read_integer(
            input,
            output,
            "Enter window size: ",
            window_size))
    {
        output << "Invalid input or input closed.\n";
        return;
    }

    if (window_size < 1 ||
        window_size > sequence_size)
    {
        output << "Window size must be between 1 and "
               << sequence_size << ".\n";
        return;
    }

    std::vector<int> values;

    values.reserve(sequence_size);

    output << "\nEnter " << sequence_size << " elements:\n";

    for (int i = 0; i < sequence_size; ++i)
    {
        int value{};

        if (!read_integer(
                input,
                output,
                "Element " + std::to_string(i) + ": ",
                value))
        {
            output << "Invalid input or input closed.\n";
            return;
        }

        values.push_back(value);
    }

    // --------------------------------------------------
    // Step 2: Initialize the first window
    // --------------------------------------------------

    output << "\n";
    output << "====================================\n";
    output << "STEP 1: INITIALIZE WINDOW\n";
    output << "====================================\n";

    long long current_sum = 0;

    for (int i = 0; i < window_size; ++i)
    {
        current_sum += values[i];
    }

    long long maximum_sum = current_sum;

    int maximum_start = 0;

    output << "Initial window: ";
    print_window(values, 0, window_size, output);

    output << "\nInitial sum: " << current_sum << "\n";

    output << "\nThe first window establishes our baseline.\n";
    output << "We will now move the window one position at a time.\n";

    // --------------------------------------------------
    // Step 3: Slide the window
    // --------------------------------------------------

    output << "\n";
    output << "====================================\n";
    output << "STEP 2: SLIDE THE WINDOW\n";
    output << "====================================\n";

    const int total_slides = sequence_size - window_size;

    int displayed_steps = 0;

    for (int right = window_size;
         right < sequence_size;
         ++right)
    {
        const int left = right - window_size;

        const int outgoing = values[left];
        const int incoming = values[right];

        // Incremental update:
        // Remove the element leaving the window.
        current_sum -= outgoing;

        // Incorporate the element entering the window.
        current_sum += incoming;

        const int current_start = left + 1;

        // Determine whether this window is worth displaying.
        const bool trace_enabled =
            displayed_steps < MAX_TRACE_STEPS;

        if (trace_enabled)
        {
            output << "\n------------------------------------\n";
            output << "Window movement " << (left + 1) << "\n";
            output << "------------------------------------\n";

            output << "Outgoing element: " << outgoing << "\n";
            output << "Incoming element: " << incoming << "\n";

            output << "Remove outgoing contribution: "
                   << "- " << outgoing << "\n";

            output << "Add incoming contribution: "
                   << "+ " << incoming << "\n";

            output << "Updated sum: " << current_sum << "\n";

            output << "Current window: ";
            print_window(
                values,
                current_start,
                window_size,
                output);

            output << "\n";
        }

        // --------------------------------------------------
        // Step 4: Update maximum
        // --------------------------------------------------

        if (current_sum > maximum_sum)
        {
            maximum_sum = current_sum;
            maximum_start = current_start;

            if (trace_enabled)
            {
                output << "NEW MAXIMUM FOUND: "
                       << maximum_sum << "\n";
            }
        }
        else if (trace_enabled)
        {
            output << "Maximum remains: "
                   << maximum_sum << "\n";
        }

        if (trace_enabled)
        {
            ++displayed_steps;
        }
    }

    // --------------------------------------------------
    // Step 5: Final results
    // --------------------------------------------------

    output << "\n";
    output << "====================================\n";
    output << "       EXECUTION SUMMARY\n";
    output << "====================================\n";

    if (total_slides > MAX_TRACE_STEPS)
    {
        output << "Trace limit reached. Suppressed "
               << (total_slides - MAX_TRACE_STEPS)
               << " additional movement descriptions.\n";
    }

    output << "Sequence size: " << sequence_size << "\n";
    output << "Window size: " << window_size << "\n";
    output << "Total movements: " << total_slides << "\n";

    output << "\nMaximum sum: " << maximum_sum << "\n";

    output << "Best window: ";
    print_window(
        values,
        maximum_start,
        window_size,
        output);

    output << "\nStarting index: " << maximum_start << "\n";

    output << "\nComplexity analysis:\n";
    output << "Time: O(n)\n";
    output << "Auxiliary space: O(k) for stored input, "
              "O(1) additional algorithm state.\n";

    output << "\nThe window moved incrementally rather than "
              "recalculating every sum from scratch.\n";
}
