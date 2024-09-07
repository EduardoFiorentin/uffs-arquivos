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
#include "./Graph.h"
#include "./Edge.h"

using namespace std;

int main() {
    int v, o , x, y, n;
    char opt; 
    cin >> v >> o; 

    Grafo graph(v);
    vector<int> induced_subg_vertices(v, 0); 

    for (int i = 0; i < o; i++) {
        
        cin >> opt;
        switch (opt) {
        
        // insere aresta 
        case 'I':
            cin >> x >> y;
            graph.insere_aresta(Aresta(x, y));
            break;
        
        case 'R':
            cin >> x >> y;
            graph.remove_aresta(Aresta(x, y)); 

            break;
        

        // imprime numero de arestas
        case 'E':
            cout << graph.num_arestas() << endl; 

            break;
        

        // numero de arestas do subgrafo induzido 
        case 'S':

            cin >> n; // numero de vertices do grafo induzido

            for (int j = 0; j < v; j++) {
                induced_subg_vertices[j] = 0; 
            }

            for (int j = 0; j < n; j++) {
                cin >> x; 
                induced_subg_vertices[x] = 1; 
            }

            cout << graph.num_arestas_subgrafo_induzido(induced_subg_vertices, graph) << endl; 

            break;
        

        // imprimir complemento grafo 
        case 'X':
            graph.imprime_complemento(); 
            break;
        

        default:
            break;
        }

    }

    return 0;
}