#include <iostream>
#include <algorithm>
// VEDERE BENE
using namespace std;
template<typename T>
class unidirected_edge {
    T nodo_from;
    T nodo_to;

public:
    /* Costruttore user-defined */
    unidirected_edge(const T& n1,const T& n2)
    {
        nodo_from= min(n1,n2);
        nodo_to=max(n1,n2);
    }
// implementazione to e from
    T from() const { return nodo_from; }
    T to() const { return nodo_to; }
// implementazione operator<
    bool operator<(const unidirected_edge& other) const{
        if(nodo_from<other.nodo_from){
            return true;
        }else if ( nodo_from>other.nodo_from){
            return false;
        }else{
            if(nodo_to<other.nodo_to){
                return true;
            }else{
                return false;}
            }

        }
// implementazione operator==
    bool operator==(const unidirected_edge& other) const{
        if(nodo_from==other.nodo_from && nodo_to==other.nodo_to){
            return true;
        }else{
            return false;
        }
    
    }
};
// implementazione operator<< (operatore di stampa)
template<typename T>
ostream& operator<<(ostream& os, const unidirected_edge<T>& e)
{
    os<<"(" <<e.from()<<","<< e.to()<<")";
    return os;
}

