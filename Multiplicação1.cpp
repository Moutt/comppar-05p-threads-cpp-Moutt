#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

void multiplyRow(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C, int row, int N, int X) {
    for (int j = 0; j < X; ++j) {
        C[row][j] = 0;
        for (int k = 0; k < N; ++k) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
}

int main() {
    int M = 500, N = 500, X = 500;
    vector<vector<int>> A(M, vector<int>(N, 1));
    vector<vector<int>> B(N, vector<int>(X, 2));
    vector<vector<int>> C(M, vector<int>(X, 0));
    vector<thread> threads;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < M; ++i) {
        threads.push_back(thread(multiplyRow, cref(A), cref(B), ref(C), i, N, X));
    }

    for (auto &t : threads) {
        t.join();
    }

    auto end = high_resolution_clock::now();

    cout << "Multiplicação por linhas (com threads) concluída em "
         << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    return 0;
}
