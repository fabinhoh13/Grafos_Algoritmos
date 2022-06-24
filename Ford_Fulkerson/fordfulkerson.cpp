#include "fordfulkerson.h"

Vertice :: Vertice (char label, int parent, bool seen, int flux):
    label(label), parent(parent), seen (seen), flux (flux){}

Vertice :: ~Vertice(){}

bool Vertice :: operator< (const Vertice& str){
        return (id < str.id);
}

bool Vertice :: compare (const Vertice& one, const Vertice& two){
        return (one.id < two.id);
}


Edge :: Edge () {}

Edge :: Edge (int s, int t, int maxf, int minf, int flux, bool seen): 
    source(s), target (t), max_flux (maxf), flux(flux), min_flux (minf), seen (seen) {}

Edge :: ~Edge () {}

Adj :: Adj(int target,int maxf, int minf, int flux, bool seen, bool reverse, bool ful, bool hasReversel): 
    target (target), max_flux (maxf), flux(flux), min_flux (minf), seen (seen), reverse (reverse), full (full), hasReverse(hasReverse) {}
    
Adj :: ~Adj(){}


Graph :: Graph () {}

// Inicializador do meu grafo
Graph :: Graph (int v, int e):
    vertices (v), edges (e) {
    //-------------------------------------

     
    for (int i = 0; i < v; i++) {
        Vertice vAux('0', -1, false);
        vAux.id = i + 1;
        v_vertices.push_back(vAux);
        vector <Adj> aux1;
        adj_list.push_back (aux1);
    }
    int source, target, weigth;
    for (int i = 0; i < e; i++) {
        cin >> source >> target >> weigth;
        Edge e_aux (source, target, weigth);
        v_edges.push_back (e_aux);
        Adj adjAux (target, weigth);
        adj_list.at(source - 1).push_back(adjAux);
    }
    // Para que os caminhos encontrados estejam de acordo com o resultado esperado, eu ordeno em ordem crescente a partir do vertice
    // de destino de cada aresta
    for (int i = 0; i < v; i++){
        sort(adj_list[i].begin(), adj_list[i].end(), [](Adj & one, Adj & two){return one.target < two.target;});
    }   
}

Graph :: ~Graph() {}

// Função que printa toda a lista de adjacência
void Graph :: printAdj () {
    int cont = 1;
    for (int i = 0; i < vertices; i++){
        cout << i + 1 << ": ";
        for (auto j : adj_list[i]){
            cout << j.target << " ";
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
        cout << i.target << " ";
    }
    cout << endl << endl;
}
void Graph :: printEdgeSeen () {
    for (int i = 0; i < edges; i++){
        cout << "De " << v_edges[i].source << " para " << v_edges[i].target << ": ";
        if (v_edges[i].seen == true)
            cout << "True";
        else
            cout << "False";
        cout << endl;
    }
}


// Função que coloca como visitado uma determinada aresta
void Graph :: setEdgeSeen (int source, int target) {
    for (int i = 0; i < edges; i++) {
        if (v_edges[i].source == source && v_edges[i].target == target) {
            v_edges[i].seen = true;
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

// Função que cria arcos reversos
void Graph :: createReverseEdge (int source, int target){
    bool flag = false;
    // primeiro verifico se já existe um arco reverso
    for (auto i : adj_list[target-1]){
        if (i.target == source){
            flag = true;
            break;
        }
    }
    //cout << "Hora de colocar o arco" << endl;
    
    // caso não tenha...
    if (!flag){
        int max_flux;
        int flux;
        // ...procuro pelo arco direto...
        for (int i = 0; i < adj_list[source - 1].size(); i++){
            if (adj_list[source - 1][i].target == target){
                // ...guardo o fluxo máximo e o fluxo atual, para serem guardados no arco reverso
                max_flux = adj_list[source - 1][i].max_flux;
                flux = adj_list[source - 1][i].flux;
                // e também falo que o arco direto tem um arco reverso, que me ajudará depois
                adj_list[source - 1][i].hasReverse = true;
            }
        }
        // Depois eu adiciono o arco reverso na lista de adjacências
        Adj aux(source, max_flux);
        aux.reverse = true;
        aux.flux = flux;
        adj_list[target - 1].push_back(aux);
        // e faço uma ordenação para manter na ordem crescente
        sort(adj_list[target - 1].begin(), adj_list[target - 1].end(), [](Adj & one, Adj & two){return one.target < two.target;});  
    }
}

// Função que atualiza um arco reverso
void Graph :: UpdateReverseEdge (int source, int target, int flux) {
    // Quando eu faço alguma alteração em um arco direto, preciso mudar o valor do arco reverso, para isso
    // procuro pelo arco reverso e somo o fluxo atual nele
    for (int i = 0; i < adj_list[target - 1].size(); i++){
        if (adj_list[target - 1][i].target == source){
            adj_list[target - 1][i].flux += flux;
            // e caso o arco estivesse cheio, eu reseto a flag, para que o arco possa ser reutilizado na busca de caminho
            if (adj_list[target - 1][i].full){
                adj_list[target - 1][i].full = false;
            }
        }
    }
}

// Função que atualiza o arco direto
void Graph :: UpdateDirectEdge (int source, int target, int flux) {
    // Quando eu faço alguma alteração em um arco reverso, preciso mudar o valor do arco direto, para isso
    // procuro pelo arco direto e subtraio o fluxo atual nele
    for (int i = 0; i < adj_list[source - 1].size(); i++){
        if (adj_list[source - 1][i].target == target){
            adj_list[source - 1][i].flux -= flux;
            // e caso o arco estivesse cheio, eu reseto a flag, para que o arco possa ser reutilizado na busca de caminho
            if (adj_list[source - 1][i].full){
                adj_list[source - 1][i].full = false;
            } 
        }
        
    }
}

void setEdgeSeen (Graph *G, int source, int target) {
    for (int i = 0; i < G->edges; i++) {
        if (G->v_edges[i].source == source && G->v_edges[i].target == target) {
            G->v_edges[i].seen = true;
        }   
    }
}

// Função que busca o caminho
bool DFS (Graph *G, int initial_v, int final_v) {
    
    // Coloco o vértice inicial como true
    G->v_vertices[initial_v].seen = true;
    // Dentro da minha lista de adjacência, vou trabalhar somente com a lista do vertice "initial_v"
    // Dessa forma, usarei somente o vector dele, dentro do meu vector de vectors
    int n_vertices = G->adj_list[initial_v - 1].size();
    for (int i = 0; i < n_vertices; i++) {
        // Aqui eu somente estou guardando o indice do vértice para usar de forma mais clara depois
        int v_index = G->adj_list[initial_v - 1][i].target;
        // Caso o arco que eu estou tentando usar estiver cheio, eu não usarei
        if(G->adj_list[initial_v - 1][i].full == true){
            continue;
        }
        // Caso o vértice não tenha sido visitado
        if (G->v_vertices[v_index].seen == false){
            // Faço com que a aresta entre o vertice inicial e o vértice vizinho seja marcado como 
            // visitado
            G->adj_list[initial_v - 1][i].seen = true;
            // Guardo qual é o pai do proximo vertice
            G->v_vertices[v_index - 1].parent = initial_v;
            // E faço a chamada recursiva, passando agora o vértice vizinho como vértice inicial
            DFS (G, v_index, final_v);
        }
        else {
            // Caso contrário, faço com que, caso a aresta entre o vértice inicial e o vertice vizinho
            // seja marcado como visitado
            if (G->adj_list[initial_v - 1][i].seen == false){
                G->adj_list[initial_v - 1][i].seen = true;
            }
        }
    }
    // E retorno se o ultimo vertice foi visitado
    return G->v_vertices[final_v - 1].seen;
}

// Função que procura o fluxo máximo de um grafo
void FordFulkerson (Graph *G, int fst, int lst){
    // lista que guarda o caminho de determinada iteração
    list <Vertice *> path;
    // o meu source terá como fluxo máximo o maior valor inteiro possível, assim como pede o pseudocódigo
    G->v_vertices[fst - 1].flux = INT_MAX;
    while (DFS(G, fst, lst)){
        // Percorro meus vértices de tras pra frente, olhando o caminho feito pelo DFS
        for (int v = lst; v != fst; v = G->v_vertices[v - 1].parent) {
            // e guardo na minha lista com o caminho, para eu ter o caminho do primeiro até o ultimo
            path.push_front(&G->v_vertices[v - 1]);
            // Gambiarra para resolver um loop infinito
            if (G->v_vertices[v - 1].id == 0){
                return;
            }
        }

        int v;
        int adjIndex;
        // Percorro o caminho para atualizar os rotulos
        for (auto i : path){
            v = i->parent;
            for (int j = 0; j < G->adj_list[v - 1].size(); j++){
                if (G->adj_list[v - 1][j].target == i->id){
                    // Caso eu encontre um arco direto, meu fluxo passando pelo vertice sera  ξj = min{ξi, u¯(i,j)-f (i,j)}
                    // e também rotulo com '+', para mostrar que o arco que originou esse vertice foi direto
                    if (!G->adj_list[v - 1][j].reverse){
                        i->label = '+';
                        i->flux = min(G->v_vertices[i->parent - 1].flux, (G->adj_list[i->parent - 1][j].max_flux - G->adj_list[i->parent - 1][j].flux));
                    }
                    // E caso for um arco reverso, meu fluxo passando pelo vertice será de e ξj = min{ξi, f (i,j)-u(i,j)}
                    // e também rotulo com '-', para mostrar que o arco que originou esse vertice foi reverso
                    else{
                        i->label = '-';
                        i->flux = min(G->v_vertices[i->parent - 1].flux, (G->adj_list[i->parent - 1][j].flux - G->adj_list[i->parent - 1][j].min_flux));
                    }
                }
            }
            // E faço um print do caminho percorrido pelo DFS, junto de suas devidas rotulações
            cout << "[" << i->parent << ", " << i->label << ", " << i->flux << "] "; 
            
        }
        cout << endl;
        // O fluxo que está no vertice T é o gargalo do caminho atual, então eu guardo ele na variável 'flux', para melhor uso daqui em diante
        int flux = G->v_vertices[lst - 1].flux;
        // Caso o meu último vértice for rotulado, ou seja, tem qualquer coisa diferente de '0'
        if (G->v_vertices[lst - 1].label != '0'){
            // então agora eu vou aumentar o fluxo
            // para isso, percorro o meu caminho de trás pra frente
            for (int v = lst; v != fst; v = G->v_vertices[v - 1].parent) {
                int w = G->v_vertices[v - 1].parent;
                for (int i = 0; i < G->adj_list[w - 1].size(); i++){
                    if ( G->adj_list[w - 1][i].target == v){
                        // Caso for um arco direto, eu somo o gargalo no fluxo atual do arco
                        if (!G->adj_list[w - 1][i].reverse){
                            G->adj_list[w - 1][i].flux += flux;
                            // E caso ele tiver um arco reverso, preciso atualizar o valor desse arco reverso
                            if (G->adj_list[w - 1][i].hasReverse){
                                G->UpdateReverseEdge (w, v, flux);
                            }
                            // E também preciso verificar se o fluxo atual do arco excedeu o fluxo máximo
                            if (G->adj_list[w - 1][i].flux == G->adj_list[w - 1][i].max_flux){
                                G->adj_list[w - 1][i].full = true;
                            }
                        }
                        // E caso for um arco reverso, eu subtraio o gargalo no fluxo atual do arco
                        else{
                            G->adj_list[w - 1][i].flux -= flux;
                            // e também preciso atualizar o valor do arco direto desse arco reverso
                            G->UpdateDirectEdge (v, w, flux);
                            // E também preciso verificar se o fluxo atual do arco excedeu o fluxo mínimo
                            if (G->adj_list[w - 1][i].flux == G->adj_list[w - 1][i].min_flux){
                                G->adj_list[w - 1][i].full = true;
                            }
                        }
                        // e a cada passada em um arco, tento criar o seu respectivo arco reverso
                        G->createReverseEdge (w, v);
                    }
                }
                
            }
        }
        // Cancelo todos os rótulos
        for (int i = 1; i <= G->vertices; i++){
            G->v_vertices[i].seen = false;
            G->v_vertices[i].label = '0';
            G->v_vertices[i].parent = -1;
            G->v_vertices[i].flux = 0;
        }
        // e limpo minha lista de caminhos para guardar o caminho da proxima iteração
        path.clear();
    }
}


// pseudo código Ford Fulkerson
/*
void ford_fulkerson (Grafo){
    while (existir caminho){
        if (arco entre um vertice e outro == direto){
            rotulo como direto
            acho o valor do fluxo
        }
        else{
            rotulo como reverso
            acho o valor do fluxo
        }
        if (arco rotulado){
            construir caminho para aumento de fluxo
            aumentar fluxo, somar arcos diretos, subtrair arcos reversos
            cancelar todos os rotulos
            atualizar o grafo de aumento de fluxo
        }
    }
}







*/
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