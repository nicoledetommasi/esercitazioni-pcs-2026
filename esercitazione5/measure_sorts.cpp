#include <iostream>
#include <iomanip> // per formattare l'output in tabella
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include "sorts.hpp"
#include "timecounter.h" // misura i tempi
#include "randfiller.h" // riempimento casuale di vettori

int main() {
    std:: vector<int> sizes;
    for (int n=1; n<=100; n=n+10){
        sizes.push_back(n);
    }
    int ripetizioni=100;
    //FORMATTAZZIONE OUTPUT
    std::cout<< std::left<< std::setw(10)<<"Size"
             <<std::setw(12)<< "Bubble"
             <<std::setw(12)<< "Insertion"
             <<std::setw(12)<< "Selection"
             <<std::setw(12)<< "Mergesort"
             <<std::setw(12)<< "Quicksort"
             <<std::setw(12)<< "std::sort"<< std::endl;
    std::cout << std::string(80,'-')<<std::endl;

    randfiller rf;
    timecounter tc;
// creazione di vettore di vettori: genero 100 vettori per la dimensione n
    int n0=-1;
    for (int n:sizes){
        //Generazione vettore casuale 
        std::vector<std::vector<int>> matrice_base(ripetizioni, std::vector<int>(n));
        
        for (int i=0;i<ripetizioni; i++){
            rf.fill(matrice_base[i],-10000,10000);
        }
            // copio il vettore da usare per ogni algoritmo di ordinamento
            std::vector<std::vector<int>> m1=matrice_base;
            std::vector<std::vector<int>> m2=matrice_base;
            std::vector<std::vector<int>> m3=matrice_base;
            std::vector<std::vector<int>> m4=matrice_base;
            std::vector<std::vector<int>> m5=matrice_base;
            std::vector<std::vector<int>> m6=matrice_base;
            
            //BUBBLE SORT
            tc.tic();
            for(int j=0; j<ripetizioni; j++){
                bubble_sort(m1[j]);
            }
            double t_bubble=tc.toc();
            double media_bubble=t_bubble/100;

            //INSERTION SORT
            tc.tic();
            for(int j=0; j<ripetizioni; j++){
                insertion_sort(m2[j]);
            }
            double t_insertion=tc.toc();
            double media_insertion=t_insertion/100;
            //SELECTION SORT
            tc.tic();
            for(int j=0; j<ripetizioni; j++){
                selection_sort(m3[j]);
            }
            double t_selection=tc.toc();
            double media_selection=t_selection/100;
            //MERGESORT
            tc.tic();
            for(int j=0; j<ripetizioni; j++){
                merge_sort(m4[j],0,m4[j].size()-1);
            }
            double t_merge=tc.toc();
            double media_merge=t_merge/100;
            //QUICKSORT
            tc.tic();
            for(int j=0; j<ripetizioni; j++){
                quick_sort(m5[j],0,m5[j].size()-1);
            }
            
            double t_quick=tc.toc();
            double media_quick=t_quick/100;

            //std::sort
            tc.tic();
            for (int j=0; j<ripetizioni;j++){
                std::sort(m6[j].begin(),m6[j].end());
            }
            double t_sort=tc.toc();
            double media_sort=t_sort/100;
            
        
        std::cout << std::left << std::setw(6) << n
                  << std::setw(12) << media_bubble
                  << std::setw(12) << media_insertion
                  << std::setw(12) << media_selection
                  << std::setw(12) << media_merge
                  << std::setw(12) << media_quick
                  << std::setw(12) << media_sort << std::endl;

        double min_quad=std::min({media_bubble,media_insertion,media_selection});
        double min_log=std::min({media_merge,media_quick});
        if (n0==-1 && min_log<min_quad && n>1){
            n0=n;
        }
    } 
    if (n0!=-1){
        std::cout<< "n0= "<<n0<< std::endl;
        std::cout << "Oltre questa dimensione, gli algoritmi logaritmici sono piu' efficienti." << std::endl;
    } else {
        std::cout << "n0 non trovato nel range testato." << std::endl;
    }
    return 0;
}   

//Size      Bubble      Insertion   Selection   Mergesort   Quicksort   std::sort   
//--------------------------------------------------------------------------------
//1     1.583e-08   3.75e-08    3.25e-08    1.083e-08   1e-08       2.4667e-07  
//11    1.38083e-06 5.1292e-07  7.7916e-07  3.75167e-06 1.03667e-06 8.15e-07    
//21    3.68334e-06 1.35792e-06 2.20875e-06 7.975e-06   1.61042e-06 2.19833e-06 
//31    6.25709e-06 2.15958e-06 3.64084e-06 1.08438e-05 2.29625e-06 2.97375e-06 
//41    1.01433e-05 3.28417e-06 5.26667e-06 1.52771e-05 4.70417e-06 5.88291e-06 
//51    2.04687e-05 5.12834e-06 8.73584e-06 1.65138e-05 5.22458e-06 6.2725e-06  
//61    2.18488e-05 6.22708e-06 1.01629e-05 1.69121e-05 5.19375e-06 6.615e-06   
//71    2.47392e-05 7.21541e-06 1.16171e-05 1.71625e-05 5.23625e-06 6.22042e-06 
//81    2.80458e-05 8.28166e-06 1.21842e-05 1.6755e-05  5.64708e-06 6.64291e-06 
//91    3.05079e-05 8.6e-06     1.35171e-05 1.77388e-05 5.96709e-06 6.74125e-06 




