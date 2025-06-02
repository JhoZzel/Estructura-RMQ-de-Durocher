#include "SparseTable.h"
#include "test.h"
using namespace std;

const int MAX_N = 1e4;
const int MAX_VALUE = 1e9;
const int MAX_QUERIES = 1e5;

int naive(int l, int r, vector<int> &a) {
    assert(l <= r);
    int mn = INT_MAX;
    for (int i = l; i <= r; i++) {
        mn = min(mn, a[i]);
    }
    return mn;
}

void test() {
    int n = random(1, MAX_N);
    vector<int> a(n);
    int q = random(1, MAX_QUERIES);
    vector<pair<int,int>> queries(q);
    for (auto &[l, r] : queries) {
        l = random(0, n - 1);
        r = random(0, n - 1);
        if (l > r) swap(l, r);
    }
    SparseTable st(a);
    for (auto [l, r] : queries) {
        int naive_ans = naive(l, r, a);
        int sparse_table_ans = st.query(l, r);
        assert(naive_ans == sparse_table_ans);
    }
}

int main() {
    int tests = 100;
    for (int t = 1; t <= tests; t++) {
        cout << "Ejecutando test " << t << ": ";
        test();
        cout << "OK!\n";
    }
    return 0;
}


