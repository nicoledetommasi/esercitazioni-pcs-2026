#include <iostream>
#include <map> //Una std::map memorizza coppie di elementi: una chiave (key) e un valore (value)
//a chiave è il nodo e il valore è il set dei suoi vicini.
#include <set>
#include <vector>
#include "unidirected_edge.hpp"
#include <optional>
using namespace std;
template <typename T>
class unidirected_graph{
    //a ogni nodo T associo un insieme di elementi di tipo T (set che è l'insisme dei suoi vicini)
    map<T, set<T>> lista_adiacenza; //(lista di adiacenza)
   // costruisco un vettore che memorizza gli arcchi nell'ordine in cui sono inseriti
   vector<unidirected_edge<T>> archi;
public:
    // costruttore di default (inizializzo il grafo vuoto)
    unidirected_graph(){}
    //costruttore di copia
    unidirected_graph(const unidirected_graph& other): 
    lista_adiacenza(other.lista_adiacenza),archi(other.archi){}
    // metodo neighbours()
    set<T> neighbours(const T& nodo) const{ 
        auto indice_nodo=lista_adiacenza.find(nodo);
        if(indice_nodo==lista_adiacenza.end()){
            return set<T>();
        }
        return lista_adiacenza.at(nodo);   
        // ritorna l'insieme dei nodi che rispondono a quella chiave
    }
    //metodo add_edge(): Ricevo un arco, se l'arco già esiste non faccio nulla; altrimenti lo aggiugno 
    void add_edge(const unidirected_edge<T> & e) {
        //se arco esiste, non fare nulla
        for(int i = 0; i<(int)archi.size();i++){
            if (archi[i]==e){
                return;
            }
        }
        //aggiugno arco al vettore
        archi.push_back(e);

        //Modifico lista adiacenza quando aggiungo un arco
        lista_adiacenza[e.from()].insert(e.to());
        lista_adiacenza[e.to()].insert(e.from());
    }

    // metodo all_edges()
    vector<unidirected_edge<T>> all_edges() const{
        return archi;
    }
    //metodo all_nodes()
    set<T> all_nodes() const{
        set<T> lista_nodi;
        for(const auto& n:lista_adiacenza){
            T nodo=n.first; // accedo ala chiave
            lista_nodi.insert(nodo);
        }
        return lista_nodi;
    }
    //metodo edge_number()
    optional<int> edge_number(const unidirected_edge<T>& e)const{
        for( int i=0;i< (int)archi.size();i++){
            if(e==archi[i]){
                return i; // se lo trovo ritorno direttamente il numero dell'arco
            }
        }
        return nullopt;
    } 
    //metodo edge_at()
    unidirected_edge<T> edge_at(const int i){
        return archi.at(i); // at verifica che esista e restituisce l'arco, se non esiste restitutisce errore
    }
    // operator-()
    unidirected_graph<T> operator-(const unidirected_graph<T>& other) const{
        unidirected_graph<T> differenza_grafi;
        for (int i=0;i<(int)archi.size();i++){
            const auto& arco_corrente=archi[i];
            bool trovato_in_other=false;
        for(int j=0;j<(int)other.archi.size();j++){
            if(arco_corrente==other.archi[j]){
                trovato_in_other=true;
                break;
            }
        }
        if (!trovato_in_other){
            differenza_grafi.add_edge(arco_corrente);
        }
    }
    return differenza_grafi;
    }

};