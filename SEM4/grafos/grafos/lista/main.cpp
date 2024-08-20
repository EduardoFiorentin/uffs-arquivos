#include <iostream> 
#include "./Graph.h"
#include "./Edge.h"

using namespace std;

int main() {

    try {
        int vertices_num = 6;
        // cout << "Numero de vertices: "; 
        // cin >> vertices_num;
        Graph g(vertices_num);

        cout << "Num vertices: " << g.get_num_vertices() << endl; 
        cout << "Num arestas: " << g.get_num_edges() << endl; 


        cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        g.insert_edge(Edge(3, 2));
        g.insert_edge(Edge(2, 3));  // repetida 
        g.insert_edge(Edge(2, 4));

        cout << "Num vertices: " << g.get_num_vertices() << endl; 
        cout << "Num arestas: " << g.get_num_edges() << endl; 
        cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        g.print_graph();
        
        g.remove_edge(Edge(2, 3));
        
        cout << "Num vertices: " << g.get_num_vertices() << endl; 
        cout << "Num arestas: " << g.get_num_edges() << endl; 
        cout << "Tem aresta (2, 3): " << (g.find_edge(Edge(2, 3)) ? "Sim" : "Nao") << endl; 

        g.print_graph();
    }
    catch(exception &err) {
        cerr << err.what() << endl;
    }

    return 0;
}