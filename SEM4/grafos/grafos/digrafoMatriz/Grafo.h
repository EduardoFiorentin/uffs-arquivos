#ifndef GRAFO_H

#define GRAFO_H

#include "Aresta.h"
#include <vector>

class Grafo {
public:
    /** Constroi um grafo simples que possui o numero de vertices recebido por
     *  parametro e que nao possui arestas */
    Grafo(int num_vertices);

    int num_vertices();
    int num_arestas();

    /** Insere uma aresta no grafo caso a aresta ainda nao exista no grafo e
     * nao seja um laco */
    void insere_aresta(Aresta e);

    /** Remove uma aresta do grafo caso a aresta exista no grafo */
    void remove_aresta(Aresta e);

    void imprime();

    bool temAresta(Aresta e);

    void imprimirGrafoMatriz();

    int grauSaida(int vertice);

    int grauEntrada(int vertice); 

    bool caminho(int v, int w, std::vector<int> &marcado); 
    bool caminho2(int v, int w, std::vector<int> &marcado);

    bool ehFortementeConexo();
    bool ehFracamenteConexo();

    bool todos_vertices_vizitados(vector<int> &marcado);

private:
    int num_vertices_;
    int num_arestas_;
    std::vector<std::vector<int>> matriz_adj_;

    void valida_vertice(int v);
    void valida_aresta(Aresta e);
};

#endif /* GRAFO_H */
