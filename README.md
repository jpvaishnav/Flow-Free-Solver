# Flow-free-solver

[Flow free](bigduckgames.com/flowfree) game solver using backtracking and relevant techniques 

---

### Table of Contents


- [Problem Description](#problem-description)
- [Solution Approaches](#solution-approaches)
- [Efficiency](#efficiency-of-the-solution)

---

## Problem description
- To solve the number link puzzle game named Flow Free
- Puzzle will contain a squared matrix or grid will completely or substantially colored cells
- Connect the cells of the same color by drawing a path between them such that this path does not intersect with any other colored path, and there should not be any empty cells left after the entire connection

![sg](https://user-images.githubusercontent.com/46133803/100767070-5636e200-341f-11eb-9d6b-af3db0b89617.png)

#### CSP Framework

- Variables: Xij  {each cell of the grid } Where i ∈ [1,n],  j ∈ [1,n] and n*n=size of the grid
- Domain: { Red, Blue, Green, White, Yellow, Purple,............} Size of the domain is C
- Constraints:   1. Xij should not be uncolored
                 2. Path of one color should not intersect with path of another color
                 3. ∈ path p such that  Xij and Xi’j’ have some color ∀ c ∈ domain 

---

## Solution approaches 

### Backtracking

- Assign a specific color to a cell
- Perform recursion for its successor states
- If any of the successor states are satisfied as goal test then return the solution, 
- Else perform backtrack i.e. one step back, change the successor and repeat the process until no successor is left.

### Filtering

- Early detection of future failure
- Avoiding in exploration of unnecessary and redundant paths.

#### Deadlock and Isolated Path

![di](https://user-images.githubusercontent.com/46133803/100767045-4fa86a80-341f-11eb-8ad1-f1155b705ae4.png)


### Ordering

- Strategy to choose a variable color from the matrix
- Picks the next colored cells that have the fewest possible moves left in 4 successive directions

## Run 

```html
    $ g++ -o flowfree main.cpp
    $ ./flowfree.out
    # Or open application.exe
```
---

## Efficiency of the solution

- Exponential nature
- Time complexity: O(C^(n*n))
- Space complexity: O(C^(n*n))
- The above discussed solution solves upto n=11 using feasible resources

## Comparison

| Grid size | Technique | Nodes explored | Time taken(Seconds) |
|--- | --- | --- | --- |
| 7| Backtracking | 6597 | 0 |
| 7 | Backtracking + Filtering | 90 | 0 |
| 7 | Backtracking + Filtering + Ordering | 74 | 0 |
| 8 | Backtracking | 42823078 | 7 |
| 8 | Backtracking + Filtering | 7252 | 2 |
| 9 | Backtracking + Filtering + Ordering | 1017 | 5 |

---
