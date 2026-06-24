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
#include "lettura_netlist.hpp"
#include "graph_visit.hpp"
#include "Eigen/Eigen"
#include "metodo_gradiente_coniugato.hpp"
using namespace Eigen;
using namespace std;
// costruisco la matrice B: deve avere tante righe quanti sono i resistori 
// e tante colonne quanti sono i cicli

MatrixXd costruzione_B(vector<vector<int>>& maglie,pair<vector<Componente>,unidirected_graph<int>>& coppie){
    //calcolo il numero di resistori
    auto componenti=coppie.first; // vettore
    int n_resistori=0;
    for(auto& struttura:componenti){
        if(struttura.tipo=='R'){
            n_resistori+=1;
        }
    }

    //calcolo il numero dei cicli
    auto n_cicli=maglie.size();
    //inizializzo a zero la matrice B con dimensioni n_resistori x n_cicli
    MatrixXd B=MatrixXd::Zero(n_resistori, n_cicli);

    // devo iterare sulla quantità di cicli
    for(size_t i=0; i<n_cicli; i++){
        // per ogni coppia di nodo devo vedere se c'è il resistore
        if (maglie[i].empty()) continue;
        for(size_t j=0; j<maglie[i].size();j++){ // sto iterando sul singolo ciclo in maglie
            int indice_resistore=0;
            int u=maglie[i][j];
            int w=maglie[i][(j+1) % maglie[i].size()];
            for(auto& componente:componenti){
                if(componente.tipo !='R') continue;
                if((u==componente.nodo_da && w==componente.nodo_a)||
                    (w==componente.nodo_da && u==componente.nodo_a)){
                // se il nodo che incontri è ugluale a quello in componenti controlla se è un resistore
                    if(u<w){
                        B(indice_resistore,i)=(+1);
                    }else{
                    // se il nodo che incontri è ugluale a quello in componenti controlla se è un resistore
                        B(indice_resistore,i)=(-1);
                    }
                }
                indice_resistore++;
            }
        }
    }
    return B;
}

// calcolo matrice R
MatrixXd costruzione_R(pair<vector<Componente>,unidirected_graph<int>>& coppie){
    // n_resistori
    auto componenti=coppie.first;
    int n_resistori=0;
    for(auto& struttura:componenti){
        if(struttura.tipo=='R'){
            n_resistori++;
        }
    }
    MatrixXd R=MatrixXd::Zero(n_resistori,n_resistori);
    int i=0;
    for(auto& struttura:componenti){
        if(struttura.tipo=='R'){
            R(i,i)=struttura.valore;
            i++;
        }
    }
    return R;
}

// calcolo termine noto v
VectorXd costruzione_v(vector<vector<int>>& maglie,pair<vector<Componente>,unidirected_graph<int>>& coppie){
    auto componenti=coppie.first; // vettore
    auto n_cicli=maglie.size();
    VectorXd v=VectorXd::Zero(n_cicli);
    for(size_t i=0; i<n_cicli; i++){
        for(size_t j=0; j<maglie[i].size()-1;j++){ // sto iterando sul singolo ciclo in maglie
            int u=maglie[i][j];
            int w=maglie[i][j+1];
            for(auto& componente:componenti){
                if(componente.tipo !='V') continue;

                if(u==componente.nodo_da && w==componente.nodo_a){
                    v[i]-=componente.valore;
                }else if((u==componente.nodo_a && w==componente.nodo_da)){
                    v[i]+=componente.valore;
                }
            }
        }
    }
    return v;
}
// SISTEMA LINARE 
VectorXd calcolo_correnti(MatrixXd& B,MatrixXd& R, VectorXd& v){
    MatrixXd A=B.transpose()*R*B;
    VectorXd x0=VectorXd::Zero(A.rows());
    double tol =1.0e-12;
    auto risultato=pcg(A,v,x0,tol);
    if(!risultato.has_value()){
        cerr<<"PCG fallito!"<< endl;
    }
    return risultato.value();// vettore delle correnti di maglia
}
VectorXd calcolo_tensioni(MatrixXd& B,MatrixXd& R,VectorXd& i_maglia){
    return R*B*i_maglia;
}