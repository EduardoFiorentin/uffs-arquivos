// #include <bits/stdc++.h> 
#include <iostream> 
#include <vector> 
#include <algorithm>
#include <cmath> // para sqrt
#include <chrono> 

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
    vector<int> marcado, caminho;
    double x, y, lixo, current, adc;
    double shortest_dist, local_aux, total_distance = 0; 

    // leitura dos dados 
    while (cin >> lixo >> x >> y) {
        locs.push_back(make_pair(x, y));
    }

    marcado.resize(locs.size());

    shortest_dist = INFINITY; 
    current = 0;
    marcado[current] = 1;
    caminho.push_back(current);

    while(caminho.size() < locs.size()){
        
        shortest_dist = INFINITY;

        for(int i=0; i<locs.size(); i++){
            if(!marcado[i]){
                local_aux = distance(locs[current], locs[i]);
                if(local_aux < shortest_dist){
                    shortest_dist = local_aux;
                    adc = i;
                }
            }
        }
        caminho.push_back(adc);
        marcado[adc] = 1;
        current = adc;
        total_distance += shortest_dist;

    }

    total_distance += distance(locs[current], locs[0]);

    cout << "Menor distância: " << total_distance << endl; 

    auto resultado = chrono::high_resolution_clock::now() - inicio;
    long double seconds = chrono::duration_cast<std::chrono::milliseconds>(resultado).count();
    cout << "Tempo: " << seconds / 1000 << " segundos" << endl; 

    return 0;
}