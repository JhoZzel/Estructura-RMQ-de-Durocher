#include <iostream>
#include <vector>     
#include <algorithm>  
#include <climits>     
#include <cassert>        
#include <cmath>        

using namespace std;

#pragma once

struct SparseTable {
    vector<vector<int>> st;
    SparseTable() {}
    SparseTable(vector<int> &a) { // 0-indexed
        int n = a.size();
        int k = __lg(n) + 1;
        st.resize(n, vector<int>(k));
        for (int i = 0; i < n; i++) st[i][0] = a[i];
        for (int p = 1, d = 1; 2 * d <= n; p++, d <<= 1) {
            for (int i = 0; i + 2 * d <= n; i++) {
                st[i][p] = min(st[i][p - 1], st[i + d][p - 1]);
            }
        }
    }
    
    int query(int l, int r) {
        if (l > r) return INT_MAX; 
        int k = __lg(r - l + 1);
        int d = (1 << k);
        return min(st[l][k], st[r - d + 1][k]);
    }
};
