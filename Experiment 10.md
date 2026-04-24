# Experiment – 10 (Fenwick Tree Approach)

## Question

Given an integer array `nums`, return an integer array `counts` where `counts[i]` is the number of smaller elements to the right of `nums[i]`.

### Examples

**Example 1:**
Input: `nums = [5,2,6,1]`
Output: `[2,1,1,0]`

**Example 2:**
Input: `nums = [-1]`
Output: `[0]`

**Example 3:**
Input: `nums = [-1,-1]`
Output: `[0,0]`

### Constraints

* `1 <= nums.length <= 10^5`
* `-10^4 <= nums[i] <= 10^4`

---

## Proposed Solution (Approach)

We use a **Fenwick Tree (Binary Indexed Tree)** to efficiently count how many smaller elements appear after each element.

### Key Idea:

* Traverse the array **from right to left**
* Use Fenwick Tree to:

  * **Query**: how many elements smaller than current have been seen
  * **Update**: mark the current element as visited

### Why coordinate compression?

Since values range from `-10^4` to `10^4`, we shift them to positive indices using:

```
index = nums[i] + 10001
```

This ensures all values map safely into Fenwick Tree indices.

### Time Complexity:

* `O(n log n)`

---

## Algorithm

1. Initialize:

   * Fenwick Tree array `BIT`
   * Result array `counts`

2. Traverse array from right to left:

   * Convert value to index using offset
   * Query BIT for count of smaller elements
   * Store result in `counts[i]`
   * Update BIT with current index

3. Return `counts`

---

## C++ Code

```cpp id="h2y5g7"
#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
public:
    vector<int> BIT;
    int size;

    FenwickTree(int n) {
        size = n;
        BIT.resize(n + 1, 0);
    }

    void update(int index, int value) {
        while (index <= size) {
            BIT[index] += value;
            index += index & (-index);
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += BIT[index];
            index -= index & (-index);
        }
        return sum;
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> counts(n);

        int offset = 10001; // shift to positive
        int maxVal = 20002;

        FenwickTree ft(maxVal);

        for (int i = n - 1; i >= 0; i--) {
            int index = nums[i] + offset;

            counts[i] = ft.query(index - 1); // smaller elements
            ft.update(index, 1);
        }

        return counts;
    }
};

int main() {
    Solution obj;
    vector<int> nums = {5, 2, 6, 1};

    vector<int> result = obj.countSmaller(nums);

    cout << "Output: ";
    for (int x : result) {
        cout << x << " ";
    }

    return 0;
}
```

---

## Dry Run (Given Input)

**Input:**
`nums = [5, 2, 6, 1]`

### Step-by-step (Right → Left)

| Step | Element | Index (after shift) | Query Result | counts[]  | BIT Update |
| ---- | ------- | ------------------- | ------------ | --------- | ---------- |
| 1    | 1       | 10002               | 0            | [*,*,_,0] | Insert 1   |
| 2    | 6       | 10007               | 1            | [*,*,1,0] | Insert 6   |
| 3    | 2       | 10003               | 1            | [_,1,1,0] | Insert 2   |
| 4    | 5       | 10006               | 2            | [2,1,1,0] | Insert 5   |

### Explanation:

* For 1 → no smaller elements → 0
* For 6 → {1} → 1
* For 2 → {1} → 1
* For 5 → {2,1} → 2

---

## Final Output

`[2,1,1,0]`

---

| Component        | Complexity |
| ---------------- | ---------- |
| Time Complexity  | O(n log n) |
| Space Complexity | O(n)       |

