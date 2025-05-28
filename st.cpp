#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vector<int>> st;
 
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

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &e : a) cin >> e;
    SparseTable st(a);
    while(q--) {
        int l,r;
        cin >> l >> r;
        r--;
        cout << st.query(l, r) << "\n";
    }
    return 0;
}
