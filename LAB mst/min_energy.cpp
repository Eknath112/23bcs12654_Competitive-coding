#include <bits/stdc++.h>
using namespace std;

int minInitEnergy(vector<vector<int>>& t) {
    
    sort(t.begin(), t.end(), [](vector<int>& a, vector<int>& b) {
        return (a[1] - a[0]) > (b[1] - b[0]);
    });

    int e = 0;
    int initE = 0;

    for (auto &x : t) {
        int act = x[0];
        int minE = x[1];

        if (e < minE) {
            initE += (minE - e);
            e = minE;
        }

        e -= act;
    }

    return initE;
}

int main() {
    //vector<vector<int>> t = {{1,2},{2,4},{4,8}};
    int n;cin>>n;
    vector<vector<int>>t;
    for(int i=0;i<n;i++){
        int a,b;cin>>a>>b;
        t.push_back({a,b});
    }
    cout << minInitEnergy(t);

    return 0;
}
