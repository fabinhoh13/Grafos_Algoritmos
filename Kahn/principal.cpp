#include "Kahn.h"

int main () {
    int n_vertices, n_edges;

    cin >> n_vertices >> n_edges;

    
    Graph G (n_vertices, n_edges);
    //G.printAdj();

    vector <int> L = Kahn(&G);


    if (!L.empty()){
        int len = L.size();
        cout << "L = {";
        for (int i = 0; i < len - 1; i++){
            cout << L[i] << ", ";
        }
        cout << L[len - 1] <<"}" << endl;
    }
    else {
        cout << "Erro: ciclo detectado" << endl;
    }

    return 0;
}