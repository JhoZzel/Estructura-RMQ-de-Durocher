#include "SparseTable.h"
#include "Durocher_RMQ.h"
#include "test.h"
using namespace std;

const int MAX_N = 1e6;
const int MAX_VALUE = 1e9;
const int MAX_QUERIES = 1e5;

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
    Durocher_RMQ rmq(a);
    for (auto [l, r] : queries) {
        int sparse_table_ans = st.query(l, r);
        int durocher_ans = rmq.query(l, r);
        assert(sparse_table_ans == durocher_ans);
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
