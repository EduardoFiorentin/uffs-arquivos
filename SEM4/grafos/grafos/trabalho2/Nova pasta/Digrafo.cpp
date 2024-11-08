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

#include "./Digrafo.h"
#include "./Aresta.h"
#include <iostream>
#include <list> 
#include <stack>

using namespace std; 

// construtor
Digrafo::Digrafo(int num_vertices) {
    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    lista_adj_.resize(num_vertices_);

};


// retorna o número de vértices
int Digrafo::num_vertices() {
    return num_vertices_; 
};

// retorna o número de arestas
int Digrafo::num_arestas() {
    return num_arestas_; 
}

// verifica se uma aresta existe no grafo
bool Digrafo::encontra_aresta(Aresta e) {
    for (auto adj : lista_adj_[e.v1]) {
        if (adj == e.v2) {
            return true;
        }
    }   
    return false; 
}

// insere aresta
void Digrafo::insere_aresta(Aresta e) {
    // antes de inserir, verifica se a aresta já existe e se a aresta passada é um laço
    if (encontra_aresta(e)) return; 
    if (e.v1 == e.v2) return; 

    // se a aresta não existir, ela é inserida nas duas listas em que deve aparecer, e o número de arestas é incrementado
    lista_adj_[e.v1].push_back(e.v2);
    num_arestas_++;

}

// imprime digrafo
void Digrafo::imprime_digrafo() {
    for (int i = 0; i < num_vertices_; i++) {
        cout << i << ": ";
        for (int j : lista_adj_[i]) {
            
            cout << "-> " << j;            
        }
        cout << "\n";
    } 
}

// busca em profundidade
void Digrafo::busca_prof(int v, vector<int> &marcado) {

    // Criacao e inicializacao do vetor marcado
    // int marcado[num_vertices_] = {0};
    stack<int> pilha;
    pilha.push(v);
    
    while (!pilha.empty()) {
        int w = pilha.top();
        pilha.pop();
        
        if (marcado[w] == 0) {
            //printf("%d\n", w);
            marcado[w] = 1;
            
            //for (int u = (num_vertices_ - 1); u >= 0; u--)               
                for (int j : lista_adj_[w]) {                
                    if (marcado[j] == 0)
                        pilha.push(j);
}
}
}
    // loop para verificar de todos os vértices foram marcados
    for (int i = 0; i < num_vertices_; i++) {
        printf("%d ", marcado[i]);
    }

}  

// criar digrafo com arestas invertidas
Digrafo Digrafo::digrafo_invertido() {

    Digrafo digrafo_inv(num_vertices_); 

    for (int i = 0; i < num_vertices_; i++) {
        for (int j : lista_adj_[i]) {
            digrafo_inv.insere_aresta(Aresta(j, i));
        }
    }

    // digrafo_inv.imprime_digrafo(); 
    return digrafo_inv;
}

// encontrar componentes fortemente conexas

// busca em profundidade com recursão
// (necessário para gerar a ordem certa no vetor ordem)
void Digrafo::bp_ordem(int v, vector<int>& marcado, vector<int>& ordem, int& indice_ordem) {
    marcado[v] = 1;
    for (int vizinho : lista_adj_[v]) {
        if (marcado[vizinho] == 0) {
            bp_ordem(vizinho, marcado, ordem, indice_ordem);
        }
    }
    ordem[indice_ordem] = v;
    indice_ordem++;
}

vector<vector<int>> Digrafo::pesquisa_comp_fortemente_conexa(vector<int>& marcado, vector<int>& ordem) {
    vector<int> visitados(num_vertices_, 0);
    int indice_ordem = 0;

    // busca em prof. no grafo original 
    for (int v = 0; v < num_vertices_; v++) {
        if (marcado[v] == 0) {
            bp_ordem(v, marcado, ordem, indice_ordem);
            cout << "Chamada idx_ordem: " << indice_ordem << endl;
        }
    }

    // pega grafo invertido 
    Digrafo grafo_invertido = digrafo_invertido();

    // busca no grafo invertido
    for (int i = 0; i < num_vertices_; i++) visitados[i] = 0; 
    
    vector<vector<int>> componentes;

    cout << "\nOrdem: "; 
    for (auto i: ordem) {
        cout << i << " "; 
    }
    cout << "\n\n";

    cout << "\nvalor final idx_orde: " << indice_ordem << endl;
    
    for (int i = indice_ordem - 1; i >= 0; i--) {
        int vertice = ordem[i];
        if (visitados[vertice] == 0) {
            vector<int> componente_atual;
            
            grafo_invertido.busca_prof(vertice, visitados);
            for (int j = 0; j < num_vertices_; j++) {
                if (visitados[j] == 1) {
                    componente_atual.push_back(j);
                    // visitados = 1 na busca em prof rodada para este componete e 2 quando foi adicionada a uma comp. conexa
                    visitados[j] = 2; 
                }
            }
            componentes.push_back(componente_atual);
        }
    }

    // Imprimir
    cout << "Componentes:\n";
    for (const auto& componente : componentes) {
        for (int vertice : componente) {
            cout << vertice << " ";
        }
        cout << "\n";
    }

    return componentes; 
}

void Digrafo::encontra_componentes_fortemente_conexas() {
    vector<int> marcado(num_vertices_, 0);
    vector<int> ordem(num_vertices_);

    vector<vector<int>> componentes = pesquisa_comp_fortemente_conexa(marcado, ordem);
}

// grau de saída de cada componente fortemente conexa

