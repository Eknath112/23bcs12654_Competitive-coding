## Approach

We want to partition the array into contiguous subarrays of length at most `k`. Each subarray is replaced by its maximum element repeated across its length. The goal is to maximize the total sum.

Key idea:
- At each index `i`, we can decide to form a subarray ending at `i` of length `len` (where `1 ≤ len ≤ k`).
- The contribution of that subarray is `max(arr[i-len+1 ... i]) * len`.
- We add this to the best sum achievable up to index `i-len`.

This naturally leads to a **DP formulation**.

---

## Algorithm

1. **Define DP state**:  
   `dp[i]` = maximum sum achievable using the first `i` elements of the array.

2. **Transition**:  
   For each `i` from `1` to `n`:
   - Initialize `maxVal = 0`.
   - For each possible subarray length `len` from `1` to `k` (but not exceeding `i`):
     - Update `maxVal = max(maxVal, arr[i-len])`.
     - Candidate sum = `dp[i-len] + maxVal * len`.
     - Take maximum over all candidates.

3. **Base case**:  
   `dp[0] = 0` (empty array sum).

4. **Answer**:  
   `dp[n]` (where `n = arr.length`).

---

## Code (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> dp(n+1, 0);

    for (int i = 1; i <= n; i++) {
        int maxVal = 0;
        for (int len = 1; len <= k && i - len >= 0; len++) {
            maxVal = max(maxVal, arr[i-len]);
            dp[i] = max(dp[i], dp[i-len] + maxVal * len);
        }
    }
    return dp[n];
}

int main() {
    vector<int> arr = {1,15,7,9,2,5,10};
    int k = 3;
    cout << maxSumAfterPartitioning(arr, k) << endl; // Output: 84
    return 0;
}
```

---

## Example Walkthrough

Input:
```
arr = [1,15,7,9,2,5,10], k = 3
```

- Partition `[1,15,7] → max=15 → contributes 15*3 = 45`
- Next `[9] → contributes 9`
- Next `[2,5,10] → max=10 → contributes 30`
- Total = 84

---

## Complexity

- **Time**: \(O(n \cdot k)\) since for each index we check up to `k` lengths.  
- **Space**: \(O(n)\) for the DP array.

---

