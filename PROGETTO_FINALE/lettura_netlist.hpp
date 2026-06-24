#include <concepts>
#include <iostream>
#pragma once
#include <vector>
#include <sstream>
#include <set>
#include <numeric>
#include <fstream>
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"
#include "cicli_fondamentali.hpp"
using namespace std;
// LETTURA FILE E COSTRUZIONE DEL GRAFO
struct Componente{
    char tipo;
    int numero;
    double valore;
    int nodo_da;
    int nodo_a;
};
// vector<Componente> ha tutti i componenti  e unidirected_graph<int> ha il nodo e la lista dei nodi adiacenti 
pair<vector<Componente>,unidirected_graph<int>> lettura_netlist(const string& filename){
    // string filename="prova2.txt";
    ifstream ifs(filename);
    unidirected_graph<int> g;
    vector<Componente> componenti;
    if(!ifs.is_open()){
        cerr<<"impossibile aprire il file!"<< filename <<endl;
        return {componenti,g};
    }
    Componente c;
    string prima_colonna;
    while (ifs>>prima_colonna>>c.valore>>c.nodo_da>>c.nodo_a){
        stringstream ss(prima_colonna);
        ss>>c.tipo>>c.numero;// string to integer perchè l'1 è memorizzato come stringa
        componenti.push_back(c);
        g.add_edge(unidirected_edge<int>(c.nodo_da,c.nodo_a));
    }// ss vede già che 1 è un int perchè converte direttamente i dati 
    return {componenti,g};
}
// trasformo il vettore di incidenza in ciclo
vector<int> conversione(const vector<int>& v, pair<vector<Componente>,unidirected_graph<int>>& coppie){
    vector<int> risultato;
    vector<int> indici;
    for(size_t i=0; i< v.size();i++){
        if(v[i]==1){
            //risultato.push_back(coppie.first[i].nodo_da);
            //risultato.push_back(coppie.first[i].nodo_a);
            indici.push_back(i); // ho gli indici degli archi attivi
        }
    }// vettore archi attivi
    auto archi=coppie.second.all_edges();
    auto nodo_corrente=archi[indici[0]].from();//scelgo il primo nodo
    int partenza=nodo_corrente;
    risultato.push_back(nodo_corrente);
    vector<bool> usato(indici.size(),false);
    do{ 
        bool trovato_in_questo_giro=false;
        for(size_t i=0; i< indici.size();i++){
            if(usato[i]) continue;
            int indice=indici[i];
            if(archi[indice].from()==nodo_corrente){
                nodo_corrente=archi[indice].to();
                risultato.push_back(nodo_corrente);
                usato[i]=true;
                trovato_in_questo_giro=true;
                break;
            }else if(archi[indice].to()==nodo_corrente){
                nodo_corrente=archi[indice].from();
                risultato.push_back(nodo_corrente);
                usato[i]=true;
                trovato_in_questo_giro=true;
                break;
            }
        }
        if(!trovato_in_questo_giro) break;
    }while(nodo_corrente!=partenza && find(usato.begin(),usato.end(),false)!=usato.end());
   
    return risultato;
}

// TROVARE I CICLI MINIMI
vector<vector<int>> trova_maglie(bool opzione, pair<vector<Componente>,unidirected_graph<int>>& coppie){
    auto& g=coppie.second; // metto & per non fare la copia di g ma uso un riferimento
    auto nodo_partenza=*g.all_nodes().begin(); // begin restituisce un iteratore e *  me lo dereferenzia (mi da l'elemento a cui punta l'iteratore )
    vector<vector<int>> maglie;
    if(opzione){
       auto maglie_depina=de_pina(g,nodo_partenza);
        for(auto vettore : maglie_depina){
            vector<int> maglia=conversione(vettore,coppie);
            maglie.push_back(maglia);
        }
    }else{
        maglie=dfs_minima(g,nodo_partenza);
    }
    return maglie;
}
