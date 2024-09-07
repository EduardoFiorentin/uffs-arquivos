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
    int num_arestas(); 
    bool encontra_aresta(Aresta e);
    void insere_aresta(Aresta e);
    void remove_aresta(Aresta e);
    void imprime_grafo();
    int grau_vertice(int v); 

    int num_arestas_subgrafo_induzido(std::vector<int> &vertices, Grafo &graph); 
    void imprime_complemento(); 

private: 
    int num_arestas_;
    int num_vertices_;
    std::vector<std::list<int>> lista_adj_;
};

#endif