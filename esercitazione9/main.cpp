#include <iostream>
#include "unidirected_graph.hpp"
#include "graph_visit.hpp"
using namespace std;

int main(){
    unidirected_graph<int> grafo;

    grafo.add_edge(unidirected_edge<int>(1, 2));
    grafo.add_edge(unidirected_edge<int>(1, 3));
    grafo.add_edge(unidirected_edge<int>(1, 4));
    grafo.add_edge(unidirected_edge<int>(1, 6));

    grafo.add_edge(unidirected_edge<int>(2, 7));
    grafo.add_edge(unidirected_edge<int>(2, 5));
    grafo.add_edge(unidirected_edge<int>(2, 4));

    grafo.add_edge(unidirected_edge<int>(3, 6));

    grafo.add_edge(unidirected_edge<int>(4, 7));
    grafo.add_edge(unidirected_edge<int>(4, 6));

    grafo.add_edge(unidirected_edge<int>(5, 7));

    grafo.add_edge(unidirected_edge<int>(6, 7));
    grafo.add_edge(unidirected_edge<int>(6, 8));

    grafo.add_edge(unidirected_edge<int>(7, 9));

    grafo.add_edge(unidirected_edge<int>(8, 9));

    fifo<int> coda;
    unidirected_graph<int> grafo_finale1=graph_visit(grafo,1,coda);
    save_to_dot(grafo_finale1, "test_grafo_bfs.dot");

    lifo<int> pila;
    unidirected_graph<int> grafo_finale2=graph_visit(grafo,1,pila);
    save_to_dot(grafo_finale2, "test_grafo_dfs.dot");

    unidirected_graph<int> grafo_finale3=recursive_dfs(grafo,1);
    save_to_dot(grafo_finale3, "test_grafo_rec_dfs.dot");
    
    fifo<int> coda_dijkstra;
    unidirected_graph<int> grafo_finale4=dijkstra_senza_pesi(grafo,1,coda_dijkstra);
    save_to_dot(grafo_finale4, "test_grafo_dijkstra.dot");

    return 0;
}