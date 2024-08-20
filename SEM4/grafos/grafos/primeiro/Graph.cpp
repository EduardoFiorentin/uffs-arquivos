#include "./Graph.h"
#include "./Edge.h"
#include <iostream>

using namespace std;

Graph::Graph(int num_vertices) {
    if (num_vertices <= 0) throw(invalid_argument("Numero de vertices invalido!"));

    num_vertices_ = num_vertices;
    num_edges_ = 0; 

    // realocar sua memória para o tamanho num_vertices
    adjacency_matrix_.resize(num_vertices);

    for (int i = 0; i < num_vertices; i++) {

        // segundo valor - valor para cada posição do novo vetor (padrão = 0)
        adjacency_matrix_[i].resize(num_vertices, 0);
    }


}

int Graph::get_vertices_num() {
    return num_vertices_; 
}

int Graph::get_edges_num() {
    return num_edges_; 
}

bool Graph::find_edge(Edge e) {
    if (adjacency_matrix_[e.v1][e.v2] != 0) return true;
    return false; 
}; 

void Graph::insert_edge(Edge e) {
    if (this->find_edge(e)) return;     // Se a aresta já existe 
    if (e.v1 == e.v2) return;           // Se a aresta for um laço 

    adjacency_matrix_[e.v1][e.v2] = 1;
    adjacency_matrix_[e.v2][e.v1] = 1;

    num_edges_++; 
}; 

void Graph::remove_edge(Edge e) {
    if (!find_edge(e)) return;          // se a aresta não existe 
    if (e.v1 == e.v2) return;           // Se a aresta for um laço 

    adjacency_matrix_[e.v1][e.v2] = 0;
    adjacency_matrix_[e.v2][e.v1] = 0;

    num_edges_--; 

}; 

void Graph::print_graph() {
    for (int i = 0; i < num_vertices_; i++) {
        cout << i << ": ";
        for (int j = 0; j < num_vertices_; j++) {
            if (adjacency_matrix_[i][j] != 0) cout << j << " "; 
        }
        cout << endl; 
    }
}; 
