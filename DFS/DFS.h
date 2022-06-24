#ifndef DFS_H
#define DFS_H

#include <iostream>
#include <string>
// Incluir alguma STL, seja lista ou vector
#include <vector>
#include <algorithm>

using namespace std;


class Edge {
    public:    
        int source;
        int target;
        int weight;
        bool seen;

        Edge (int s, int t, int w, bool seen = false);
        Edge ();

        ~Edge ();

};


class Graph {
    public:    
        int vertices;
        int edges;
        bool directed;

        vector <bool> v_vertices;

        vector <Edge> v_edges;

        // Lista de Adjacências
        vector <vector <int>> adj_list;

        Graph ();
        Graph (int v, int e, bool d);

        ~Graph ();

        void printAdj ();
        void print1Adj (int index);
        void printV ();

        void setEdgeSeen (int source, int target);
        bool getEdgeSeen (int source, int target);

};

void DFS (Graph *G, int initial_v);


#endif