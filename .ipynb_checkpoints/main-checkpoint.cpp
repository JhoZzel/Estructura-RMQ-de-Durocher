#include <bits/stdc++.h>
#include "CartesianTree.h"
#include "SparseTable.h"
#include "random.h"
using namespace std;

void back(int i, int sa, int mask, int n, vector<int> &masks) {
    if (sa < 0) return;
    if (i == 2 * n) {
        if (sa == 0) masks.push_back(mask);
        return;
    }
    back(i + 1, sa + 1, (mask << 1) + 1, n, masks);
    back(i + 1, sa - 1, (mask << 1) + 0, n, masks);
}  

unordered_map<int,int> lookup_table[10][10];

struct Block {
    int n;
    int mask;
    vector<int> a;
    Block () {}
    Block (vector<int> a) : a(a) {
        n = a.size();
        CartesianTree ct(a);
        mask = ct.mask;
    }
    int query(int l, int r) {
        int pos = lookup_table[l][r][mask];
        return a[pos];
    }
};

int main() {

    int n = 1e5;
    int k = 0.5 * log(n) / log(4);
    vector<int> masks;
    back(0, 0, 0, k, masks);
    for (int mask : masks) {
        CartesianTree ct(mask);
        vector<vector<int>> all = ct.generate();
        for (int i = 0; i < k; i++) {
            for (int j = i; j < k; j++) {
                lookup_table[i][j][mask] = all[i][j];
            }
        }
    }

    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = random(1, 1e9);

    vector<int> b;
    vector<int> id(n); 
    vector<Block> blocks;
    int i = 0, j = 0;
    while(i < n) {
        int mn = INT_MAX;
        vector<int> v;
        for (int z = 0; z < k; z++) {
            if (i >= n) break;
            id[i] = j;
            mn = min(mn, a[i]);
            v.push_back(a[i]);
            i++;
        }
        b.push_back(mn);
        blocks.push_back(Block(v));
        j++;
    }

    SparseTable st(b);
    
    auto query = [&](int l, int r) -> int {
        int id_l = id[l];
        int id_r = id[r];
        if (id_l == id_r) {
            int s = id_l * k;
            l -= s; r -= s;
            assert(l < k and r < k);
            return blocks[id_l].query(l, r);
        }
        else {
            int mn = st.query(id_l + 1, id_r - 1);
            int s1 = id_l * k;
            int s2 = id_r * k;
            l -= s1; r -= s2;
            assert(l < k and r < k);
            mn = min(mn, blocks[id_l].query(l, k - 1));
            mn = min(mn, blocks[id_r].query(0, r));
            return mn;
        }
    };

    auto brute = [&](int l, int r) -> int {
        int mn = INT_MAX;
        for (int k = l; k <= r; k++) {
            mn = min(mn, a[k]);
        }
        return mn;
    };
    
    auto test = [&](int l, int r) {
        int q1 = query(l, r);
        int q2 = brute(l, r);
        if (q1 == q2) cout << "OK!\n";
        else {
            cout << l << " " << r << " -> " << " deberia de ser " << q2 << " pero tengo " << q1 << endl; 
        }
    };
    
    SparseTable xd(a);
    for (int i = 0; i < 1000; i++) {
        int l = random(0, n - 1);
        int r = random(0, n - 1);
        if (l > r) swap(l, r);
        assert(query(l, r) == xd.query(l,r));
    }

    return 0;
}
