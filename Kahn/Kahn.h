#ifndef KAHN_H
#define KAHN_H

#include <iostream>
#include <string>
// Incluir alguma STL, seja lista ou vector
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;

class Vertice {
    
    public:
        int id;
        int timesBeingTarget;

        Vertice (int id, int tbt);
        ~Vertice();
};


class Edge {
    public:    
        int source;
        int target;
        bool marked;

        Edge (int s, int t, bool marked = false);
        Edge ();

        ~Edge ();

        

};


class Graph {
    public:    
        int vertices;
        int edges;
        bool directed;

        vector <Vertice> v_vertices;

        vector <Edge> v_edges;

        // Lista de Adjacências
        vector <vector <int>> adj_list;

        Graph ();
        Graph (int v, int e);

        ~Graph ();

        void printAdj ();
        void print1Adj (int index);
        void printV ();
        bool VerticesWithoutSources (int index);
        bool allMarked ();

        void excludeArch (int index);

        void setEdgeSeen (int source, int target);
        bool getEdgeSeen (int source, int target);

};

bool VerticesWithoutSources (int index);


vector <int> Kahn (Graph *G);


#endif