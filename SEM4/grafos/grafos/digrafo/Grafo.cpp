/*
 * Tarefa 01 - Grafo - Listas de Adjacencia
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Daniele Rohr
 * Matricula: 2121101060
 * 
 * Nome:      Eduardo Fiorentin
 * Matricula: 2211100002
 */

#include "./Grafo.h"
#include "./Aresta.h"
#include "./Filapri_min.h"
#include <iostream>
#include <limits>
#include <limits>

#define INF std::numeric_limits<int>::max()

using namespace std; 

Grafo::Grafo(int num_vertices) {
    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    lista_adj_.resize(num_vertices_);

};

int Grafo::get_num_vertices() {
    return num_vertices_; 
};

int Grafo::num_arestas() {
    return num_arestas_; 
}

// voltar o encontra no insere 
// bool Grafo::encontra_aresta(Aresta e) {
//     for (int adj : lista_adj_[e.v1]) {
//         if (adj == e.v2) {
//             return true;
//         }
//     }
//     for (int adj : lista_adj_[e.v2]) {
//         if (adj == e.v1) {
//             return true;
//         }
//     }
//     return false; 
// }

void Grafo::insere_aresta(Aresta e) {

    // if (encontra_aresta(e)) return; 
    // if (e.v1 == e.v2) return; 

    lista_adj_[e.v1].push_back({e.v2, e.peso});
    // lista_adj_[e.v2].push_back(e.v1);
    num_arestas_++;

}

// void Grafo::remove_aresta(Aresta e) {

//     if (!encontra_aresta(e)) return; 

//     lista_adj_[e.v1].remove(e.v2);
//     lista_adj_[e.v2].remove(e.v1);

//     num_arestas_--; 

// }

void Grafo::imprime_grafo() {

    int i = 0; 
    for (auto vert: lista_adj_) {
        std::cout << "\n" << i << ":"; 
        
        for (auto arst: vert) {
            std::cout << " " << arst.first; 
        }

        i++;
    }
    std::cout << std::endl; 

}

int Grafo::grau_vertice(int v) {
    if (v < 0 || v >= num_vertices_) return -1; 

    int deg = 0; 
    for (auto edge: lista_adj_[v]) {
        if ( edge.first != 0 ) deg++;
    }

    return deg; 
}; 

// int Grafo::num_arestas_subgrafo_induzido(vector<int> &vertices, Grafo &graph) {

//     Grafo subgrafo_induzido(num_vertices_); 

//     for (int i = 0; i < num_vertices_; i++) {
//         if (vertices[i]) {
//             for (int j = 0; j < num_vertices_; j++) {
//                 if (vertices[j] && graph.encontra_aresta(Aresta(i, j))) {
//                     subgrafo_induzido.insere_aresta(Aresta(i, j)); 
//                 }
//             }
//         }
//     }

//     return subgrafo_induzido.num_arestas(); 
// }

// void Grafo::imprime_complemento() {
//     for (int i = 0; i < num_vertices_; i++) {
//         cout << i << ":";
//         for (int j = 0; j < num_vertices_; j++) {
//             if (i != j && !encontra_aresta(Aresta(i, j))) std::cout << " " << j; 
//         }
//         cout << endl; 
        
//     }
//     std::cout << std::endl; 

// }

    void Grafo::dijkstra(int s, vector<int> &pai, vector<int> &dp) {
        for (int w = 0; w < lista_adj_.size(); w++) {
            dp[w] = INF;
            pai[w] = -1; 
        }
        dp[s] = 0; 
        int peso_uv = 0; 

        Filapri_min<int> fila_prio(lista_adj_.size()); 

        fila_prio.insere(0, 0);
        for (int i = 1; i < lista_adj_.size(); i++) {
            fila_prio.insere(i, INF); 
        }

        while (!fila_prio.vazia()) {
            // pair <prioridade, indice_elemento_na_lista>
            pair<int, int> menor_prio = fila_prio.remove(); 

            // u = menor_prio (indice na lista = second)
            // v = cada vizinho de saída de u (indice na lista = first)

            if (dp[menor_prio.second] != INF) {
                for (auto viz_saida: lista_adj_[menor_prio.second]) {
                    

                    // encontra peso da aresta uv
                    for (auto acha_v: lista_adj_[menor_prio.second]) {
                        if (acha_v.first == menor_prio.second) {
                            peso_uv = acha_v.second;
                        }
                    }

                    if (dp[viz_saida.first] > (dp[menor_prio.second] + peso_uv)) {
                        dp[viz_saida.first] = (dp[menor_prio.second] + peso_uv);
                        pai[viz_saida.first] = menor_prio.second; 
                    }

                    fila_prio.diminui_prio(viz_saida.first, (dp[menor_prio.second] + peso_uv));
                }
            }
        }

    };
