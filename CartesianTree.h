#include <iostream>     
#include <vector>      
#include <stack>      
#include <bitset>    
#include <cassert>  
#include <cmath>   

using namespace std;

#pragma once

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

        for (int i = 0; i < n; i++) if (par[i] == -1) root = i;

        assert(root != -1);
    }

    void dbg() {
        cout << "root : " << root << endl;
        for (int i = 0; i < n; i++) {
            cout << i << " : " << L[i] << " " << R[i] << " " << par[i] << endl; 
        }
        cout << "mask: " << bitset<20>(mask) << " = " << mask << endl;
    }
};
