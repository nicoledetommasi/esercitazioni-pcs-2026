#include <iostream>
int main()
{
    double ad[4]={0.0,1.1,2.2,3.3};
    float af[8]={0.0,1.1,2.2,3.3,4.4,5.5,6.6,7.7};
    int ai[3]={0,1,2};


    int x=1;
    // qui inizializzo x a 1 
    float y= 1.1;
    // stampando gli indirizzi delle variabili si nota che 
    // in memoria vive prima la y e all'indirizzi successivo la x
    (&y)[1]=0; // In questo passaggio quindi io sto assegnando alla variabile 
    // che vive all'indirizzo dopo quello della y il valore 0
    // [base+i*sizeof(T) dove in questo caso la base è l'indirixxo della y, i + 1, il tipo è float
    //  quindi sizeofa(T) è 4 ]
    // Se si fa il calcolo quindi lo 0 è memorizzato nell'indirizzo dove vive la x.
    //Di conseguenza quando stampo la x mi stampa 0 e non 1 perchè è stata sovrascritta. 


    std::cout << x << "\n";
    return 0;
    
}