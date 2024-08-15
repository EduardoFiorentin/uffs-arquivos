#include <iostream> 
#include <stdlib.h>
#include <vector>

using namespace std;

int mochila(int i, int c, vector<int> p, vector<int> v, int n) {
    if (i >= n || c == 0) return 0; 
    if (p[i] > c) return mochila(i+1, c, p, v, n);

    if (p[i] > c) {
        return mochila(i+1, c, p, v, n);
    }

    return max(v[i] + mochila(i+1, c - p[i], p, v, n), mochila(i+1, c, p, v, n));
}

int main() {
    
    int n, c; 
    cin >> n;
    cin >> c; 

    // int p[] = malloc(sizeof(int) * n); 
    vector<int> p(n), v(n); 


    for (int i = 0; i < n; i++) {
        cin >> v[i];
        cin >> p[i]; 
    }

    cout << endl << "rodando" << endl;

    cout << mochila(0, c, p, v, n) << endl; 

}