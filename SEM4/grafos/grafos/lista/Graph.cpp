#include "./Graph.h"
#include "./Edge.h"
#include <iostream>


Graph::Graph(int num_vertices) {
    num_vertices_ = num_vertices;
    num_edges_ = 0;

    adjacency_matrix_.resize(num_vertices_);

};

int Graph::get_num_vertices() {
    return num_vertices_; 
};

int Graph::get_num_edges() {
    return num_edges_; 
}

bool Graph::find_edge(Edge e) {
    bool ad1, ad2 = false; 

    for (int adj : adjacency_matrix_[e.v1]) {
        if (adj == e.v2) {
            return true;
        }
    }
    for (int adj : adjacency_matrix_[e.v2]) {
        if (adj == e.v1) {
            return true;
        }
    }

    return (ad1 && ad2); 
}; 

void Graph::insert_edge(Edge e) {

    if (find_edge(e)) return; 

    adjacency_matrix_[e.v1].push_back(e.v2);
    adjacency_matrix_[e.v2].push_back(e.v1);
    num_edges_++;

}

void Graph::remove_edge(Edge e) {

    if (!find_edge(e)) return; 

    adjacency_matrix_[e.v1].remove(e.v2);
    adjacency_matrix_[e.v2].remove(e.v1);

    num_edges_--; 

}

void Graph::print_graph() {

    std::cout << "Vizinhos:"; 
    int i = 0; 
    for (auto vert: adjacency_matrix_) {
        std::cout << "\n" << i << ":"; 
        
        for (int arst: vert) {
            std::cout << " " << arst; 
        }

        i++;
    }
    std::cout << std::endl; 

}

int Graph::vertice_deg(int v) {
    if (v < 0 || v >= num_vertices_) return -1; 

    int deg = 0; 
    for (int edge: adjacency_matrix_[v]) {
        if ( edge != 0 ) deg++;
    }

    return deg; 
}; 
