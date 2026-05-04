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
    for (int j=1; j<N; j++) {
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

// merge
template<typename T>
void merge(std::vector<T>& vec, int p,int q, int r){
    int i,j,k;
    int n1=q-p+1;
    int n2=r-q;
    std::vector<T> L(n1);
    std::vector<T> R(n2);
    for (i=0; i<n1; i++){
        L[i]=vec[p+i];
    }
    for ( j=0; j<n2; j++){
        R[j]=vec[q+1+j];
    }
    i=0; 
    j=0;
    k=p;
    while(i<n1 &&j<n2){
        if(L[i]<=R[j]){
            vec[k]=L[i];
            i++;
        }
        else{
            vec[k]=R[j];
            j++;
        }
        k++;
    }
    while (i<n1){
        vec[k]=L[i];
        i++;
        k++;
    }
    while (j<n2){
        vec[k]=R[j];
        j++;
        k++;
    }
    return;
}


//mergesort
template<typename T>
void merge_sort(std::vector<T>& vec, int p, int r){
    if (p<r){
        int q=p+(r-p)/2;
        merge_sort(vec,p,q);
        merge_sort(vec,q+1,r);
        merge(vec,p,q,r);
    }
    return;
}


template<typename T>
int partition(std::vector<T>& vec, int p,int r){
    T x=vec[r];
    int i=p-1;
    for (int j=p;j<=r-1; j++){
        if (vec[j]<=x){
            i=i+1;
            std::swap(vec[i],vec[j]);
        }
    }
    std::swap(vec[i+1],vec[r]);
    return i+1;
}

// quicksort
template<typename T>
void quick_sort(std::vector<T>& vec, int p, int r){
    if (p<r){
        int q=partition(vec,p,r);
        quick_sort(vec,p,q-1);
        quick_sort(vec,q+1,r);
    }
    return;
}

template <typename T>
void insertion_sort_hybrid(std::vector <T> & vec, int p, int n)
{
    for(int i= p + 1; i <= n; i++)
    {
        T val = vec[i];
        int j = i;
        while (j > p && vec[j-1]>val)
        {
            vec[j] = vec[j-1];
            j-=1;
        }
        vec[j] = val;
    }

}
template <typename T>
int partition_hybrid(std::vector <T> & vec, int p, int r)
{
    int pivot = vec[r];
    int j = p;

    for (int i = p; i < r; i ++)
    {
        if(vec[i]<pivot)
        {
            int temp = vec[i];
        vec[i] = vec[j];
        vec[j]=temp;
        j += 1;
        }
    }

    int temp = vec[j];
    vec[j] = vec[r];
    vec[r] = temp;

return j; 
}

//Ottimizzo il Quicksort classico
template <typename T>
void hybrid_quick_sort(std::vector <T> & vec, int p, int r)
{
    while (p < r)
    {
        if(r - p + 1 < 10)
        {
            insertion_sort_hybrid(vec, p, r);
            break;
        }
        else{
            int pivot = partition(vec,p,r);
            if (pivot-p < r - pivot)
            {
            hybrid_quick_sort(vec,p, pivot - 1);
            p = pivot + 1;
            }
    else {
        hybrid_quick_sort(vec,pivot + 1, r);
        r = pivot - 1;
        }
        }
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
