#include <bits/stdc++.h> 

using namespace std;

double distance(pair<int, int> &x, pair<int, int> &y) {
    int xd = x.first - y.first;
    int yd = x.second - y.second;
    int dij = (int) (sqrt(xd * xd + yd * yd) + 0.5);
    return  dij;
}

int main() {

    auto inicio = chrono::high_resolution_clock::now();

    vector<pair<int, int>> locs;
    vector<int> permut; 
    double x, y, lixo;
    double shortest_dist, total_step_dist; 

    // leitura dos dados 
    while (cin >> lixo >> x >> y) {
        locs.push_back(make_pair(x, y));
    }

    for (int i = 0; i < locs.size(); i++) {
        permut.push_back(i);
    }

    shortest_dist = INFINITY; 

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

    auto resultado = chrono::high_resolution_clock::now() - inicio;
    long double seconds = chrono::duration_cast<std::chrono::milliseconds>(resultado).count();
    cout << "Tempo: " << seconds / 1000 << " segundos" << endl; 

    return 0;
}