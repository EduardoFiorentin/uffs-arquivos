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

#include "./Graph.h"
#include "./Edge.h"
#include <iostream>

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

bool Grafo::encontra_aresta(Aresta e) {
    bool ad1, ad2 = false; 

    for (int adj : lista_adj_[e.v1]) {
        if (adj == e.v2) {
            return true;
        }
    }
    for (int adj : lista_adj_[e.v2]) {
        if (adj == e.v1) {
            return true;
        }
    }

    return (ad1 && ad2); 
}; 

void Grafo::insere_aresta(Aresta e) {

    if (encontra_aresta(e)) return; 
    if (e.v1 == e.v2) return; 

    lista_adj_[e.v1].push_back(e.v2);
    lista_adj_[e.v2].push_back(e.v1);
    num_arestas_++;

}

void Grafo::remove_aresta(Aresta e) {

    if (!encontra_aresta(e)) return; 

    lista_adj_[e.v1].remove(e.v2);
    lista_adj_[e.v2].remove(e.v1);

    num_arestas_--; 

}

void Grafo::imprime_grafo() {

    int i = 0; 
    for (auto vert: lista_adj_) {
        std::cout << "\n" << i << ":"; 
        
        for (int arst: vert) {
            std::cout << " " << arst; 
        }

        i++;
    }
    std::cout << std::endl; 

}

int Grafo::grau_vertice(int v) {
    if (v < 0 || v >= num_vertices_) return -1; 

    int deg = 0; 
    for (int edge: lista_adj_[v]) {
        if ( edge != 0 ) deg++;
    }

    return deg; 
}; 

int Grafo::num_arestas_subgrafo_induzido(vector<int> &vertices, Grafo &graph) {

    Grafo induced_subgraph(num_vertices_); 

    for (int i = 0; i < num_vertices_; i++) {
        if (vertices[i]) {
            for (int j = 0; j < num_vertices_; j++) {
                if (vertices[j] && graph.encontra_aresta(Aresta(i, j))) {
                    induced_subgraph.insere_aresta(Aresta(i, j)); 
                }
            }
        }
    }

    return induced_subgraph.num_arestas(); 
}

void Grafo::imprime_complemento() {
    for (int i = 0; i < num_vertices_; i++) {
        cout << i << ":";
        for (int j = 0; j < num_vertices_; j++) {

            if (i != j && !encontra_aresta(Aresta(i, j))) std::cout << " " << j; 

        }
        cout << endl; 
        
    }
    std::cout << std::endl; 

}