#include <bits/stdc++.h>
using namespace std;

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

struct CartesianTree {
    int n;
    int root;
    int mask;
    vector<int> L,R,par;  
    vector<vector<int>> all;

    CartesianTree(vector<int> &a) {
        n = a.size();

        L.assign(n, -1);
        R.assign(n, -1);
        par.assign(n, -1);

        root = -1;
        mask = 0;

        build_from_array(a);
    }
    
    CartesianTree(int mask) : mask(mask) {
        n = __lg(mask) + 1;

        assert(n % 2 == 0);

        n >>= 1;

        L.assign(n, -1);
        R.assign(n, -1);
        par.assign(n, -1);
 
        root = -1;

        build_from_mask();
    }

    void build_from_mask() {
        stack<int> st;
        int cur = 0;
        int last = -1;
        for (int i = 2 * n - 1; i >= 0; i--) {
            if ((mask >> i) & 1) {
                if (last == -1) {
                    if (st.empty()) {
                        st.emplace(cur++);
                    }
                    else {
                        int now = st.top();
                        R[now] = cur;
                        par[cur] = now;
                        st.emplace(cur++);
                    }
                } else {
                    if (!st.empty()) {
                        int p = par[last];
                        R[p] = cur;
                        par[cur] = p;
                    }
                    L[cur] = last;
                    par[last] = cur;
                    st.emplace(cur++);
                }
                last = -1;
            } else {
                last = st.top();
                st.pop();
            }
        }

        for (int i = 0; i < n; i++) if (par[i] == -1) root = i;
        assert(root != -1);
    }

    vector<vector<int>> generate() {
        all.assign(n, vector<int>(n, -1));
        dfs(root, 0, n - 1);
        return all;
    }

    void dfs(int now, int l, int r) {
        if (now == -1) return;
        dfs(L[now], l, now - 1);
        for (int i = l; i <= now; i++) {
            for (int j = now; j <= r; j++) {
                assert(all[i][j] == -1);
                all[i][j] = now;
            }
        }
        dfs(R[now], now + 1, r);
    }

    void build_from_array(vector<int> &a) {
        stack<int> st;
        for (int i = 0; i < n; i++) {
            if (st.empty()) {
                mask = (mask << 1) | 1;
                st.emplace(i);
                continue;
            }
            int now = st.top();
            if (a[i] > a[now]) {
                R[now] = i;
                par[i] = now;
                mask = (mask << 1) | 1;
                st.emplace(i);
            } else {
                int last = -1;
                do {
                    last = now;
                    mask = (mask << 1) | 0;
                    st.pop();
                    if (st.empty()) break;
                    now = st.top();
                } while(a[i] < a[now]);

                assert(last != -1);

                if (!st.empty()) {
                    int p = par[last];
                    R[p] = i;
                    par[i] = p;
                }

                L[i] = last;
                par[last] = i;

                mask = (mask << 1) | 1;
                st.emplace(i);
            }
        }
        while(!st.empty()) {
            mask = (mask << 1) | 0;
            st.pop();
        }

        for (int i = 0; i < n; i++) {
            if (par[i] == -1) root = i;
        }
        assert(root != -1);
    }

    void dbg() {
        cout << "root : " << root << endl;
        for (int i = 0; i < n; i++) {
            cout << i << " : " << L[i] << " " << R[i] << " " << par[i] << endl; 
        }
        cout << "mask: " << bitset<30>(mask) << " -> " << mask << endl;
    }
};

struct Block {
    int off;
    int mask;
    Block () {}
    Block (vector<int> &a, int x) : off(x) {
        CartesianTree ct(a);
        mask = ct.mask;
    }
};

struct Durocher {
    int n,k;
    vector<int> a;
    vector<int> b;
    vector<int> id; 
    SparseTable st;
    vector<int> lookup_table[10][10];
    vector<Block> blocks;

    Durocher(vector<int> &a) : a(a) {
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
        int mask = blocks[j].mask;
        int off = blocks[j].off;
        int pos = lookup_table[l][r][mask];
        return a[pos + off];
    }

    int query(int l, int r) {
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


int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &e : a) cin >> e;
    
    Durocher dr(a);
    while(q--) {
        int l,r;
        cin >> l >> r;
        r--;
        cout << dr.query(l, r) << "\n";
    }

    return 0;
}

