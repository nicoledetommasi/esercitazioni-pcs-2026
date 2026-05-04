#include<iostream>
#include <concepts>
#include <vector>
#include "sorts.hpp"
#include "randfiller.h"

int main() {
    randfiller rf;
    std::vector<int> vec(100); // DICHIARO UN VETTORE DI 100 ELEMENTI che rappresentano la dimensione
    rf.fill(vec,100,8000);

    for (int i=0;i<100;i++){
        std::vector<int> casuali(vec[i]); //genero un nuovo vettore che ha la dimensione del numero che è nella pos i-esima
        rf.fill(casuali,-500,500);

        quick_sort(casuali,0,casuali.size()-1);
        if (!is_sorted(casuali.begin(),casuali.end())){
            std::cerr<< "Il quicksort non ha ordinato bene il vettore \n";
            return EXIT_FAILURE;

        }
    }
    std::vector<std::string> stringa={"orizzonte","Zaffiro","Eclissi","Sussurro","Labirinto","Libellula","Mosaico","Alchimia","Vento","Miraggio"};
    quick_sort(stringa,0,stringa.size()-1);
    if (!is_sorted(stringa.begin(),stringa.end())){
            std::cerr<< "Il quicksort non ha ordinato bene il vettore di stringhe \n";
            return EXIT_FAILURE;

        }
    return EXIT_SUCCESS;
}