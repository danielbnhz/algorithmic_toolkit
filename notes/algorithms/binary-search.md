# Binary Search

## Overview

Binary search is a **divide-and-locate** algorithm for finding a target
value in a **sorted** collection.

Instead of checking every element, it repeatedly examines the middle
element and discards the half of the remaining search range that cannot
contain the target.

Binary search is often implemented iteratively with a loop. A recursive
implementation is also possible, but recursion is not required.

## How it works

For an ascending array:

1.  Set `low` to the first valid index and `high` to the last valid
    index.
2.  Calculate the midpoint of the current range.
3.  Compare the middle element with the target:
    -   If they are equal, the target has been found.
    -   If the middle element is smaller, continue in the right half.
    -   If the middle element is larger, continue in the left half.
4.  Repeat until the target is found or the search range becomes empty.

The search range is inclusive: both `low` and `high` are candidate
indices.

### Example

Search for `23` in this sorted array:

``` text
Index:  0   1   2   3   4   5   6   7   8
Value:  3   7  11  15  19  23  27  31  35
```

    Step   `low`   `high`   `mid`   `array[mid]` Decision
  ------ ------- -------- ------- -------------- -------------------------------------
       1       0        8       4             19 19 is smaller than 23; search right
       2       5        8       6             27 27 is larger than 23; search left
       3       5        5       5             23 Target found at index 5

Each comparison removes roughly half of the remaining candidates.

## Iterative C++ implementation

``` cpp
#include <vector>

int binary_search(const std::vector<int>& values, int target)
{
    int low = 0;
    int high = static_cast<int>(values.size()) - 1;

    while (low <= high)
    {
        // This form avoids the potential overflow of (low + high) / 2.
        const int mid = low + (high - low) / 2;

        if (values[mid] == target)
        {
            return mid;
        }

        if (values[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}
```

The function returns the index of a matching element, or `-1` if the
target is absent.

The condition `low <= high` matters: when `low == high`, one candidate
index remains and must still be checked. Once `low > high`, the search
range is empty.

## Recursive implementation

The same strategy can be expressed recursively by making each smaller
search range a new function call.

``` cpp
#include <vector>

int binary_search_recursive(
    const std::vector<int>& values,
    int target,
    int low,
    int high)
{
    if (low > high)
    {
        return -1;
    }

    const int mid = low + (high - low) / 2;

    if (values[mid] == target)
    {
        return mid;
    }

    if (values[mid] < target)
    {
        return binary_search_recursive(
            values, target, mid + 1, high);
    }

    return binary_search_recursive(
        values, target, low, mid - 1);
}
```

A wrapper can initialize the search bounds:

``` cpp
int binary_search_recursive(
    const std::vector<int>& values,
    int target)
{
    return binary_search_recursive(
        values, target, 0,
        static_cast<int>(values.size()) - 1);
}
```

The recursive version has the same time complexity as the iterative
version, but uses additional call-stack space.

## Complexity

Let `n` be the number of elements.

  -----------------------------------------------------------------------
  Measure                 Complexity              Reason
  ----------------------- ----------------------- -----------------------
  Time                    `O(log n)`              The candidate range is
                                                  approximately halved
                                                  after each comparison.

  Iterative auxiliary     `O(1)`                  A fixed number of
  space                                           variables is used.

  Recursive auxiliary     `O(log n)`              Each recursive call
  space                                           adds a stack frame,
                                                  with logarithmically
                                                  many calls.
  -----------------------------------------------------------------------

For comparison, a linear search can require `O(n)` time because it may
inspect every element.

## Important requirements and details

-   **The collection must be sorted** according to the ordering used by
    the comparisons. Binary search does not work reliably on arbitrary
    unsorted data.
-   **The search bounds must be updated carefully.** After checking
    `mid`, use `mid + 1` or `mid - 1` so the next range excludes the
    already-checked midpoint.
-   **Duplicates:** this implementation returns a matching occurrence,
    but does not guarantee the first or last occurrence when duplicates
    exist. Finding the first or last occurrence requires a slightly
    modified boundary search.
-   **Insertion positions:** a related form of binary search finds the
    position where a value could be inserted while preserving sorted
    order. This is commonly called a lower-bound search.

## Key idea

Binary search trades the requirement of sorted data for a much smaller
search effort. Rather than moving through the collection one element at
a time, it uses each comparison to eliminate about half of the remaining
possibilities.
