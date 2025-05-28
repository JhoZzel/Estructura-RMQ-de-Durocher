#include <bits/stdc++.h>
#include "SparseTable.h"
#include "random.h"
using namespace std;

const int MAX_N = 3000 + 4;
const int MAX_V = 1e9;

int main() {
    int nTests = 100;
    for (int t = 1; t <= nTests; t++) {
        cout << "Test #" << t << ": ";
        int n = random(1, MAX_N);
        vector<int> a(n);
        for (int &x : a) x = random(1, MAX_V);

        auto brute = [&](int l, int r) {
            int mn = INT_MAX;
            for (int i = l; i <= r; i++) {
                mn = min(mn, a[i]);
            }
            return mn;
        };

        SparseTable st(a);
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                assert(st.query(i,j) == brute(i, j));
            }
        }
        cout << "passed succesfully\n";
    }
    
        
    return 0;
}

