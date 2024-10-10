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

#include <iostream> 
#include "./Grafo.h"
#include "./Aresta.h"

using namespace std;

int main() {
    // int v, o , x, y, n;
    // char opt; 
    // cin >> v >> o; 

    // Grafo grafo(v);
    // vector<int> vertices_subgrafo_induzido(v, 0); 

    // for (int i = 0; i < o; i++) {
        
    //     cin >> opt;
    //     switch (opt) {
        
    //     // insere aresta 
    //     case 'I':
    //         cin >> x >> y;
    //         grafo.insere_aresta(Aresta(x, y));
    //         break;
        
    //     case 'R':
    //         cin >> x >> y;
    //         grafo.remove_aresta(Aresta(x, y)); 

    //         break;
        

    //     // imprime numero de arestas
    //     case 'E':
    //         cout << grafo.num_arestas() << endl; 

    //         break;
        

    //     // numero de arestas do subgrafo induzido 
    //     case 'S':

    //         cin >> n; // numero de vertices do grafo induzido

    //         for (int j = 0; j < v; j++) {
    //             vertices_subgrafo_induzido[j] = 0; 
    //         }

    //         for (int j = 0; j < n; j++) {
    //             cin >> x; 
    //             vertices_subgrafo_induzido[x] = 1; 
    //         }

    //         cout << grafo.num_arestas_subgrafo_induzido(vertices_subgrafo_induzido, grafo) << endl; 

    //         break;
        

    //     // imprimir complemento grafo 
    //     case 'X':
    //         grafo.imprime_complemento(); 
    //         break;
        

    //     default:
    //         break;
    //     }

    // }

    Grafo grafo(5); 

    grafo.insere_aresta({0, 1, 10});
    grafo.insere_aresta({0, 3, 5});
    
    grafo.insere_aresta({1, 2, 1});
    grafo.insere_aresta({1, 3, 2});

    grafo.insere_aresta({2, 4, 4});

    grafo.insere_aresta({3, 1, 3});
    grafo.insere_aresta({3, 2, 9});
    grafo.insere_aresta({3, 4, 2});
   
    grafo.insere_aresta({4, 0, 7});
    grafo.insere_aresta({4, 2, 6});
   
    grafo.imprime_grafo(); 

    vector<int> pai(grafo.get_num_vertices());
    vector<int> dp(grafo.get_num_vertices());

    grafo.dijkstra(0, pai, dp);

    cout << "\nVetor pai: ";
    for (auto elem: pai) {
        cout << elem << " ";
    }
    
    cout << "\nVetor dp: ";
    for (auto elem: dp) {
        cout << elem << " ";
    }




    return 0;
}