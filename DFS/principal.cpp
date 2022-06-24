#include "DFS.h"

int main () {
    int n_vertices, n_edges, directed, initial_vertice;

    cin >> n_vertices >> n_edges >> directed>> initial_vertice;

    bool d;
    if (directed == 1)
        d = true;
    else
        d = false;
    
    Graph G (n_vertices, n_edges, d);
    //G.printAdj();
    //G.printV ();

    DFS (&G, initial_vertice);

    return 0;
}