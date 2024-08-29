#include <iostream> 
#include <vector> 
#include <algorithm>
#include <cmath> // para sqrt
#include <chrono> 

using namespace std;

double distance(pair<int, int> &x, pair<int, int> &y) {
    int xd = x.first - y.first;
    int yd = x.second - y.second;
    return (int) (sqrt(xd * xd + yd * yd) + 0.5); 
}

int main() {

    auto inicio = chrono::high_resolution_clock::now();

    vector<pair<int, int>> locs;
    vector<int> c, verified; 

    pair<int, int> act; 
    // vector<int> permut; 
    int z, x, y;
    double shortest_dist; 

    // leitura dos dados 
    while (cin  >> z >> x >> y) {
        locs.push_back(make_pair(x, y));
    }

    shortest_dist = INFINITY; 
    int nearest_element; 

    verified.resize(locs.size(), 0);

    // do {
    //     total_step_dist = 0.0;

    //     for (int i = 0; i < locs.size() - 1; i++) {
    //         total_step_dist += distance(locs[permut[i]], locs[permut[i + 1]]); 
    //     }

    //     // Adiciona a distância do último ponto de volta ao ponto inicial
    //     total_step_dist += distance(locs[permut[locs.size() - 1]], locs[permut[0]]);

    //     if (total_step_dist < shortest_dist) 
    //         shortest_dist = total_step_dist; 

    // } while (next_permutation(permut.begin(), permut.end()));

    act = locs[0]; 
    while (c.size() < locs.size()) {

        for (int i = 0 ; i < locs.size(); i++) {
            double dist = distance(locs[i], act);
            if ( dist < shortest_dist && verified[i]) {
                nearest_element = i; 
                shortest_dist = dist; 
            }
        }
        c.push_back(nearest_element);

    }


    cout << "Menor distância: " << shortest_dist << endl; 

    auto resultado = chrono::high_resolution_clock::now() - inicio;
    long double seconds = chrono::duration_cast<std::chrono::milliseconds>(resultado).count();
    cout << "Tempo: " << seconds / 1000 << " segundos" << endl; 

    return 0;
}
