#include <iostream> 
#include "Graph.h"
using namespace std;

int main() {


    try {
        int num_vertices;
        cin >> num_vertices;
        Graph g(num_vertices);

    }
    catch(exception &err) {
        cerr << err.what() << endl;
    }

    return 0;
}