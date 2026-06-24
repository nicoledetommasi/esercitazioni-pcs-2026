#include <concepts>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include "unidirected_edge.hpp"
#include "unidirected_graph.hpp"
#include "cicli_fondamentali.hpp"
#include "lettura_netlist.hpp"
#include "graph_visit.hpp"
using namespace std;

int main(){
    string nome_file;
    cout<< "Inserisci il nome del file della netlist: ";
    cin >> nome_file;

    auto risultato = lettura_netlist(nome_file);
    auto componenti = risultato.first;
    auto g = risultato.second;

    // stampa i componenti letti
    for (auto& c : componenti){
        cout << c.tipo << c.numero << " valore=" << c.valore 
             << " da=" << c.nodo_da << " a=" << c.nodo_a << endl;
    }

    // stampa gli archi del grafo
    for (auto& arco : g.all_edges()){
        cout << "arco: " << arco.from() << " -- " << arco.to() << endl;
    }

    vector<vector<int>> depina=trova_maglie(true, risultato);
    vector<vector<int>> cicli=trova_maglie(false, risultato);
    cout<<"no depina\n";
    for (auto& ciclo :cicli){
        for (auto& arco:ciclo){
            cout<< arco<<'\n';
        }
    }
    cout<<"depina\n";
    for (auto& ciclo :depina){
        for (auto& arco:ciclo){
            cout<< arco<<'\n';
        }
    }
    
    return 0;
}