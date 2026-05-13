#include "unidirected_edge.hpp"
#include <iostream>
using namespace std;
int main() {
    unidirected_edge<int> arco1(9,4);
    unidirected_edge<int> arco2(4,9);
    // verifico se l'arco è stampato come: numero minore,maggiore
    cout << "Arco 1 (9,4): " << arco1 << endl; // Deve stampare (4,9)
    cout << "Arco 2 (4,9): " << arco2 << endl; // Deve stampare (4,9)
    // verifico se l'operatore di uguaglianza funziona (operator==)
    if (arco1==arco2){
        cout<< "L'operatore di uguaglianza funziona (archi speculari sono uguali)"<<endl;
    }else{
        cout<< "ERRORE: l'arco NON è ordinato bene"<<endl;
    }
    //verifico l'operator<
    unidirected_edge<int> arco3(1,12);
    unidirected_edge<int> arco4(4,5);
    cout << "Arco 3 (1,12): " << arco1 << endl; // Deve stampare (4,9)
    cout << "Arco 4 (4,5): " << arco2 << endl;
    if (arco3<arco1){
        cout<<arco3<<"viene prima di "<<arco1<<"(1<4)"<<endl;
    }else{
        cout<<"L'Arco 3"<<arco3<< "è maggiore dell'arco1"<<arco1<<endl;
    }
    if (arco4<arco2){
        cout<<"L'Arco 4 viene prima dell'arco2 (4==4 e 5<9)"<<endl;
    }else{
        cout<<"L'Arco 4 non viene prima dell'arco2 (4==4 ma 5<9)"<<endl;
    }

    return 0;
}