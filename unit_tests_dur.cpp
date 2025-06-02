#include "Durocher_RMQ.h"
using namespace std;

void run_unit_test(int id, vector<int> &a, vector<tuple<int, int, int>> &queries) {
    Durocher_RMQ rmq(a);
    for (auto &[l, r, ans] : queries) {
        int durocher_ans = rmq.query(l, r);
        assert(ans == durocher_ans && "Error: Se esperaba un valor distinto para la query");
    }
    cout << "Test " << id << " unitario. OK!\n";
    cout << "Todas las queries fueron respondidas correctamente.\n\n";
}

void run_unit_tests() {
    // Test Case 1
    vector<int> test1 = {4, 3, 2, 1, 10, 2, 20};
    vector<tuple<int, int, int>> queries1 = {
        {0, 6, 1},
        {1, 2, 2},
        {0, 0, 4},
        {3, 5, 1},
        {5, 6, 2}
    };
    run_unit_test(1, test1, queries1);

    // Test Case 2
    vector<int> test2 = {7, 5, 3, 1, 3, 5, 7};
    vector<tuple<int, int, int>> queries2 = {
        {0, 6, 1},
        {1, 3, 1},
        {2, 4, 1},
        {0, 2, 3},
        {5, 6, 5}
    };
    run_unit_test(2, test2, queries2);

    // Test Case 3
    vector<int> test3 = {1, 1, 1, 1, 1};
    vector<tuple<int, int, int>> queries3 = {
        {0, 4, 1},
        {1, 3, 1},
        {2, 2, 1},
        {0, 0, 1},
        {4, 4, 1}
    };
    run_unit_test(3, test3, queries3);

    // Test Case 4
    vector<int> test4 = {10, 20, 30, 40, 50};
    vector<tuple<int, int, int>> queries4 = {
        {0, 1, 10},
        {1, 3, 20},
        {2, 4, 30},
        {0, 4, 10},
        {3, 3, 40}
    };
    run_unit_test(4, test4, queries4);

    // Test Case 5
    vector<int> test5 = {5, 4, 3, 2, 1};
    vector<tuple<int, int, int>> queries5 = {
        {0, 4, 1},
        {0, 0, 5},
        {1, 2, 3},
        {2, 4, 1},
        {3, 3, 2}
    };
    run_unit_test(4, test5, queries5);

    cout << "=> Todas las pruebas unitarias han pasado exitosamente!\n";
}

int main() {
    run_unit_tests();
    return 0;
}

