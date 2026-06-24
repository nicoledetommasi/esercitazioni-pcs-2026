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
#include "lettura_netlist.hpp"
#include "graph_visit.hpp"
#include "cicli_fondamentali.hpp"
#include "Eigen/Eigen"
#include "sistema_lineare.hpp"
#include "metodo_gradiente_coniugato.hpp"
using namespace Eigen;
using namespace std;


int main(){
    string nome_file;
    cout<< "Inserisci il nome del file della netlist: ";
    cin >> nome_file;
    bool scelta;
    cout<< "Inserisci il depina (true) o dfs (false): ";
    cin >> scelta;

    auto risultato = lettura_netlist(nome_file);
    auto componenti = risultato.first;
    auto g = risultato.second;

    if (componenti.empty()){
        cerr<<" Errore: impossibile procedere. Controlla il nome del file.\n";
        return 1;
    }
    
    vector<vector<int>> maglie=trova_maglie(scelta,risultato);
    MatrixXd R = costruzione_R(risultato);
    MatrixXd B = costruzione_B(maglie, risultato);
    VectorXd v = costruzione_v(maglie, risultato);

    VectorXd I = calcolo_correnti(B, R, v);
    VectorXd v_r = calcolo_tensioni(B, R, I);

    VectorXd I_r = B*I;
    size_t i = 0;

    vector<string> resistori;
    for (auto const& componente : componenti)
    {
        if (componente.tipo == 'R')
        {
            double tensione = v_r(i);
            double corrente = I_r(i);
            cout.precision(2);
            cout << componente.tipo << componente.numero << " : V = " << tensione << " Volt, I = " << corrente << " Ampere\n";
            i ++;
        }
    }
    
    return 0;
}