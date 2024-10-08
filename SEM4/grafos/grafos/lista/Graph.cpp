#include "./Graph.h"
#include "./Edge.h"
#include <iostream>


Grafo::Grafo(int num_vertices) {
    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    lista_adj_.resize(num_vertices_);

};

int Grafo::get_num_vertices() {
    return num_vertices_; 
};

int Grafo::get_num_edges() {
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

    std::cout << "Vizinhos:"; 
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
