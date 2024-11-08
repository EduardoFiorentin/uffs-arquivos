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
#include <algorithm> 

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

// Busca em profundidade com o tempo de finalização
void Digrafo::busca_prof(int v, vector<int> &marcado, vector<int> &finalizacao, int &tempo) {
    marcado[v] = 1;
    
    for (int j : lista_adj_[v]) {
        if (marcado[j] == 0) {
            busca_prof(j, marcado, finalizacao, tempo);
        }
    }

    finalizacao[tempo] = v;
    tempo +=1;
}

// Busca em profundidade sem tempo de finalização
void Digrafo::busca_prof_st(int v, vector<int> &marcado) {
    marcado[v] = 1;
    
    for (int j : lista_adj_[v]) {
        if (marcado[j] == 0) {
            busca_prof_st(j, marcado);
        }
    }
}
 

// Construção do digrafo transposto
Digrafo Digrafo::digrafo_transposto() {
    
    Digrafo digrafo_transposto(num_vertices_);

    for (int i = 0; i < num_vertices_; i++) {
        for (int j : lista_adj_[i]) {
            digrafo_transposto.insere_aresta(Aresta(j,i));
        }
    }

    return digrafo_transposto;
}

// encontrar as componentes fortemente conexas
vector<vector<int>> Digrafo::encontra_componentes_fort_con() {


    vector<int> finalizacao(num_vertices_);
    vector<int> marcado(num_vertices_, 0);
    int indice_ordem = 0;

    vector<vector<int>> comp_fort_conex;

    // busca em profundidade no grafo original
    for (int i = 0; i < num_vertices_; i++) {
        if (marcado[i] == 0) {                         
            busca_prof(i, marcado, finalizacao, indice_ordem);  
        }
    }

    cout << "Indice ordem: " << indice_ordem << endl;

    // reseta o vetor marcado para 0 para uso na próxima busca em profundidade
    for (int i = 0; i < num_vertices_; i++) marcado[i] = 0;

    // inverte as arestas do grafo (grafo transposto)
    Digrafo transposto = digrafo_transposto();   

    // realiza busca em profundidade no grafo transposto por ordem de tempo de finalização     
    for (int i = indice_ordem - 1; i >= 0; i--) {
        int vertice = finalizacao[i];
        if (marcado[vertice] == 0) {
            vector<int> componente_atual;
            
            transposto.busca_prof_st(vertice, marcado);
            for (int j = 0; j < num_vertices_; j++) {
                if (marcado[j] == 1) {
                    componente_atual.push_back(j);
                    
                    // visitados = 1 na busca em prof rodada para este componete e 2 quando foi adicionada a uma comp. conexa
                    marcado[j] = 2; 
                }
            }
            comp_fort_conex.push_back(componente_atual);
        }
        
    }

    // Imprimir
    cout << "Componentes:\n";
    for (const auto& componente : comp_fort_conex) {
        for (int vertice : componente) {
            cout << vertice << " ";
        }
        cout << "\n";
    }

    // return componentes;

    return comp_fort_conex;
}


void Digrafo::numero_conexoes(vector<vector<int>> componentes) {

    // percorre o vector das componentes conexas e verifica se existem arestas com os vértices das outras componentes
    
    for (auto comp: componentes) {
        for (int comp2: comp) {
            cout << comp2 << " ";
        }
        cout << endl;
    }

   int numero_conexoes = 0;

    // esse for percorre as componentes
    for (int i = 0; i < componentes.size(); i++) {

        numero_conexoes = 0;

        // esse for percorre os vértices do j-componente
        for (int j = 0; j < componentes.size(); j++) {
            //esse for aqui percorre os vértices da k-componente

            if (j == i) continue;

            for (int v1: componentes[i]) {
                
                for (int v2: componentes[j]) {
                    
                    if (encontra_aresta(Aresta(v1, v2))) {
                        numero_conexoes++;
                        break;
                    }
                    if (numero_conexoes > 0) break; 
                }
            }
        }           

        
        printf("%d: %d \n", i, numero_conexoes);
        numero_conexoes = 0;
    }
}


