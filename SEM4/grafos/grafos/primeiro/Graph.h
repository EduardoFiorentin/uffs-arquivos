#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Edge.h"

class Graph {
public:
    Graph(int num_vertices);

    int get_vertices_num();
    int get_edges_num(); 
    // bool find_edge(int a, int b); 
    bool find_edge(Edge e);
    void insert_edge(Edge e); 
    void remove_edge(Edge e); 
    void print_graph(); 
    bool print_graph_path(int v, int w, int marcado[], int depth);
    bool have_path(int v, int w, vector<int> &visited);
    bool is_connected();

private:
    int num_vertices_;
    int num_edges_; 
    std::vector<std::vector<int>> adjacency_list_; 
};

#endif