#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "sorts.hpp"
#include "timecounter.h" // misura i tempi
#include "randfiller.h" // riempimento casuale di vettori

int main() {
    std:: vector<int> sizes;
    for (int n=4; n<=8192; n*=2){
        sizes.push_back(n);
    }
    // std::vector<int> sizes = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};
    //std::vector<int> sizes(12); // Crea un vettore di 12 elementi vuoti
    //int n = 4;
    //for (int i = 0; i < 12; ++i) {
    //sizes[i] = n;
    //n *= 2;}

    //FORMATTAZZIONE OUTPUT
    std::cout<< std::left<< std::setw(10)<<"Size"
             <<std::setw(15)<< "Bubble"
             <<std::setw(15)<< "Insertion"
             <<std::setw(15)<< "Selection"
             <<std::setw(15)<< "std::sort"<< std::endl;
    std::cout << std::string(70,'-')<<std::endl;

    randfiller rf;
    timecounter tc;

    for (int n:sizes){
        //Generazione vettore casuale 
        std::vector<int> vec(n);
        rf.fill(vec,-1000,1000);

        std::cout<<std::left<< std::setw(10)<<n;
        // copio il vettore da usare per ogni test
        auto v1 = vec;
        auto v2 = vec;
        auto v3 = vec;
        auto v4 = vec;

        //BUBBLE SORT
        tc.tic();
        bubble_sort(v1);
        double time_bubble=tc.toc();
        //INSERTION SORT
        tc.tic();
        insertion_sort(v2);
        double time_insertion=tc.toc();
        //SELECTION SORT
        tc.tic();
        selection_sort(v3);
        double time_selection=tc.toc();
        //std::sort
        tc.tic();
        std::sort(v4.begin(),v4.end());
        double time_std=tc.toc();
         
        std::cout<<std::left<<std::setw(10)
                 <<std::setw(15)<<time_bubble
                 <<std::setw(15)<<time_insertion
                 <<std::setw(15)<<time_selection
                 <<std::setw(15)<<time_std<<std::endl;

    }
    return 0;
}

