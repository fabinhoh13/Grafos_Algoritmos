#include "Kahn.h"

Vertice :: Vertice (int id, int tbt):
    id (id), timesBeingTarget (tbt) {}

Vertice :: ~Vertice () {}

Edge :: Edge () {}

Edge :: Edge (int s, int t, bool marked): 
    source(s), target (t), marked (marked) {}

Edge :: ~Edge () {}



Graph :: Graph () {}

// Inicializador do meu grafo
Graph :: Graph (int v, int e):
    vertices (v), edges (e) {
    //-------------------------------------

     
    for (int i = 0; i <= v; i++) {
        //Primeiro eu completo todo o meu vector onde estarão guardados os valores de visitação
        // de cada vértice separadamente
        Vertice aux (i, 0);
        v_vertices.push_back(aux);
        vector <int> aux1;
        // Depois inicializo o meu vector de vector que será a minha lista de adjacência
        adj_list.push_back (aux1);
    }
    int source, target;
    for (int i = 0; i < e; i++) {
        // Faço a leitura dos dados de cada aresta
        cin >> source >> target;
        // Insiro os dados dentro do vector de arestas
        Edge e_aux (source, target);
        // tenho um contador que conta quantos arcos de entrada tem um determinado vertice
        // Caso haja, eu somo o meu contador com +1
        v_vertices[target].timesBeingTarget++;
        v_edges.push_back (e_aux);
        // E começo a montar minha lista de adjacência
        // Primeiramente, eu coloco os dados normalmente dentro da lista
        adj_list.at(source).push_back(target);
    }   
}

Graph :: ~Graph() {}

// Função que printa toda a lista de adjacência
void Graph :: printAdj () {
    for (int i = 1; i <= vertices; i++){
        cout << i << ": ";
        for (auto j : adj_list[i]){
            cout << j << " ";
        }
        cout << endl;
    }

    cout << endl;
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
    for (auto i : this->v_vertices) {
        cout << "Vertice " << i.id << ": " << i.timesBeingTarget << endl;
    }
}

bool Graph :: VerticesWithoutSources (int index) {
    bool flag;
    for (auto i : v_edges) {
        if (i.target != index){
            flag = true;
        }
        else return false;
    }
    return flag;
}

bool Graph :: allMarked () {
    bool flag;
    for (auto i : v_edges) {
        if (i.marked == true){
            flag = true;
        }
        else return false;
    }
    return flag;
}

void Graph :: excludeArch (int index) {
    v_vertices[index].timesBeingTarget--;
}

bool VerticesWithoutSources (vector <Edge> edges, int index){
    bool flag;
    for (auto i : edges) {
        if (i.target != index){
            flag = true;
        }
        else return false;
    }
    return flag;
}

vector <int> Kahn (Graph *G) {
    // Vector onde serão guardados os elementos da ordenação
    vector <int> L;
    // Lista onde serão guardados os vértices sem arcos de entrada
    list <int> S;

    // Faço o teste para cada vértice a partir do meu contador.
    // Se houver algum contador zerado, significa que o
    // vertice i não tem nenhum arco de entrada
    for (int i = 1; i < G->v_vertices.size(); i++){
        if (G->v_vertices[i].timesBeingTarget == 0){
            S.push_back (i);
        }
    }
    //G->printV();
    int v;

    // Agora, indo pra parte principal do algorítmo
    // Enquanto a minha lista de vertices sem arcos de entrada tiver elementos
    while (!S.empty()){
        // Eu retiro o primeiro vertice desta lista
        v = S.front();
        S.pop_front();
        // E insiro no meu Vector que contem os elementos da ordenação
        L.push_back(v);

        // Agora, para cada arco de v para w na minha lista de adjancências
        for (auto w : G->adj_list[v]){
            
            // diminuo meu contador de arcos de entrada dentro do meu vector de vertices
            //cout << w << endl;
            G->excludeArch(w);
            
            // E se caso não houver mais arcos de entrada de v para w
            if ( G->v_vertices[w].timesBeingTarget == 0){
                // Coloco o vértice w na lista dos conjuntos sem arcos de entrada
                S.push_back (w);
            }
        }
    }

    // Logo após o término da ordenação, preciso verificar se o vértice é cíclico
    // Para isso, caso houver algum arco que não foi zerado, significa que
    // meu grafo é cíclico
    //G->printV();
    for (auto i : G->v_vertices){
        if (i.timesBeingTarget != 0){
            // Dessa forma, retorno para o programa principal um Vector vazio
            vector <int> empty_vector;
            return empty_vector;
        }
    }

    // Caso contrário, retorno ao programa principal meu Vector contendo a ordenação
    // topológica completa
    return L;
    
}

