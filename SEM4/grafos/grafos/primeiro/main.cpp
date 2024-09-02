#include <iostream> 
#include "Graph.h"
using namespace std;

int main() {


    try {
        // int vertices_num;
        // cout << "Numero de vertices: "; 
        // cin >> vertices_num;
        Graph g(3);

        // cout << "Num vertices: " << g.get_vertices_num() << endl; 
        // cout << "Num arestas: " << g.get_edges_num() << endl; 


        // cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        // g.insert_edge(Edge(3, 2));
        // g.insert_edge(Edge(3, 4));
    
        // cout << "Num vertices: " << g.get_vertices_num() << endl; 
        // cout << "Num arestas: " << g.get_edges_num() << endl; 
        // cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        // g.remove_edge(Edge(2, 3));
        
        // cout << "Num vertices: " << g.get_vertices_num() << endl; 
        // cout << "Num arestas: " << g.get_edges_num() << endl; 
        // cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        // g.insert_edge(Edge(0, 1));  
        // g.insert_edge(Edge(0, 2));  // repetida 
        // g.insert_edge(Edge(0, 5));
        // g.insert_edge(Edge(5, 2));
        // g.insert_edge(Edge(5, 3));
        // g.insert_edge(Edge(2, 3));
        // g.insert_edge(Edge(2, 4));
        // g.insert_edge(Edge(3, 4));

        g.insert_edge(Edge(0, 1));
        g.insert_edge(Edge(1, 2));
        // g.insert_edge(Edge(0, 2));
        // g.print_graph();

        g.print_graph();

        vector<int> visited(8, 0);

        cout << "Conectado: " << g.is_connected() << endl;
        cout << "Caminho: " << g.have_path(0, 1, visited) << endl;

        // int marcado[6] = {0, 0, 0, 0, 0, 0}; 
        // g.print_graph_path(0, 4, marcado, 0);

        cout << "fim" << endl; 
    }
    catch(exception &err) {
        cerr << err.what() << endl;
    }

    return 0;
}