#include <iostream>
#include <algorithm>
#include <cmath>
int main()
{
    static const int N=5;
    double arr[N]={3.9,1.3,4.1,6.9,5.4};
    // CALCOLO LA MEDIA 
    double somma=0.0;
    for (int i=0; i<N; i++){
        somma=somma+arr[i];
    }
    double media=somma/N;
    std::cout << "La MEDIA è: "<< media<< "\n";
    // CALCOLO IL MIN E IL MASSIMO 
    // calcolo con le funzioni 
    double min =arr[0];
    double max=arr[0];
    // for (int i=1; i<N;i++){
    //     max=std::max(max,arr[i]);
    //     min=std::min(min,arr[i]);
    // }
    // calcolo manualmente
    for (int i=1; i<N;i++){
        if (arr[i]>=max){
           max=arr[i];  
        }
    }
    for (int i=1; i<N;i++){
        if (arr[i]<=min){
           min=arr[i];  
        }
        }

    std::cout<< "Il MINIMO è: "<< min <<"\n";
    std::cout<< "Il MASSIMO è: "<< max <<"\n";
    // calcolo la deviazione standard
    double differenza=0.0;
    double quadrato=0.0;
    double s=0.0;
    for (int i=0;i<N;i++){
        differenza=arr[i]-media;
        quadrato= differenza*differenza;
        s=s+quadrato;
    
    }
    double rapporto=s/N;
    double dev=sqrt(rapporto);
    std::cout<< "la DEVIAZIONE STANDARD è: "<< dev<<"\n";
    return 0;
}



