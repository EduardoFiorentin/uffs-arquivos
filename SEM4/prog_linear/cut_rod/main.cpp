// #include <iostream>
// #include <vector>

// using namespace std;

// int cut_rod(vector<int> p, int n, vector<int> r) {
//     if (r[n] >= 0) return r[n]; 
    
//     int q;
//     if (n == 0) q = 0;
//     else {
//         q = -1; 
//         for (int i = 1; i < n; i++) {
//             q = max(q, p[i] + cut_rod(p, n - i, r)); 
//         }
//         r[n] = q;
//     }

//     return q;
// }

// int main() {
//     int n; 
//     cin >> n;
//     vector<int> p = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30}; 
//     vector<int> r(n);  
//     for (int i = 0; i < n; i++) {
//         r[i] = -1;
//     }
//     cout << cut_rod(p, n, r) << endl;

//     cout << endl; 
//     for (int i = 0; i < n; i++) {
//         cout << r[i]<< endl; 
//     }

// }

#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int cut_rod(vector<int>& p, int n, vector<int>& r) {
    if (r[n] >= 0) return r[n]; 
    
    int q = INT_MIN;
    if (n == 0) q = 0;
    else {
        for (int i = 1; i <= n; i++) {
            q = max(q, p[i-1] + cut_rod(p, n - i, r)); 
        }
        r[n] = q;
    }

    return r[n];
}

int main() {
    int n; 
    cin >> n;
    vector<int> p = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30}; 
    vector<int> r(n + 1, -1); 
    
    cout << cut_rod(p, n, r) << endl; 

    for (int i = 0; i <= n; i++) {
        cout << r[i] << endl; 
    }
}