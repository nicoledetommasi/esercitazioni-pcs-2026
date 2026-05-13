#include <iostream>
#include <vector>
#include <optional>
#include "unidirected_graph.hpp"
using namespace std;
int main(){
    unidirected_graph<int> grafo;
    unidirected_edge<int> e1(1,2);
    unidirected_edge<int> e2(3,4);
    unidirected_edge<int> e3(1,5);

    grafo.add_edge(e1);
    grafo.add_edge(e2);
    // testo add_edge()
    // testo l'esistenza di un arco (edge_number)
    optional<int> risultato1=grafo.edge_number(e1); //optional restituisce un contenitore
    if (risultato1.has_value()){ // .has_value() restituisce true o false in base al fatto che il contenitore è pieno o vuoto
        cout<< "Arco trovato nella posizione: "<< risultato1.value()<< endl;
    }else{
        cout<< "ERRORE: arco non trovato ma doveva esserci "<<endl;
    }
    // testo la non esistenza di un arco nel grafo
    optional<int> risultato2=grafo.edge_number(e3);
    if (!risultato2.has_value()){
        cout<< "Arco non trovato nella posizione (non esiste nel grafo)"<< endl;
    }else{
        cout<< "ERRORE: arco trovato (non è stato aggiunto al grafo, non dovrebbe esserci) "<<endl;
    }
    
    //testo la funzione neighbours
    grafo.add_edge(e3);
    set<int> vicini1=grafo.neighbours(3);
    set<int> vicini2=grafo.neighbours(5);
    if (!vicini1.empty()){
        cout<< "I nodi vicini al nodo 3 sono: "<< endl;
        for (const auto& v:vicini1){
            cout<<v<<" "<< endl;
        }
    }else{
        cout<< "Il nodo 3 non ha vicini o non esiste nel grafo"<< endl;
    }
    // testo all_edges()
    vector<unidirected_edge<int>> archi=grafo.all_edges();
    if(!archi.empty()){
        cout<< "gli archi nel grafo sono: "<<endl;
        for (const auto& a:archi){
            cout<< a << " "<<endl;
        }
    }else{
        cout<< "Non sono presenti archi nel grafo"<< endl;
    }

    // testo all_nodes()
    set<int> nodi=grafo.all_nodes();
    if (!nodi.empty()){
        cout<< "I nodi all'interno del grafo sono: "<< endl;
        for (const auto& n:nodi){
            cout << n << endl;
        }
    }else{
        cout << "Il grafo non ha nodi"<< endl;
    }

   
    unidirected_graph<int> grafo2;
    unidirected_edge<int> e4(4,9);
    unidirected_edge<int> e5(7,8);
    unidirected_edge<int> e6(2,6);
    grafo2.add_edge(e5);
    grafo2.add_edge(e4);
    grafo2.add_edge(e6);
    grafo2.add_edge(e1);
    grafo2.add_edge(e2);
     // test dell'operatore operator-
    cout << "\n--- TEST DIFFERENZA (G1 - G2) ---" << endl;
    cout << "G1 ha: (1,2), (3,4), (1,5)" << endl;
    cout << "G2 ha: (1,2), (3,4), (7,8), (4,9), (2,6), " << endl;
    unidirected_graph<int> differenza_grafi = grafo - grafo2;
    vector<unidirected_edge<int>> archi_differenza=differenza_grafi.all_edges();
    
    if (!archi_differenza.empty()){
        cout<< "Gli archi del grafo differenza sono: "<< endl;
        for (const auto& d:archi_differenza){
            cout << d << endl;
        }
    }else{
        cout << "Il grafo risultante dalla differenza non ha archi"<< endl;
    }
    // testo edge_at() dal grafo differenza
    if (!archi_differenza.empty()) {
        cout << "Test edge_at(0): " << differenza_grafi.edge_at(0) << endl;
    }


    return 0;
}