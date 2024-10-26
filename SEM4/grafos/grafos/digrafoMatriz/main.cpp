#include "Aresta.h"
#include "Grafo.h"
#include <exception>
#include <string>
#include <iostream>

using namespace std;

void print_exception(const exception &e, int level = 0) {
    cerr << "exception: " << string(level, ' ') << e.what() << "\n";
    try {
        rethrow_if_nested(e);
    } catch(const std::exception& nested_exception) {
        print_exception(nested_exception, (level + 2));
    }
}

int main() {
    try {
        // Grafo g(4);

        // Aresta a(0, 2, 5);
        // Aresta b(0, 3, 4);
        // Aresta c(1, 3, 3);
        // Aresta d(3, 1, 1);

        // g.insere_aresta(a);
        // g.insere_aresta(b);
        // g.insere_aresta(c);
        // g.insere_aresta(d);
        

        // g.imprime();

        // cout << g.temAresta(a) << "\n";
        // cout << g.temAresta(Aresta(0, 3, 0)) << "\n";

        // g.imprimirGrafoMatriz();

        // cout << "Grau de saída do vértice 0: " << g.grauSaida(0) << "\n";
        // cout << "Grau de entrada do vértice 3: " << g.grauEntrada(3) << "\n";

        
        // vector<int> marcado(4); 

        // cout << g.caminho(1, 0, marcado)<< "\n";
        // cout << g.ehFortementeConexo() << "\n";
        // cout << g.ehFracamenteConexo() << "\n";
    
        int P, D, X, Y, S; 

        cin >> P >> D; 
        Grafo grafo(P);
    
        for (int i = 0; i < D; i++) {

            cin >> X >> Y >> S;
    
            if (S == 1) {
                grafo.insere_aresta(Aresta(X, Y, 1));
            } 
            else {
                grafo.insere_aresta(Aresta(X, Y, 1));
                grafo.insere_aresta(Aresta(Y, X, 1));
            }

        }

        cout << "Leitura finalizada" << endl; 

        grafo.imprime();


    }


    catch (const exception &e) {
        print_exception(e);
    }

    return 0;
}
