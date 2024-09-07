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
    int v, o , x, y, n;
    char opt; 
    cin >> v >> o; 

    Grafo grafo(v);
    vector<int> vertices_subgrafo_induzido(v, 0); 

    for (int i = 0; i < o; i++) {
        
        cin >> opt;
        switch (opt) {
        
        // insere aresta 
        case 'I':
            cin >> x >> y;
            grafo.insere_aresta(Aresta(x, y));
            break;
        
        case 'R':
            cin >> x >> y;
            grafo.remove_aresta(Aresta(x, y)); 

            break;
        

        // imprime numero de arestas
        case 'E':
            cout << grafo.num_arestas() << endl; 

            break;
        

        // numero de arestas do subgrafo induzido 
        case 'S':

            cin >> n; // numero de vertices do grafo induzido

            for (int j = 0; j < v; j++) {
                vertices_subgrafo_induzido[j] = 0; 
            }

            for (int j = 0; j < n; j++) {
                cin >> x; 
                vertices_subgrafo_induzido[x] = 1; 
            }

            cout << grafo.num_arestas_subgrafo_induzido(vertices_subgrafo_induzido, grafo) << endl; 

            break;
        

        // imprimir complemento grafo 
        case 'X':
            grafo.imprime_complemento(); 
            break;
        

        default:
            break;
        }

    }

    return 0;
}