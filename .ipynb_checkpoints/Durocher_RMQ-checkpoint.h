#include "CartesianTree.h"
#include "SparseTable.h"

using namespace std;

struct Block {
    int off;
    int mask;
    Block () {}
    Block (vector<int> &a, int x) : off(x) {
        CartesianTree ct(a);
        mask = ct.mask;
    }
};

struct Durocher_RMQ {
    int n,k;
    SparseTable st;
    vector<int> a,b,id;
    vector<int> lookup_table[10][10];
    vector<Block> blocks;

    Durocher_RMQ(vector<int> &a) : a(a) {
        n = a.size();
        k = max(1.0, round(0.5 * log(n) / log(4)));

        for (int i = 0; i < k; i++)
            for (int j = i; j < k; j++)
                lookup_table[i][j].resize(1 << (2 * k));

        back(0, 0, 0, k);

        id.resize(n);
        
        int i = 0, j = 0;
        while(i < n) {
            int mn = INT_MAX;
            vector<int> v;
            int off = i;
            for (int z = 0; z < k; z++) {
                if (i >= n) break;
                id[i] = j;
                mn = min(mn, a[i]);
                v.push_back(a[i]);
                i++;
            }
            b.push_back(mn);
            blocks.push_back(Block(v, off));
            j++;
        }

        st = SparseTable(b);

    }

    void back(int i, int sa, int mask, int n) {
        if (sa < 0 or sa > n) return;
        if (i == 2 * n) {
            if (sa) return;
            CartesianTree ct(mask);
            vector<vector<int>> all = ct.generate();
            for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    lookup_table[i][j][mask] = all[i][j];
                }
            }
            return;
        }
        back(i + 1, sa + 1, (mask << 1) + 1, n);
        back(i + 1, sa - 1, (mask << 1) + 0, n);
    }  

    int query_block(int l, int r, int j) {
        assert(l <= r);
        int mask = blocks[j].mask;
        int off = blocks[j].off;
        int pos = lookup_table[l][r][mask];
        return a[pos + off];
    }

    int query(int l, int r) {
        assert(l <= r);
        int id_l = id[l];
        int id_r = id[r];
        if (id_l == id_r) {
            int s = id_l * k;
            l -= s; r -= s;
            assert(l < k and r < k);
            return query_block(l, r, id_l);
        }
        else {
            int mn = st.query(id_l + 1, id_r - 1);
            int s1 = id_l * k;
            int s2 = id_r * k;
            l -= s1; r -= s2;
            assert(l < k and r < k);
            mn = min(mn, query_block(l, k - 1, id_l));
            mn = min(mn, query_block(0, r, id_r));
            return mn;
        }
    }
};
