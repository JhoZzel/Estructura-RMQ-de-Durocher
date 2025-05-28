mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

int random(int L, int R) {
    return uniform_int_distribution<int>(L, R)(rnd);
}
