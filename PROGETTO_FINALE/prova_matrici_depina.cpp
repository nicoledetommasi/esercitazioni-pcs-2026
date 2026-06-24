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
#include "metodo_gradiente_coniugato.hpp"
#include "sistema_lineare.hpp"  
using namespace std;

int main() {
    string nome_file;
    cout<< "Inserisci il nome del file della netlist: ";
    cin >> nome_file;

    auto risultato = lettura_netlist(nome_file);
    auto componenti = risultato.first;
    auto g = risultato.second;

    // stampa i componenti letti
    cout << "=== COMPONENTI ===\n";
    for (auto& c : componenti)
        cout << c.tipo << c.numero << " valore=" << c.valore
             << " da=" << c.nodo_da << " a=" << c.nodo_a << endl;

    // stampa gli archi del grafo
    cout << "\n=== ARCHI GRAFO ===\n";
    for (auto& arco : g.all_edges())
        cout << "arco: " << arco.from() << " -- " << arco.to() << endl;

    // trovo le maglie
    vector<vector<int>> maglie = trova_maglie(true, risultato); // o false per DFS

    cout << "\n=== MAGLIE ===\n";
    for (size_t i = 0; i < maglie.size(); i++) {
        cout << "maglia " << i << ": ";
        for (auto& nodo : maglie[i])
            cout << nodo << " ";
        cout << "\n";
    }

    // costruzione matrici
    MatrixXd R = costruzione_R(risultato);
    MatrixXd B = costruzione_B(maglie, risultato);
    VectorXd v = costruzione_v(maglie, risultato);

    cout << "\n=== MATRICE R ===\n" << R << "\n";
    cout << "\n=== MATRICE B ===\n" << B << "\n";
    cout << "\n=== MATRICE B^T*R*B ===\n" << B.transpose()*R*B << "\n";
    cout << "\n=== VETTORE v ===\n" << v << "\n";

    // soluzione sistema
    VectorXd i_maglia = calcolo_correnti(B, R, v);

    cout << "\n=== CORRENTI DI MAGLIA ===\n";
    for (int i = 0; i < i_maglia.size(); i++)
        cout << "I" << i+1 << " = " << i_maglia[i] << " A\n";

    // tensioni sui resistori
    VectorXd tensioni = calcolo_tensioni(B, R, i_maglia);

    cout << "\n=== TENSIONI SUI RESISTORI ===\n";
    int idx = 0;
    for (auto& c : componenti) {
        if (c.tipo == 'R') {
            cout << "R" << c.numero << ": V = " << tensioni[idx]
                 << " V,  I = " << tensioni[idx] / c.valore << " A\n";
            idx++;
        }
    }

    return 0;
}