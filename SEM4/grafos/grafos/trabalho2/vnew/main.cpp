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
    vector<int> marcado(p);
    vector<int> finalizacao(p);
    int tempo = 0;
   

    // entradas x, y, s e construção do digrafo

    for (int i = 0; i < d; i++) {
        cin >> x >> y >> s;
        digrafo.insere_aresta(Aresta(x, y));

        if (s == 2) {
            digrafo.insere_aresta(Aresta(y, x));
        }
    }

    
    // imprime as saídas (componentes: grau de saída da componente)
    // digrafo.grau_saida_compFortConex(digrafo.compFortConex());
    digrafo.numero_conexoes(digrafo.encontra_componentes_fort_con());

    

    return 0;
}
