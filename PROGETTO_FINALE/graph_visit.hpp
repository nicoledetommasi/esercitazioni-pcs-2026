#pragma once
#include <queue>
#include <stack>
#include "unidirected_graph.hpp"
#include <map>
#include <vector>
#include <limits>
#include <fstream>
#include <numeric>
#include <queue>
#include <string>
using namespace std;

template<typename T>

class fifo{
private:
    queue<T> coda;
public:
    void put(const T& value){
        coda.push(value);
    } // inserisco un elemento alla fine della cosa 
    T get(){
        T testa=coda.front(); // restituisce l'elemento
        coda.pop(); //lo rimuovo per estrarlo dalla coda ma non restituisce nulla
        return testa;
    }
    bool empty() const{
        return coda.empty();
        // verifico se il contenitore è vuoto 
        


    }

};
template<typename T>
class lifo{
    private: 
        stack<T> pila;
    public:
    void put(const T& value){
        pila.push(value);
    }
    T get() {
        T testa=pila.top();
        pila.pop();
        return testa;
    }
    bool empty() const{
        return pila.empty();
    }
};
template<typename T , typename C>

unidirected_graph<T> graph_visit(const unidirected_graph<T>& grafo, T nodo_sorgente, C& container){
    map< T,bool> reached;
    unidirected_graph<T> g;
    reached[nodo_sorgente]=true;
    container.put(nodo_sorgente);
    while (!container.empty() ){
        T n=container.get();
        for(T w:grafo.neighbours(n)){ // esploro i vicini nella lista di adiacenza
            if(!reached[w]){ // se non è stato visitato
                reached[w]=true;
                g.add_edge(unidirected_edge<T>(n,w));
                container.put(w);
            }
        }
    }
    return g;
}

template<typename T>
void dfs_helper(T u, const unidirected_graph<T>& grafo, map<T, bool>& reached, unidirected_graph<T>& tree){
    reached[u]=true;
    for(T v:grafo.neighbours(u)){
        if(!reached[v]){
            tree.add_edge(unidirected_edge<T>(u,v));
            dfs_helper(v,grafo,reached,tree);
        }
    }
}
// recursive_dfs()
template<typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& grafo, int nodo_sorgente){
    unidirected_graph<T> g;
    map< T,bool> reached;
    dfs_helper(nodo_sorgente, grafo,reached,g);
    return g;
}
//algoritmo dijkstra senza pesi per trovare i cammini minimi
template<typename T>
struct dijkstra{
    unidirected_graph<T> albero;
    map<T,T> predecessori;
};


template<typename T>
dijkstra<T> dijkstra_senza_pesi(const unidirected_graph<T>& g, T nodo_sorgente)//m è il numero totale di nodi, ricordarsi nel main di chimare all_nodes
{   unidirected_graph<T> albero;
    

    map<T, int> dist; //array predecessore inizializzato tutto a -1
    map<T, T> pred;//problema dell'infinito //array distanze inizializzate tutte a infinito

    for (const auto& nodo:g.all_nodes()){
        dist[nodo]=numeric_limits<int>::max();
    }
    pred[nodo_sorgente]=nodo_sorgente;//l'unico a non essere -1 è il primo che è predecessore di se stesso
    dist[nodo_sorgente]=0;//la prima distanza da se stesso è 0

    //priority queue
    priority_queue<pair<int,T>, vector<pair<int,T>>, greater<pair<int, T>>> prio_queue;//definisco una struttura di coppie distanza-nodo salvate in vettore, ordinato dal più piccolo al più grande
    prio_queue.push({0,nodo_sorgente});

    // for (int i=0;i<m;i++){
    //     prio_queue.push({dist[i], i});
    // }
    while (!prio_queue.empty()){
        T u=prio_queue.top().second;//prendi la prima coppia del vettore e di essa il secondo elemento che è il nodo con distanza minima
        int p=prio_queue.top().first;//prendi la distanza
        prio_queue.pop();//togli la coppia con distanza minima

        if (p>dist[u]) continue;

        for (const T& w: g.neighbours(u)){
            if (dist.find(w)==dist.end()||dist[w]> dist[u]+1){
                dist[w]=dist[u]+1;
                pred[w]=u;

                albero.add_edge(unidirected_edge<T>(u,w));
                prio_queue.push({dist[w],w});//aggiorna la priorità perchè ho trovato un buon percorso da percorrere
                //la coda si riordina automaticamente una volta aggiunta la coppia, distanza w e w
                //è per fare il decrease key che ha fatto il prof vicini
            }
        }
    }
    return {albero, pred};
}
/*template<typename T,typename C>
dijkstra dijkstra_senza_pesi(const unidirected_graph<T>& grafo, int nodo_sorgente, C& container){
    unidirected_graph<T> g;
    // recupero tutti i nodi 
    auto nodi= grafo.all_nodes();
    const int INF= numeric_limits<int>::max();
    map<T, int> dist;
    map<T,T> pred;
    for (T nodo:nodi){
        dist[nodo]=INF;
        pred[nodo]=-1;

    pred[nodo_sorgente]=nodo_sorgente;
    dist[nodo_sorgente]=0;
    container.put(nodo_sorgente);

    while (!container.empty()){
        T u=container.get();
        for (T w:grafo.neighbours(u)){
            if (dist[w]> dist[u]+1){
                dist[w]=dist[u]+1;
                pred[w]=u;
                container.put(w);
            }
        }
    }
    // costruzione grafo finale dopo aver calcolato tutti i risultati
    for (T nodo:nodi){
        if (dist[nodo]!= INF && nodo!=nodo_sorgente){
            g.add_edge(unidirected_edge<T>(pred[nodo],nodo));
        }
    }
    return {albero,pred};
}*/


template<typename T>
void save_to_dot(const unidirected_graph<T>& g, const string& filename) {
    ofstream out(filename);

    if (!out.is_open()) {
        // Gestione errore se il file non si apre
        return;
    }

    // Inizio del file DOT per un grafo non orientato
    out << "graph G {" << endl;

    // Recuperiamo tutti i nodi
    auto nodes = g.all_nodes();
    
    // Scriviamo i nodi (opzionale, utile se ci sono nodi isolati senza archi)
    for (const auto& n : nodes) {
        out << "    " << n << ";" << endl;
    }

    // Recuperiamo tutti gli archi
    // Nota: Assicurati che il tuo grafo restituisca la lista degli archi
    auto edges = g.all_edges(); 

    for (const auto& e : edges) {
        // e.first è il nodo sorgente, e.second è il nodo destinazione
        out << "    " << e.from()<< " -- " << e.to() << ";" << endl;
    }

    out << "}" << endl;
    out.close();
}



    
