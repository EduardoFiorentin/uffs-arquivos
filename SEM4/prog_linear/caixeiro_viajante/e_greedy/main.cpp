// #include <iostream> 
// #include <vector> 
// #include <chrono>
// #include <algorithm>
// #include <math.h>

// using namespace std;

// double distance(pair<int, int> x, pair<int, int> y) {
//     // return sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2));
//     int xd = x.first - x.second;
//     int yd = y.first - y.second;
//     int dij = (int) (sqrt(xd*xd + yd*yd) + 0.5);
//     return dij; 
// }


// int main() {
//     vector<pair<int, int>> locs;
//     vector<int> permut; 
//     int x, y, ref, prm;
//     double shortest_dist, total_step_dist; 


//     // leitura dos dados 
//     while (cin >> x >> y) {
//         locs.push_back(make_pair(x, y));
//     }

//     permut.resize(locs.size()); 

//     for (int i = 0; i < locs.size(); i++) {
//         permut[i] = i;
//     }

//     shortest_dist = INT32_MAX; 

//     do {
        
//         total_step_dist = 0; 

//         for (int i = 0; i < locs.size(); i++) {
//             total_step_dist += distance(locs[permut[i]], locs[permut[i + 1]]); 
//         }

//         total_step_dist += distance(locs[permut[locs.size() - 1]], locs[permut[0]]);

//         if (total_step_dist < shortest_dist) shortest_dist = total_step_dist; 

    
//     } while (next_permutation(locs.begin(), locs.end()));

//     cout << shortest_dist << endl; 
// }

// ordem de entrada      
//  vertice     coordenada 
//  0           3, 5 

#include <iostream> 
#include <vector> 
#include <algorithm>
#include <cmath> // para sqrt

using namespace std;

double distance(pair<int, int> x, pair<int, int> y) {
    int xd = x.first - y.first;
    int yd = x.second - y.second;
    return sqrt(xd * xd + yd * yd); 
}

int main() {
    vector<pair<int, int>> locs;
    vector<int> permut; 
    int x, y;
    double shortest_dist, total_step_dist; 

    // leitura dos dados 
    while (cin >> x >> y) {
        locs.push_back(make_pair(x, y));
    }

    permut.resize(locs.size()); 

    for (int i = 0; i < locs.size(); i++) {
        permut[i] = i;
    }

    shortest_dist = numeric_limits<double>::infinity(); 

    do {
        total_step_dist = 0.0;

        for (int i = 0; i < locs.size() - 1; i++) {
            total_step_dist += distance(locs[permut[i]], locs[permut[i + 1]]); 
        }

        // Adiciona a distância do último ponto de volta ao ponto inicial
        total_step_dist += distance(locs[permut[locs.size() - 1]], locs[permut[0]]);

        if (total_step_dist < shortest_dist) 
            shortest_dist = total_step_dist; 

    } while (next_permutation(permut.begin(), permut.end()));

    cout << "Menor distância: " << shortest_dist << endl; 
    return 0;
}
