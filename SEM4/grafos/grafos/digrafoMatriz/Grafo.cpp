#include "Grafo.h"
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

Grafo::Grafo(int num_vertices) {
    if (num_vertices <= 0) {
        throw(invalid_argument("Erro no construtor Grafo(int): o numero de "
            "vertices " + to_string(num_vertices) + " eh invalido!"));
    }

    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    matriz_adj_.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++) { // ou i < matriz_adj_.size()
        matriz_adj_[i].resize(num_vertices, 0);
    }
}

int Grafo::num_vertices() {
    return num_vertices_;
}

int Grafo::num_arestas() {
    return num_arestas_;
}

void Grafo::insere_aresta(Aresta e) {
    try {
        valida_aresta(e);
    } catch (...) {
        throw_with_nested(runtime_error("Erro na operacao "
            "insere_aresta(Aresta): a aresta " + e.to_string() + " eh "
            "invalida!"));
    }

    if ((matriz_adj_[e.v1][e.v2] == 0) && (e.v1 != e.v2)) {
        matriz_adj_[e.v1][e.v2] = e.peso;
        
        num_arestas_++;
    }
}

void Grafo::remove_aresta(Aresta e) {
    try {
        valida_aresta(e);
    } catch (...) {
        throw_with_nested(runtime_error("Erro na operacao "
            "remove_aresta(Aresta): a aresta " + e.to_string() + " eh "
            "invalida!"));
    }

    if (matriz_adj_[e.v1][e.v2] != 0) {
        matriz_adj_[e.v1][e.v2] = 0;
       
        num_arestas_--;
    }
}

void Grafo::imprime() {
    for (int v = 0; v < num_vertices_; v++) { // ou v < matriz_adj_.size()
        cout << v << ":";
        for (int u = 0; u < num_vertices_; u++) { // ou u < matriz_adj_.size()
            if (matriz_adj_[v][u] != 0) {
                cout << " " << u;
            }
        }
        cout << "\n";
    }
}


bool Grafo::temAresta(Aresta e){

    if (matriz_adj_[e.v1][e.v2] != 0){
        return true;
    }

    return false;

}

int Grafo::grauSaida(int vertice) {
    int grau = 0;

    for (int i = 0; i < num_vertices_; i++) {
        if (matriz_adj_[vertice][i] != 0) {
            grau++;
        }
    }
    return grau;
}
int Grafo::grauEntrada(int vertice) {
    int grau = 0;

    for (int i = 0; i < num_vertices_; i++) {
        if (matriz_adj_[i][vertice] != 0) {
            grau++;
        }
    }
    return grau;
}

bool Grafo::caminho(int v, int w, vector<int> &marcado) {
    if (v == w) {
    //printf("%d-", v);
    return true;
}
marcado[v] = 1;
for (int u = 0; u < num_vertices_; u++)
    if (matriz_adj_[v][u] != 0)
        if (marcado[u] == 0)
            if (caminho(u, w, marcado)) {
                return true;
}
return false;
}



void Grafo::imprimirGrafoMatriz(){
    
    for (int i = 0; i < num_vertices_; i++) {
        
        for (int j = 0; j < num_vertices_; j++) {
            cout << matriz_adj_[i][j] << " ";
            }
        cout << "\n";
        }       
    }   

bool Grafo::ehFortementeConexo() {
    
    vector<int> marcado(num_vertices_);

    for (int i = 0; i < (num_vertices_ - 1); i++) {
        for (int j = 0; j < num_vertices_; j++) {
            
            // Reseta os valores do vetor marcado
            for (int k = 0; k < num_vertices_; k++) {
                marcado[k] = 0;
            }

            if (!caminho(i, j, marcado)) {
                return false;
            }

        }
    }

    return true;
}  

bool Grafo::caminho2(int v, int w, vector<int> &marcado) {
    if (v == w) {
    //printf("%d-", v);
    return true;
}
marcado[v] = 1;
for (int u = 0; u < num_vertices_; u++)
    if (matriz_adj_[v][u] != 0 || matriz_adj_[u][v] != 0)
        if (marcado[u] == 0)
            if (caminho2(u, w, marcado)) {
                //printf("%d-", v);
                return true;
}
return false;
}

bool Grafo::ehFracamenteConexo() {
    vector<int> marcado(num_vertices_);

    for (int i = 0; i < (num_vertices_ - 1); i++) {
        for (int j = 0; j < num_vertices_; j++) {
            
            // Reseta os valores do vetor marcado
            for (int k = 0; k < num_vertices_; k++) {
                marcado[k] = 0;
            }

            if (!caminho2(i, j, marcado)) {
                return false;
            }

        }
    }

    return true;
}





bool Grafo::todos_vertices_vizitados(vector<int> &marcado) {
    for (int vert: marcado) {
        if (!vert) return false;
    }
    return true;
}






void Grafo::valida_vertice(int v) {
    if ((v < 0) || (v >= num_vertices_)) {
        throw out_of_range("Indice de vertice invalido: " + to_string(v));
    }
}

void Grafo::valida_aresta(Aresta e) {
    valida_vertice(e.v1);
    valida_vertice(e.v2);
}
