/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Daniele Rohr
 * Matricula: 2121101060
 * 
 * Nome:      Eduardo Fiorentin
 * Matricula: 2211100002
 */

#include <iostream>
#include <vector>
#include <list> 
#include "./Aresta.h"

#ifndef DIGRAFO_H
#define DIGRAFO_H

class Digrafo {

public:
    Digrafo(int num_vertices);
    int num_vertices();
    int num_arestas(); 
    bool encontra_aresta(Aresta e);
    void insere_aresta(Aresta e);
    void remove_aresta(Aresta e);
    void imprime_digrafo();    
    void busca_prof(int v, std::vector<int> &marcado, std::vector<int> &finalizacao, int &tempo);
    void busca_prof_st(int v, std::vector<int> &marcado);
    Digrafo digrafo_transposto();
    std::vector<std::vector<int>> encontra_componentes_fort_con();
    void numero_conexoes(std::vector<std::vector<int>> componentes);

    

private: 
    int num_arestas_;
    int num_vertices_;
    std::vector<std::list<int>> lista_adj_;

};

#endif /* DIGRAFO_H */
