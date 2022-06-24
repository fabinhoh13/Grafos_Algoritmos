#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include <iostream>
#include <string>
// Incluir alguma STL, seja lista ou vector
#include <vector>
#include <list>
#include <algorithm>
#include <limits.h>

using namespace std;

class Vertice {
    public:
        int id;
        char label;
        int parent;
        bool seen;
        int flux;

        Vertice (char label = '0', int parent = -1, bool seen = false, int flux = 0);

        ~Vertice();
        bool operator< (const Vertice& str);
        bool compare (const Vertice& one, const Vertice& two);

};


class Edge {
    public:    
        int source;
        int target;
        int flux;
        int min_flux;
        int max_flux;
        bool seen;

        Edge (int s, int t, int maxf, int minf = 0, int flux = 0, bool seen = false);
        Edge ();

        ~Edge ();

};

class Adj {
    public:
        int target;
        int flux;
        int min_flux;
        int max_flux;
        bool seen;
        bool reverse;
        bool full;
        bool hasReverse;

        Adj(int target, int maxf, int minf = 0, int flux = 0, bool seen = false, bool reverse = false, bool full = false, bool hasReverse = false);
        ~Adj();
};


class Graph {
    public:    
        int vertices;
        int edges;

        vector <Vertice> v_vertices;

        vector <Edge> v_edges;

        // Lista de Adjacências
        vector <vector <Adj>> adj_list;

        Graph ();
        Graph (int v, int e);

        ~Graph ();

        void printAdj ();
        void print1Adj (int index);
        void printV ();
        void printEdgeSeen ();

        void setEdgeSeen (int source, int target);
        bool getEdgeSeen (int source, int target);

        void createReverseEdge (int source, int target);
        void UpdateReverseEdge (int source, int target, int flux);
        void UpdateDirectEdge (int source, int target, int flux);
};

void setEdgeSeen (Graph *G, int source, int target);
bool DFS (Graph *G, int initial_v, int final_v);
void FordFulkerson (Graph *G, int fst, int lst);


#endif