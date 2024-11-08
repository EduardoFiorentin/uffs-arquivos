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
#include "./Digrafo.h"
#include "./Aresta.h"

using namespace std;

int main() {

    
    int p, d, x, y, s;
    
    // entradas p e d
    cin >> p >> d; 

     // criar digrafo com o número de vertices informado
    Digrafo digrafo(p);

    // entradas x, y, s e construção do digrafo

    for (int i = 0; i < d; i++) {
        cin >> x >> y >> s;
        digrafo.insere_aresta(Aresta(x, y));

        if (s == 2) {
            digrafo.insere_aresta(Aresta(y, x));
        }
    }

    digrafo.encontra_componentes_fortemente_conexas(); 
    
    // imprimir digrafo

    //digrafo.imprime_digrafo();
    //digrafo.busca_prof(0);

    //digrafo.digrafo_invertido(); 

    return 0;
}
