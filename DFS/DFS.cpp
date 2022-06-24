#include "DFS.h"

Edge :: Edge () {}

Edge :: Edge (int s, int t, int w, bool seen): 
    source(s), target (t), weight (w), seen (seen) {}

Edge :: ~Edge () {}


Graph :: Graph () {}

// Inicializador do meu grafo
Graph :: Graph (int v, int e, bool d):
    vertices (v), edges (e), directed (d) {
    //-------------------------------------

     
    for (int i = 0; i < v; i++) {
        //Primeiro eu completo todo o meu vector onde estarão guardados os valores de visitação
        // de cada vértice separadamente
        v_vertices.push_back(false);
        vector <int> aux1;
        // Depois inicializo o meu vector de vector que será a minha lista de adjacência
        adj_list.push_back (aux1);
    }
    int source, target, weigth;
    for (int i = 0; i < e; i++) {
        // Faço a leitura dos dados de cada aresta
        cin >> source >> target >> weigth;
        // Insiro os dados dentro do vector de arestas
        Edge e_aux (source, target, weigth);
        v_edges.push_back (e_aux);
        // E começo a montar minha lista de adjacência
        // Primeiramente, eu coloco os dados normalmente dentro da lista
        adj_list.at(source - 1).push_back(target);
        if (!d) {
            // Caso o grafo seja não direcionado, faço com que a lista seja tratada tanto na ida
            // da aresta quanto na volta
            adj_list.at(target - 1).push_back (source);
        }
    }   
}

Graph :: ~Graph() {}

// Função que printa toda a lista de adjacência
void Graph :: printAdj () {
    int cont = 1;
    for (auto i : this->adj_list){
        cout << cont << ": ";
        for (auto j : i){
            cout << j << " ";
        }
        cout << endl;
        cont++;
    }

    cout << endl << endl;
}

// Função que printa uma linha da lista de adjacência
void Graph :: print1Adj (int index) {
    cout << "Vertice " << index + 1 << ": ";
    for (auto i : this->adj_list[index]){
        cout << i << " ";
    }
    cout << endl << endl;
}

// Função que printa todos os valores da lista com os vértices
void Graph :: printV () {
    int cont = 1;
    for (auto i : this->v_vertices) {
        cout << "Vertice " << cont;
        if (i == true)
            cout << ": True" << endl;
        else
            cout << ": False" << endl;
        
        cont++;
    }
}

// Função que coloca como visitado uma determinada aresta
void Graph :: setEdgeSeen (int source, int target) {
    for (auto i : this->v_edges) {
        if (i.source == source && i.target == target) {
            i.seen = true;
            if (!this->directed) {
                for (auto j : this->v_edges) {
                    if (j.source == target && j.target == source) {
                        j.seen = true;
                    }
                }
            }
        }   
    }
}

// Função que retorna o estado de determinada aresta
bool Graph :: getEdgeSeen (int source, int target) {
    bool aux;
    for (auto i : this->v_edges) {
        if (i.source == source && i.target == target)
            aux = i.seen;
    }
    return aux;
}


void DFS (Graph *G, int initial_v) {
    // Coloco o vértice inicial como true
    G->v_vertices[initial_v] = true;
    // Faço o print do vertice inicial, mostrando ao final a ordem de visitação dos vértices
    cout << initial_v << endl;
    // Dentro da minha lista de adjacência, vou trabalhar somente com a lista do vertice "initial_v"
    // Dessa forma, usarei somente o vector dele, dentro do meu vector de vectors
    int n_vertices = G->adj_list[initial_v - 1].size();
    for (int i = 0; i < n_vertices; i++) {
        // Aqui eu somente estou guardando o indice do vértice para usar de forma mais clara depois
        int v_index = G->adj_list[initial_v - 1][i];
        // Caso o vértice não tenha sido visitado
        if (G->v_vertices[v_index] == false){
            // Faço com que a aresta entre o vertice inicial e o vértice vizinho seja marcado como 
            // visitado
            G->setEdgeSeen (initial_v, i);
            // E faço a chamada recursiva, passando agora o vértice vizinho como vértice inicial
            DFS (G, v_index);
        }
        else {
            // Caso contrário, faço com que, caso a aresta entre o vértice inicial e o vertice vizinho
            // seja marcado como visitado
            if (G->getEdgeSeen(initial_v, i) == false){
                G->setEdgeSeen(initial_v, i);
            }
        }
    }
}


/* Pseudo Código do DFS

void DFS (Grafo, Vertice_Inicial){
    Grafo(Vertice_Inicial)->visitado = true
    while (existir vizinho de Vertice_inicial) {
        if (vizinho != visitado) {
            vizinho.visitado = true
            DFS (Grafo, vizinho)
        }
        else {
            if (aresta entre vizinho e Vertice_inicial != visitado){
                aresta->visitado = true
            }
        }
    }
}

Criando a Lista de adjacencias???

lista Cria_Lista (numero_arestas, numero_vertices, direcionado) {
    for (i = 0; i < vertices; i++) {
        vertice.push_back(false);
        vector <int> aux;
        adj_list.push_back (aux)
    }

    for (i = 0; i < edges; i++) {
        adj_list.at(source - 1).push_back(target);
        if (direcionado) {
            adj_list.at(target - 1).push_back (source);
        }
    }
}

*/