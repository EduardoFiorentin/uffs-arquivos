#include <iostream> 
#include <stdlib.h>
#include <vector>

using namespace std;

int mochila(int i, int c, vector<int> p, vector<int> v, int n, vector<vector<int>> mem) {
    if (i >= n || c == 0) return 0; 
    if (mem[i][c] != -1) return mem[i][c]; 

    // capacidade menor do que peso do item atual - apenas testa com o proximo 
    if (p[i] > c) mem[i][c] = mochila(i+1, c, p, v, n, mem);

    // caso seja possível pegar item atual - escolhe o máximo entre incluir e não incluir o item atual 
    else mem[i][c] = max(v[i] + mochila(i+1, c - p[i], p, v, n, mem), mochila(i+1, c, p, v, n, mem));

    return mem[i][c]; 
}

int main() {
    
    int n, c; 
    cin >> n;
    cin >> c; 

    // int p[] = malloc(sizeof(int) * n); 
    vector<int> p(n), v(n); 
    vector<vector<int>> mem ( n+1, vector<int>( c+1, -1 )); 

    for (int i = 0; i < n; i++) {
        cin >> v[i];
        cin >> p[i]; 
    }

    cout << endl << "rodando" << endl;

    cout << mochila(0, c, p, v, n, mem) << endl; 

}