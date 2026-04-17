### Approach
We are asked to determine if there exists a permutation of the alphabet such that the given list of names is sorted lexicographically under that order.
  This is essentially a topological sorting problem:
    -Compare adjacent names in the list:
    -Find the first differing character between them.
    -That gives us a constraint: char1 must come before char2 in the alphabet.
    -Build a directed edge char1 → char2.

  Prefix condition:
    -If one name is a prefix of another, the shorter must come first.
    -If the longer comes first, it’s Impossible.

  Graph construction:
    -We build a directed graph of 26 nodes (a–z).
    -Add edges based on constraints.

  Topological sort:
    -Perform a topological sort (Kahn’s algorithm or DFS).
    -If a cycle exists → output "Impossible".
    -Otherwise, output the order.

  Fill remaining letters:
    -If some letters have no constraints, they can appear anywhere.
    -Just append them in any order after the sorted ones.

### Algorithm 

-Read n and the list of names.
-For each consecutive pair (name[i], name[i+1]):
-Compare character by character.
-If differing characters found: add edge.
-If no differing characters and name[i] longer → Impossible.
-Run topological sort on the graph.
-If cycle → Impossible.
-Otherwise, print the resulting order.

### Code (C++)
```cpp
    #include <bits/stdc++.h>
    using namespace std;
    int main() {
        int n;
        cin >> n;
        vector<string> names(n);
        for (int i = 0; i < n; i++) cin >> names[i];
        vector<vector<int>> adj(26);
        vector<int> indegree(26, 0);
        for (int i = 0; i < n - 1; i++) {
            string &a = names[i], &b = names[i+1];
            int len = min(a.size(), b.size());
            bool found = false;
            for (int j = 0; j < len; j++) {
                if (a[j] != b[j]) {
                    adj[a[j]-'a'].push_back(b[j]-'a');
                    indegree[b[j]-'a']++;
                    found = true;
                    break;
                }
            }
            if (!found && a.size() > b.size()) {
                cout << "Impossible\n";
                return 0;
            }
        }
        queue<int> q;
        for (int i = 0; i < 26; i++)
            if (indegree[i] == 0) q.push(i);
        string order;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(char(u + 'a'));
            for (int v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0) q.push(v);
            }
        }
        if (order.size() < 26) {
            cout << "Impossible\n";
        } else {
            cout << order << "\n";
        }
        return 0;
    }
```

#### Walkthrough
Input:

Code
3
rivest
shamir
adleman
Compare rivest vs shamir: first differing char is r vs s → r < s.

Compare shamir vs adleman: first differing char is s vs a → s < a.

Constraints: r < s, s < a.
Topological sort gives one valid order:
b c d ... q r s a t u v w x y z

Output:

Code
bcdefghijklmnopqrsatuvwxyz
