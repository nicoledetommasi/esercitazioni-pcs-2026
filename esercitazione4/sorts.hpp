#include <iostream>
#include <vector>
#include <algorithm>

// bubblesort
template<typename T>
void bubble_sort(std::vector<T>& vec) {
    int N=vec.size();
    for (int i=0;i<=N-1;i++){
        for (int j=N-1; j>i;j--){
            if (vec[j]<vec[j-1]) {
               std::swap(vec[j], vec[j-1]);
            }
        }
    }

}
// insertion sort
template<typename T>
void insertion_sort(std::vector<T>& vec) {
    int N=vec.size();
    for (int j=1; j<=N; j++) {
        T key=vec[j];
        int i=j-1;
        while (i>=0 && vec[i]>key){
            vec[i+1]=vec[i];
            i=i-1;
        }
        vec[i+1]=key;
    }
}
// selectionsort
template<typename T>
void selection_sort(std::vector<T>& vec) {
    int N=vec.size();
    for ( int i=0; i<=N-1;i++){
        int minimo =i;
        for (int j=i+1; j<N;j++){
            if ( vec[j]<vec[minimo]){
                minimo=j;
            }
        }
        std::swap(vec[i],vec[minimo]);
    }
}

// FUNZIONE is sorted()
template<typename T>
bool is_sorted(std::vector<T>& vec){
    if (vec.size()<2){
        return true; // vettore vuoto ordinato per definizione
    }
    int N=vec.size();
    for ( int i=0; i<N-1;i++){
        if (vec[i]>vec[i+1]){
            return false;
        }
    }
    return true;
}
