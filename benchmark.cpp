#include "Durocher_RMQ.h"
#include "test.h"
using namespace std;

struct Timer {
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using Duration = std::chrono::milliseconds;

    TimePoint start, end;
    Duration duration;

    Timer () {}

    void start_timer() {
        start = Clock::now();
    }

    void stop_timer() {
        end = Clock::now();
        duration = std::chrono::duration_cast<Duration>(end - start);
    }

    void print_duration() const {
        cout << "Tiempo transcurrido: " << duration.count() << " ms" << endl;
    }
} timer;

void run_benchmark() {
    const int MAX_N = 2e6;
    const int MAX_VALUE = 1e9;
    const int MAX_QUERIES = 2e6;

    cout << "Generacion de datos aleatorios...\n";

    int n = MAX_N;
    int q = MAX_QUERIES;

    cout << "n = " << n << "\n";
    cout << "q = " << q << "\n";

    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = random(1, MAX_VALUE);

    cout << "Generacion de las queries...\n";

    vector<pair<int,int>> queries(q);
    for (auto &[l, r] : queries) {
        l = random(0, n - 1);
        r = random(0, n - 1);
        if (l > r) swap(l, r);
    }

    cout << "Inicio de la comparacion SparseTable VS Durocher\n";
    cout << "\n== Sparse Table ==\n";

    cout << "Precomputacion...\n";
    timer.start_timer();
    
    SparseTable sparse_table(a);
    
    timer.stop_timer();
    timer.print_duration();
    
    timer.start_timer();
    
    cout << "Respondiendo las queries...\n";
    for (auto [l, r] : queries) {
        int ans = sparse_table.query(l, r);
        //cerr << ans << "\n";
    }


    timer.stop_timer();
    timer.print_duration();
    

    cout << "\n== Estructura de Durocher ==\n";

    cout << "Precomputacion...\n";
    timer.start_timer();
    
    Durocher_RMQ durocher(a);
    
    timer.stop_timer();
    timer.print_duration();
    


    timer.start_timer();

    cout << "Respondiendo las queries...\n";
    for (auto [l, r] : queries) {
        int ans = durocher.query(l, r);
        //cerr << ans << "\n";
    }
     
    timer.stop_timer();
    timer.print_duration();
}

int main() {
    run_benchmark();
    return 0;
}
