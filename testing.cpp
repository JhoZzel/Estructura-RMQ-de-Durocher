#include <bits/stdc++.h>
#include "SparseTable.h"
#include "random.h"
using namespace std;

const int MAX_N = 10000 + 4;
const int MAX_V = 1e9;

void back(int i, int sa, int mask, int n) {
    if (sa < 0 or sa > n) return;
    if (i == 2 * n) {
        if (sa) return;
        // Llegamos a una secuencia valida
        for (int i = 2 * n - 1; i >= 0; i--) {
            int bit = (mask >> i) & 1;
            cout << (bit ? "(" : ")");
        }
        cout << endl;
        return;
    }
    back(i + 1, sa + 1, (mask << 1) | 1, n);
    back(i + 1, sa - 1, (mask << 1) | 0, n);
}

int main() {
    int n = 3;
    back(0,0,0,n);

    return 0;
}

