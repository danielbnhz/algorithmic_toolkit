# Sliding Window — Algorithm Notes

## 1. Core Concept

The **sliding window** is an algorithmic technique for maintaining information about a **contiguous range of elements** within a sequence.

Instead of repeatedly processing every element in an overlapping range from scratch, the algorithm maintains the information it needs and updates that information as the window moves.

The central idea:

> Maintain the information needed about the current window, remove the contribution of elements leaving it, and incorporate the contribution of elements entering it.

For example, consider a fixed-size window that calculates the sum of three consecutive elements:

```cpp
currentSum -= outgoingElement;
currentSum += incomingElement;
```

The algorithm avoids recalculating the entire sum after every movement.

This is particularly useful when consecutive windows overlap substantially.

## 2. Types of Sliding Windows

### 2.1 Fixed-Size Window

A fixed-size window always contains the same number of elements.

For example, consider this sequence:

```text
[2, 4, 6, 8, 10]
```

With a window size of three, the windows are:

```text
[2, 4, 6]  -> 12
[4, 6, 8]  -> 18
[6, 8, 10] -> 24
```

Each movement removes the outgoing element and incorporates the incoming element.

Common applications:

- Maximum or minimum sum of consecutive elements.
- Rolling averages.
- Recent CPU utilization measurements.
- Audio amplitude measurements over a fixed interval.
- Recent player actions in a game.

A fixed-size window is particularly straightforward when its maintained information can be updated in constant time.

### 2.2 Variable-Size Window

A variable-size window expands or contracts according to a condition.

It is commonly implemented using two pointers:

```cpp
int left = 0;
int right = 0;
```

The right pointer expands the window by incorporating new elements.

The left pointer contracts the window when a condition requires it.

For example:

```text
[left ... right]
```

The window may expand until it violates a constraint, then contract until the constraint is satisfied again.

Common applications:

- Finding the smallest contiguous subarray whose sum reaches a target.
- Finding the longest substring without repeated characters.
- Finding the longest sequence satisfying a resource constraint.
- Finding contiguous ranges that satisfy a threshold.

**Important:** The correctness of a variable-size sliding window depends on the properties of the problem.

For example, a straightforward shrinking-window solution for finding a minimum subarray sum generally relies on nonnegative array elements. Negative numbers can invalidate the assumptions that make the window condition monotonic.

## 3. Maintaining Window State

A sliding window does not necessarily maintain a sum.

It can maintain any useful information that can be updated as elements enter or leave the range.

Examples include:

| Maintained information | Possible application |
|---|---|
| Sum | Rolling totals |
| Frequency counters | Character or element frequency |
| Maximum or minimum | Window extrema |
| Hash-based counts | Duplicate detection |
| Boolean state | Tracking whether a condition is satisfied |

For example, a variable-size window can maintain character frequencies:

```cpp
unordered_map<char, int> frequencies;
```

When the right pointer advances, the incoming character's frequency increases.

When the left pointer advances, the outgoing character's frequency decreases.

This allows the algorithm to reason about the current substring without repeatedly scanning the entire substring.

The important design question is:

**What information must be maintained to determine whether the current window satisfies the problem's requirements?**

## 4. Multiple and Nested Windows

Sliding windows do not have to operate independently or exist in isolation.

Multiple windows can examine the same sequence at different timescales.

For example:

- 2 elements: immediate behavior.
- 5 elements: medium-term behavior.
- 10 elements: longer-term behavior.

Nested windows are also possible. An outer window can contain smaller windows that independently analyze subsections of the data.

Potential applications include:

- Audio analysis.
- Hierarchical time-series analysis.
- Game behavior recognition.
- Monitoring short-term and long-term system activity.

Multiple windows are not a requirement of the sliding-window technique. They are an extension that becomes useful when different analytical timescales are needed.

## 5. Practical Application: World's Tale

A potential application is adaptive enemy AI.

An enemy could maintain a sliding window of recent player actions:

```text
[Fire, Fire, Guard, Fire]
```

It could track the frequency of different elemental attacks and adjust its tactical priorities accordingly.

As new actions arrive, old actions leave the window and frequency counters are updated.

This allows the AI to recognize recent player tendencies without repeatedly scanning the entire battle history.

A possible architecture:

1. **Battle Event Manager:** Records incoming player actions and maintains recent history.
2. **Behavior Analyzer:** Interprets the maintained window and calculates tendencies.
3. **Enemy AI:** Uses the resulting information when selecting its next action.

For example, an enemy might recognize that the player has recently favored fire attacks and adjust its defensive priorities.

The window size determines how much historical behavior influences the analysis. A smaller window reacts more quickly to changes, while a larger window represents a longer behavioral history.

## 6. Complexity Analysis

For a conventional fixed-size sliding window with constant-time incremental updates:

- **Time complexity:** \(O(n)\)
- **Auxiliary space:** \(O(1)\), excluding separately stored output.

Each element enters and leaves the window at most once.

For a conventional variable-size two-pointer window:

- **Time complexity:** Often \(O(n)\).
- **Auxiliary space:** Depends on the maintained state.

Although the algorithm may contain a nested loop, its total number of pointer movements can still be linear.

For example, if both pointers only move forward, neither can advance more than \(n\) times.

A naive implementation that independently recalculates every window may require:

\[
O(n \times k)
\]

where:

- \(n\) is the sequence length.
- \(k\) is the window size.

Incremental updates eliminate this repeated work when the maintained information supports efficient updates.

**Complexity caveat:** These bounds assume constant-time updates. Maintaining a window maximum using a more sophisticated data structure, for example, introduces additional considerations.

## 7. Recognition Checklist

When encountering an algorithm problem, ask:

1. Am I working with a contiguous sequence?
2. Am I repeatedly examining overlapping sections?
3. Can I maintain the information I need incrementally?
4. Can I update that information when elements enter or leave the window?
5. If the window is variable-sized, what condition determines when it expands or contracts?
6. Does the problem's input satisfy the assumptions required by that condition?

If these characteristics fit, sliding window is a potential solution.

## 8. Fundamental Takeaway

Sliding window is not inherently about finding maximums, minimums, or sums.

It is about efficiently maintaining information about a moving contiguous region of data.

The main optimization comes from recognizing that consecutive windows overlap, allowing previously calculated information to be reused instead of repeatedly recalculated.

The technique is especially useful for sequence-processing problems where maintaining a small amount of state is sufficient to understand the current range.