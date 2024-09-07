#include <iostream> 
#include "./Graph.h"
#include "./Edge.h"

using namespace std;

int main() {

    try {
        int vertices_num = 6;
        // cout << "Numero de vertices: "; 
        // cin >> vertices_num;
        Grafo g(vertices_num);

        // cout << "Num vertices: " << g.get_num_vertices() << endl; 
        // cout << "Num arestas: " << g.get_num_edges() << endl; 


        // cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        // g.insert_edge(Edge(3, 2));
        // g.insert_edge(Edge(2, 3));  // repetida 
        // g.insert_edge(Edge(2, 4));
        // g.insert_edge(Edge(2, 5));
        // g.insert_edge(Edge(2, 6));

        // cout << "Num vertices: " << g.get_num_vertices() << endl; 
        // cout << "Num arestas: " << g.get_num_edges() << endl; 
        // cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        // g.print_graph();

        // cout << "O grau do vertice 2 eh: " << g.vertice_deg(2) << endl; 
        
        // g.remove_edge(Edge(2, 3));
        
        // cout << "Num vertices: " << g.get_num_vertices() << endl; 
        // cout << "Num arestas: " << g.get_num_edges() << endl; 
        // cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        // g.print_graph();
        // cout << "O grau do vertice 2 eh: " << g.vertice_deg(2) << endl; 


        g.insere_aresta(Aresta(0, 1));
        g.insere_aresta(Aresta(0, 2));  // repetida 
        g.insere_aresta(Aresta(0, 5));
        g.insere_aresta(Aresta(5, 2));
        g.insere_aresta(Aresta(5, 3));
        g.insere_aresta(Aresta(2, 3));
        g.insere_aresta(Aresta(2, 4));
        g.insere_aresta(Aresta(3, 4));

        g.imprime_grafo();

    }
    catch(exception &err) {
        cerr << err.what() << endl;
    }

    return 0;
}