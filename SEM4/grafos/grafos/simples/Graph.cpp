#include "./Graph.h"
#include "./Edge.h"
#include <iostream>
#include <vector>

using namespace std;

Grafo::Grafo(int num_vertices) {
    if (num_vertices <= 0) throw(invalid_argument("Numero de vertices invalido!"));

    num_vertices_ = num_vertices;
    num_arestas_ = 0; 

    // realocar sua memória para o tamanho num_vertices
    lista_adj_.resize(num_vertices);

    for (int i = 0; i < num_vertices; i++) {

        // segundo valor - valor para cada posição do novo vetor (padrão = 0)
        lista_adj_[i].resize(num_vertices, 0);
    }


}

int Grafo::get_vertices_num() {
    return num_vertices_; 
}

int Grafo::get_edges_num() {
    return num_arestas_; 
}

bool Grafo::encontra_aresta(Aresta e) {
    if (lista_adj_[e.v1][e.v2] != 0) return true;
    return false; 
}; 

void Grafo::insere_aresta(Aresta e) {
    if (this->encontra_aresta(e)) return;     // Se a aresta já existe 
    if (e.v1 == e.v2) return;           // Se a aresta for um laço 

    lista_adj_[e.v1][e.v2] = 1;
    lista_adj_[e.v2][e.v1] = 1;

    num_arestas_++; 
}; 

void Grafo::remove_aresta(Aresta e) {
    if (!encontra_aresta(e)) return;          // se a aresta não existe 
    if (e.v1 == e.v2) return;           // Se a aresta for um laço 

    lista_adj_[e.v1][e.v2] = 0;
    lista_adj_[e.v2][e.v1] = 0;

    num_arestas_--; 

}; 

void Grafo::imprime_grafo() {
    for (int i = 0; i < num_vertices_; i++) {
        cout << i << ": ";
        for (int j = 0; j < num_vertices_; j++) {
            if (lista_adj_[i][j] != 0) cout << j << " "; 
        }
        cout << endl; 
    }
}; 

bool Grafo::print_graph_path(int v, int w, int marcado[], int depth) {
    for (int i = 0; i < depth; ++i) {
        printf("   ");
    }

    printf("caminho(%d, %d)\n", v, w);

    if (v == w) {
        return true;
    }

    marcado[v] = 1;

    for (int u = 0; u < num_vertices_; ++u) {
        if (lista_adj_[v][u] != 0 && marcado[u] == 0) {
            if (print_graph_path(u, w, marcado, depth + 1)) {
                return true;
            }
        }
    }
    
    return false;
}

// ajeitar isso aqui 
bool Grafo::have_path(int v, int w, std::vector<int> &visited) {

    if (v == w) {
        return true;
    }

    visited[v] = 1;

    for (int u = 0; u < num_vertices_; u++) {
        if (lista_adj_[v][u] != 0 && visited[u] == 0) {
            if (have_path(u, w, visited)) {
                return true;
            }
        }
    }
    
    return false;

};

bool Grafo::is_connected() {
    vector<int> visited(num_vertices_, 0); 

    for (int i = 0; i < (num_vertices_ - 1); i++) {
        for (int j = (i + 1); j < num_vertices_; j++) {
            // Reseta os valores do vetor marcado
            // for (int k = 0; k < num_vertices_; k++) {
            //     visited[k] = 0;
            // }
            if (!have_path(i, j, visited)) return false; 
        }
    }
    return true; 
};
