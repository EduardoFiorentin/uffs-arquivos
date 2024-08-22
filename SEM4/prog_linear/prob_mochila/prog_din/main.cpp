#include <iostream> 
#include <vector>
#include <chrono>

using namespace std;

int mochila(int i, int c, vector<int> &p, vector<int> &v, int n, vector<vector<int>> &mem) {
    if (i >= n || c == 0) return 0; 
    if (mem[i][c] != -1) return mem[i][c]; 

    if (p[i] > c) {
        mem[i][c] = mochila(i+1, c, p, v, n, mem);
        return mem[i][c]; 
    } else {
        mem[i][c] = max(v[i] + mochila(i+1, c - p[i], p, v, n, mem), 
                        mochila(i+1, c, p, v, n, mem));
    }

    return mem[i][c]; 
}

int main() {
    auto inicio = chrono::high_resolution_clock::now();
    
    int n, c; 
    cin >> n >> c; 


    vector<int> p(n), v(n); 
    vector<vector<int>> mem(n, vector<int>(c+1, -1)); 

    for (int i = 0; i < n; i++) {
        cin >> v[i] >> p[i];
    }

    cout << endl << "rodando" << endl;

    cout << mochila(0, c, p, v, n, mem) << endl; 

    auto resultado = chrono::high_resolution_clock::now() - inicio;
    long double seconds = chrono::duration_cast<std::chrono::milliseconds>(resultado).count();
    cout << "Tempo: " << seconds / 1000 << " segundos" << endl; 

}
