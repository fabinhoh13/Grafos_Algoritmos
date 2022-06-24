#include "fordfulkerson.h"

int main () {
    int n_vertices, n_edges;

    cin >> n_vertices >> n_edges;
    
    Graph G (n_vertices, n_edges);
    //G.printAdj();
    //G.printV ();

    //DFS (&G, initial_vertice);
    //G.printAdj();
    FordFulkerson (&G, 1, n_vertices);
    //G.printAdj();

    return 0;
}