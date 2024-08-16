#include <iostream>
#include <vector>

using namespace std;

int cut_rod(vector<int> p, int n) {
    if (n == 0) return 0;
    int q = -1;
    for (int i = 1; i <= n; i++) {
        q = max(q, p[i-1] + cut_rod(p, n - i)); 
    }
    return q;
}

int main() {
    int n; 
    cin >> n;
    vector<int> p = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30}; 
    vector<int> mem(n); 

    cout << cut_rod(p, n) << endl; 

}