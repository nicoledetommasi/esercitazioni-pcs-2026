#include <iostream>
#include <string>
#include <vector>
#include "sorts.hpp"
#include "randfiller.h"

int main() {
    randfiller rf;
    std::vector<int> vec(100); // DICHIARO UN VETTORE DI 100 ELEMENTI che rappresentano la dimensione
    rf.fill(vec,100,8000);

    for (int i=0;i<100;i++){
        std::vector<int> casuali(vec[i]); //genero un nuovo vettore che ha la dimensione del numero che è nella pos i-esima
        rf.fill(casuali,11,500);

        insertion_sort(casuali);
        if (!is_sorted(casuali)){
            std::cerr<< "L'insertion sort non ha ordinato bene il vettore \n";
            return EXIT_FAILURE;

        }
    }
    std::vector<std::string> stringa={"orizzonte","Zaffiro","Eclissi","Sussurro","Labirinto","Libellula","Mosaico","Alchimia","Vento","Miraggio"};
    insertion_sort(stringa);
    if (!is_sorted(stringa)){
            std::cerr<< "Il insertionsort non ha ordinato bene il vettore di stringhe \n";
            return EXIT_FAILURE;

        }
    return EXIT_SUCCESS;
}