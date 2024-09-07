#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Edge.h"

class Grafo {
public:
    Grafo(int num_vertices);

    int get_vertices_num();
    int get_edges_num(); 
    // bool find_edge(int a, int b); 
    bool encontra_aresta(Aresta e);
    void insere_aresta(Aresta e); 
    void remove_aresta(Aresta e); 
    void imprime_grafo(); 
    bool print_graph_path(int v, int w, int marcado[], int depth);
    bool have_path(int v, int w, std::vector<int> &visited);
    bool is_connected();

private:
    int num_vertices_;
    int num_arestas_; 
    std::vector<std::vector<int>> lista_adj_; 
};

#endif