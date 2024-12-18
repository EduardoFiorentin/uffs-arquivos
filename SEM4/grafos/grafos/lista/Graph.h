#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list> 
#include "./Edge.h"

class Grafo {

public:
    Grafo(int num_vertices);
    int get_num_vertices();
    int get_num_edges(); 
    bool encontra_aresta(Aresta e);
    void insere_aresta(Aresta e);
    void remove_aresta(Aresta e);
    void imprime_grafo();
    int grau_vertice(int v); 

private: 
    int num_arestas_;
    int num_vertices_;
    std::vector<std::list<int>> lista_adj_;
};

#endif