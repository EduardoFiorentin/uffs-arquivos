#include "./Graph.h"
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

bool Graph::find_edge(int a, int b) {
    if (a < 0 || a >= num_vertices_) throw(invalid_argument("Valor de a é inválido!"));
    if (b < 0 || b >= num_vertices_) throw(invalid_argument("Valor de b é inválido!"));

    if (adjacency_matrix_[a][b] == 1 || adjacency_matrix_[b][a] == 1) return true;
    else return false;
}; 

void Graph::insert_edge(int a, int b) {
    if (a < 0 || a >= num_vertices_) throw(invalid_argument("Valor de a é inválido!"));
    if (b < 0 || b >= num_vertices_) throw(invalid_argument("Valor de b é inválido!"));

    adjacency_matrix_[a][b] = 1; 
    adjacency_matrix_[b][a] = 1; 
}; 

void Graph::remove_edge(int a, int b) {
    if (a < 0 || a >= num_vertices_) throw(invalid_argument("Valor de a é inválido!"));
    if (b < 0 || b >= num_vertices_) throw(invalid_argument("Valor de b é inválido!"));

    adjacency_matrix_[a][b] = 0; 
    adjacency_matrix_[b][a] = 0; 
}; 

void Graph::print_graph() {
    int i = 0; 
    for (vector<int> element : adjacency_matrix_) {
        cout << "linha " << i;
    }
}; 
