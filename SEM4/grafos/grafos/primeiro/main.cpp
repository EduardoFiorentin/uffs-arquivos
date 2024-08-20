#include <iostream> 
#include "Graph.h"
using namespace std;

int main() {


    try {
        int vertices_num;
        cout << "Numero de vertices: "; 
        cin >> vertices_num;
        Graph g(vertices_num);

        cout << "Num vertices: " << g.get_vertices_num() << endl; 
        cout << "Num arestas: " << g.get_edges_num() << endl; 


        cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        g.insert_edge(Edge(3, 2));
        g.insert_edge(Edge(3, 4));
    
        cout << "Num vertices: " << g.get_vertices_num() << endl; 
        cout << "Num arestas: " << g.get_edges_num() << endl; 
        cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        // g.remove_edge(Edge(2, 3));
        
        // cout << "Num vertices: " << g.get_vertices_num() << endl; 
        // cout << "Num arestas: " << g.get_edges_num() << endl; 
        // cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        g.print_graph();
    }
    catch(exception &err) {
        cerr << err.what() << endl;
    }

    return 0;
}