#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"
#include "graph_visit.hpp"
#include <iostream>
#pragma once
#include <vector>
#include <set>
#include <numeric>
using namespace std;

//una bool per dire se esiste il path e lo calcola e trova_cicli restituisce il percorso tra u e v
template<typename T>
bool esistenza_ciclo(const unidirected_graph<T>& t,T u, T v, map<T, bool>& reached, vector<T>& path){
    reached[u]=true;
    path.push_back(u);
    if (u==v){
        return true;
    }
    for(auto& n:t.neighbours(u)){
        if(!reached[n]){
            if(esistenza_ciclo(t,n,v, reached,path)){
                return true;
            }
        }
    }
    path.pop_back();
    return false;
} 


template<typename T>
vector<T> trova_ciclo(const unidirected_graph<T>& t, T u,T v){
    map<T, bool> reached;
    vector<T> path;
    if(esistenza_ciclo(t,u,v,reached,path)){
        return path;
    }
    return vector<T>(); // se non esiste il ciclo mi da il vettore vuoto
}

template<typename T>
vector<vector<T>> dfs_minima(unidirected_graph<T>& g, T nodo_partenza){
    vector<vector<T>> cicli;
    lifo<T> s;
    unidirected_graph<T> t=graph_visit(g,nodo_partenza,s);
    vector<unidirected_edge<T>> c=g-t; // vettore di lati, itero facilemnte sui lati 
    for(auto& arco:c){
        auto path=trova_ciclo(t, arco.from(),arco.to());
        cicli.push_back(path);
    }
    return cicli;
}


// DE PINA 
template<typename T>
struct DepinaDati{
    vector<vector<int>> S;
    int m;
    int k;
    vector<unidirected_edge<T>> coalbero;
};
template<typename T>
DepinaDati<T> prep_depina(unidirected_graph<T>& g, T nodo_partenza){
    lifo<T> s;
    unidirected_graph<T> t=graph_visit(g,nodo_partenza,s);
    vector<unidirected_edge<T>> c=g-t;
    vector<vector<T>> S; // vettore di vettori della base canonica 
    int m=g.all_edges().size();
    int k=c.size();
    for (auto& arco:c){ // per ogni e appartenente a g e anche a c allora metti in Si nella posizione dell'arco in g 1
        vector<int> Si(m,0);
        Si[g.edge_number(arco).value()]=1;
        S.push_back(Si);
    }
    return {S, m, k ,c};
}
template<typename T>
int prod_scalare(const vector<T>& S,const vector<T>& P){
    int prod=0;
    for(size_t i=0; i<S.size(); i++){
        prod+= S[i]*P[i];
    }
    return prod % 2;
}

template<typename T>
vector<T> XOR(const vector<T>& S,const vector<T>& P){
    vector<T> risultato(S.size(),0);
    for(size_t i=0; i<S.size(); i++){
        risultato[i]=S[i]^P[i]; // funzione XOR in c++: non ho bisogno dell'if se S[i]=0 perchè lo gestisce già
    }
    return risultato;
}
// problema con l'ordinamento dei nodi  
template<typename T> 
struct nodo_liftato {
    T nodo_originale;
    bool sign; // true=+ =1 false=-=0

    bool operator<(const nodo_liftato& other)const{
        if(nodo_originale !=other.nodo_originale){
            return nodo_originale<other.nodo_originale; // se sono ordinati ritorna true 
        }
        return sign < other.sign; // se sono uguali allora restituiscimi prima il segno minore e poi quello maggiore
    }
    bool operator==(const nodo_liftato& other)const{
        return nodo_originale== other.nodo_originale && sign== other.sign;
    }
};
template<typename T>
unidirected_graph<nodo_liftato<T>> lifting(const unidirected_graph<T>& g, const vector<int>& Si){
    auto archi=g.all_edges(); // restituisce tutti gli archi vector<unidirected_edge>>
    int m=archi.size(); //quanti archi ho
    unidirected_graph<nodo_liftato<T>> g_primo; //inizializzo il grafo G'

    for(int i=0;i<m;i++){ //itero sul numero si archi
        T u=archi[i].from();  
        T v=archi[i].to();

        nodo_liftato<T> u_pos={u, true};
        nodo_liftato<T> u_neg={u, false};
        nodo_liftato<T> v_pos={v, true};
        nodo_liftato<T> v_neg={v, false};
        if(Si[i]==1){ // se l'arco è attivo aggiungo (u+,v-) e (u-,v+)
            g_primo.add_edge(unidirected_edge<nodo_liftato<T>>(u_pos,v_neg));
            g_primo.add_edge(unidirected_edge<nodo_liftato<T>>(u_neg,v_pos));
        }else{ // se l'arco non è attivo (u+,v+) e (u-,v-)
            g_primo.add_edge(unidirected_edge<nodo_liftato<T>>(u_pos,v_pos));
            g_primo.add_edge(unidirected_edge<nodo_liftato<T>>(u_neg,v_neg));
        }
    } 
    return g_primo;
}
template<typename T> // TUTTI i cammini minimi tra v_neg e v_pos
vector<vector<nodo_liftato<T>>> tutti_cammini_minimo(const unidirected_graph<T>& g, const unidirected_graph<nodo_liftato<T>>& g_primo){
    auto nodi=g.all_nodes();
    vector<vector<nodo_liftato<T>>>  cammini;
    for(auto& v:nodi){
        nodo_liftato<T> v_pos={v, true};
        nodo_liftato<T> v_neg={v, false};
        auto risultato=dijkstra_senza_pesi(g_primo,v_neg);
        vector<nodo_liftato<T>> cammino; // costruisco il cammino al contrario
        // if per gestire l'optional 
        if(risultato.predecessori.find(v_pos)==risultato.predecessori.end()){ // parte da v_neg e se non trova v_pos allora aggiungi un cammino vuoto
            cammini.push_back(cammino); // aggiungo un cammino vuoto
            continue;
        }
        nodo_liftato<T> corrente=v_pos;
        while(!(corrente==v_neg)){
            cammino.push_back(corrente);
            corrente=risultato.predecessori[corrente];
        } 
        cammino.push_back(v_neg);
        reverse(cammino.begin(),cammino.end());
        cammini.push_back(cammino);
    }
    return cammini; // matrice con righe che sono vettori dove gli elementi sono {nodo, true/false}
}

template<typename T>
vector<int> find_minimal_cycle(const unidirected_graph<T>& g, const vector<int>& Si){
    auto g_primo=lifting(g,Si);
    auto cammini=tutti_cammini_minimo(g,g_primo);
    int m=g.all_edges().size();
    vector<int> ciclo_migliore;
    int min_ones=numeric_limits<int>::max();
    for(auto& cammino:cammini){
        if(cammino.empty()) continue;
        vector<int> C(m,0); // vettore di incidenza 
        for(size_t j=0;j<cammino.size()-1;j++){
            auto indice = g.edge_number(unidirected_edge<T>(cammino[j].nodo_originale,cammino[j+1].nodo_originale));
            if(indice.has_value()){
                C[indice.value()]=(C[indice.value()]+1)%2;
            }
        }
        int conteggio=0;
        for(int i=0;i<m;i++){
            if(C[i]==1){
                conteggio+=1;
            }else continue;
        }
        if(conteggio<min_ones){
            min_ones=conteggio;
            ciclo_migliore=C;
        }
    }
    return ciclo_migliore;
}
template<typename T>
vector<vector<int>> de_pina(unidirected_graph<T>& g, T nodo_partenza){
    auto dati=prep_depina(g,nodo_partenza);
    vector<vector<int>> B;
    int k=dati.k;
    for(int i=0;i<k;i++){
        auto Ci=find_minimal_cycle(g,dati.S[i]);
        B.push_back(Ci);
        for(int j=i+1;j<k;j++){
            if(prod_scalare(Ci,dati.S[j])==1){
                dati.S[j]=XOR(dati.S[j],dati.S[i]);
            }
        }
    }

    return B;
}
