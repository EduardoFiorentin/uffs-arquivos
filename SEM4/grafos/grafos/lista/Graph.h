#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list> 
#include "./Edge.h"

class Graph {

public:
    Graph(int num_vertices);
    int get_num_vertices();
    int get_num_edges(); 
    bool find_edge(Edge e);
    void insert_edge(Edge e);
    void remove_edge(Edge e);
    void print_graph();

private: 
    int num_edges_;
    int num_vertices_;
    std::vector<std::list<int>> adjacency_matrix_;
};

#endif