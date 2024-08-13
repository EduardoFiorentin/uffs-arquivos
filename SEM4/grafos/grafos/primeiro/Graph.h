#ifndef GRAPH_H
#define GRAPH_H
#include <vector>

class Graph {
public:
    Graph(int num_vertices);

    int get_vertices_num();
    int get_edges_num(); 
    bool find_edge(int a, int b); 
    void insert_edge(int a, int b); 
    void remove_edge(int a, int b); 
    void print_graph(); 

private:
    int num_vertices_;
    int num_edges_; 
    std::vector<std::vector<int>> adjacency_matrix_; 
};

#endif