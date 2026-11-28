# Quicksort — Pivot-Based Recursive Sorting

## Core idea

Quicksort sorts an array by repeatedly **partitioning** it around a selected element called the **pivot**.

For each partition:

1. Choose a pivot.
2. Rearrange the elements so values smaller than (or equal to) the pivot are on its left, and larger values are on its right.
3. Put the pivot into its final sorted position.
4. Recursively apply the same process to the left and right subarrays.
5. Stop when a subarray has zero or one element; it is already sorted.

The key insight is that a partition places its pivot in the correct final position without needing to sort either side first.

## Worked example

Start with:

```text
[8, 3, 1, 7, 0, 10, 2]
```

For this example, use the **Lomuto partition scheme**: choose the last element as the pivot, then scan the other elements from left to right.

The pivot is `2`.

- `8` is greater than `2`: leave it on the right.
- `3` is greater than `2`: leave it on the right.
- `1` is less than or equal to `2`: move it into the next position on the left.
- `7` is greater than `2`: leave it on the right.
- `0` is less than or equal to `2`: move it into the next position on the left.
- `10` is greater than `2`: leave it on the right.
- Finally, swap the pivot into the position immediately after the smaller values.

The partition becomes:

```text
[1, 0, 2, 7, 3, 10, 8]
       ^
     pivot
```

The pivot `2` is now in its final sorted position. The left side contains values no greater than `2`; the right side contains values greater than `2`. Neither side is necessarily sorted yet.

Now recursively sort the two sides:

```text
[1, 0]  2  [7, 3, 10, 8]
```

After recursively partitioning those subarrays, the result is:

```text
[0, 1, 2, 3, 7, 8, 10]
```

The pivot is not revisited after its partition is complete.

## Pseudocode

This is the Lomuto version, using the final element as the pivot.

```text
QUICKSORT(array, low, high):
    if low >= high:
        return

    pivot_index = PARTITION(array, low, high)

    QUICKSORT(array, low, pivot_index - 1)
    QUICKSORT(array, pivot_index + 1, high)


PARTITION(array, low, high):
    pivot = array[high]
    boundary = low

    for scan from low to high - 1:
        if array[scan] <= pivot:
            swap array[boundary] and array[scan]
            boundary = boundary + 1

    swap array[boundary] and array[high]
    return boundary
```

`boundary` marks the next position where a value less than or equal to the pivot belongs. `scan` examines each element in the current partition.

## Complexity

| Case | Time complexity | Why |
|---|---:|---|
| Best / balanced | O(n log n) | Each level partitions the elements, and there are about log n levels. |
| Average | O(n log n) | Partitions are generally sufficiently balanced. |
| Worst / highly unbalanced | O(n²) | A pivot repeatedly produces an empty side and a side containing almost every remaining element. |

A partition takes O(n) time for a subarray of n elements.

Quicksort is generally in-place: partitioning rearranges the original array rather than creating separate left and right arrays. The recursive calls still use stack space: typically O(log n), but O(n) in the worst case.

## Pivot selection matters

Choosing the final element is simple, but it can perform poorly on already sorted or reverse-sorted input. Better pivot strategies include choosing a random element or using the median of three candidates.

The pivot strategy changes the likelihood of balanced partitions; it does not change the basic partition-and-recurse idea.

## Important distinctions

- Partitioning is **not** the same as sorting each side.
- The pivot reaches its final position after one partition.
- The two recursive calls exclude the pivot's final position.
- The base case is a subarray with zero or one element.
- This Lomuto implementation is not stable: equal elements are not guaranteed to retain their original relative order.

## Mental model

**Choose a pivot → partition around it → lock the pivot in place → recursively sort both sides.**

Quicksort solves the sorting problem by repeatedly reducing it to smaller sorting problems.
