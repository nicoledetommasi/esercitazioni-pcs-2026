#include <iostream>
#include "cicli_fondamentali.hpp"
using namespace std;

int main(){
    unidirected_graph<int> g;
    g.add_edge(unidirected_edge<int>(1, 2)); 
    g.add_edge(unidirected_edge<int>(2, 4)); 
    g.add_edge(unidirected_edge<int>(2, 3)); 
    g.add_edge(unidirected_edge<int>(1, 4)); 
    g.add_edge(unidirected_edge<int>(3, 4)); 

    int nodo_partenza = 1;

    // test DFS
    cout << "DFS" << endl;
    auto cicli_dfs = dfs_minima(g, nodo_partenza);
    cout << "numero cicli trovati: " << cicli_dfs.size() << endl;
    for (size_t i = 0; i < cicli_dfs.size(); i++){
        cout << "ciclo " << i << ": ";
        for (auto& n : cicli_dfs[i]){
            cout << n << " ";
        }
        cout << endl;
    }

    // test DE PINA
    cout << "\nDE PINA" << endl;
    auto cicli_depina = de_pina(g, nodo_partenza);
    cout << "numero cicli trovati: " << cicli_depina.size() << endl;
    for (size_t i = 0; i < cicli_depina.size(); i++){
        cout << "ciclo " << i << ": ";
        for (auto& val : cicli_depina[i]){
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "\nVERIFICA LUNGHEZZA CICLI DE PINA" << endl;
    for (size_t i = 0; i < cicli_depina.size(); i++){
        int lunghezza = 0;
        for (auto& val : cicli_depina[i]){
            if (val == 1) lunghezza++;
    }
    cout << "ciclo " << i << " ha " << lunghezza << " archi" << endl;
}

    if (cicli_dfs.size() == 2 && cicli_depina.size() == 2){
        cout << "\nTEST PASSATO" << endl;
    } else {
        cout << "\nTEST FALLITO" << endl;
    }

    return 0;
}