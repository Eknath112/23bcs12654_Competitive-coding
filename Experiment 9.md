## Approach

We want the shortest string that contains both `str1` and `str2` as subsequences.  
This is closely related to the **Longest Common Subsequence (LCS)**:

- If we know the LCS of `str1` and `str2`, we can merge the two strings around that LCS to build the shortest supersequence.
- Why? Because the LCS represents the overlapping part we don’t need to duplicate.

---

## Algorithm

1. **Compute LCS**:
   - Use DP to find the longest common subsequence of `str1` and `str2`.
   - Standard DP: `dp[i][j]` = length of LCS of `str1[0..i-1]` and `str2[0..j-1]`.

2. **Reconstruct the SCS**:
   - Start from the end of both strings.
   - While both indices are > 0:
     - If characters match → add it once to result, move both indices.
     - Else → move in the direction of the larger `dp` value, adding the character from that string.
   - Add remaining characters from either string.

3. **Reverse the result** (since we build backwards).

---

## Code (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

string shortestCommonSupersequence(string str1, string str2) {
    int n = str1.size(), m = str2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    // Build LCS table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (str1[i-1] == str2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    // Reconstruct SCS
    int i = n, j = m;
    string res;
    while (i > 0 && j > 0) {
        if (str1[i-1] == str2[j-1]) {
            res.push_back(str1[i-1]);
            i--; j--;
        } else if (dp[i-1][j] >= dp[i][j-1]) {
            res.push_back(str1[i-1]);
            i--;
        } else {
            res.push_back(str2[j-1]);
            j--;
        }
    }
    while (i > 0) {
        res.push_back(str1[i-1]);
        i--;
    }
    while (j > 0) {
        res.push_back(str2[j-1]);
        j--;
    }

    reverse(res.begin(), res.end());
    return res;
}

int main() {
    string str1 = "abac", str2 = "cab";
    cout << shortestCommonSupersequence(str1, str2) << endl; // Output: "cabac"
    return 0;
}
```

---

## Example Walkthrough

Input:
```
str1 = "abac", str2 = "cab"
```

- LCS = `"ab"`.
- Merge around LCS:
  - Start with `"cabac"`.
- Both `str1` and `str2` are subsequences of `"cabac"`.
- Length is minimal.

---

## Complexity

- **Time**: `O(n*m)` for DP table.  
- **Space**: `O(n*m)` (can be optimized to `(O(min(n,m)))` if needed).  

---


