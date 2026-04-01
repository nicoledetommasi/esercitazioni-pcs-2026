
#include <concepts>
#include<iostream>
#include <numeric>
#pragma once 
template<typename T>  requires std::integral<T> 

class rational {   
    T num_;
    T den_;


    // semplificazione 
    void semplificazione(){
        if (den_==0) return; // se ho Inf o NaN vai avanti non fare la semplificazione 
        T Mcd=std::gcd(num_,den_);
        num_=num_/Mcd;
        den_=den_/Mcd;
        if (den_<0){        //se la frazione è negativa poichè il denominatore è negativa sposto il meno davanti alla frazione 
            num_=-num_;
            den_=-den_;
        }

    }
public:
     /* Costruttore di default */
    rational()
        : num_(T{0}), den_(T{1})  
    {}
    /* Costruttore user-defined (secondo punto)*/
    rational(const T& pnum, const T& pden)
        : num_(pnum), den_(pden)    
    {
        if (den_==0 && num_!=0){    // definisco l'Inf
            num_=1; // definisco valori sentinella
        } else if (den_==0 && num_==0){ // definisco il NaN
            num_=0;
            den_=0;
        }
       semplificazione();
    }



    /* Restituiscono i valori di numeratore e denominatore (terzo punto)*/ 
    T num() const { return num_; }
    T den() const { return den_; }

    /* Implementazione operazione += */
   rational& operator+=(const rational& other){
        if ((den_==0 && num_==1)|| (other.num_==1 && other.den_ == 0)){
            num_=1;     //se uno dei due addendi è Inf allora il risultato è Inf
            den_=0;
        }
        else if ((den_==0 && num_==0)|| (other.den_ == 0 && other.num_ == 0)){
            num_=0;     //se uno dei due addendi è NaN allora il risultato è NaN
            den_=0;
        }
        else if ((den_==0 && num_==1) && (other.num_==1 && other.den_ == 0)){
            num_=0;
            den_=0;     //caso inf+inf=NaN
        }
        else { // addizione normale 
            num_=(num_*other.den_)+(other.num_*den_);
            den_=(den_*other.den_);
        }
        semplificazione(); 
        return *this;
    }
    /* Implementazione della somma + */
    rational operator+(const rational& other) const {
        rational ret = *this;
        ret += other;
        return ret; 
    }
    /* Implementazione operazione -= */
    rational& operator-=(const rational& other) {
        if ((den_ ==0 && num_!=0) || (other.den_==0 && other.num_==1 )){
            num_=1;     //Inf-numero=Inf
            den_=0;
        } else if ((den_==0 && num_==0) ||( other.den_==0 && other.num_==0)){
            num_=0;     //NaN-numero=NaN
            den_=0;
        } else { // differenza tra frazioni canonica 
            num_=(num_*other.den_)-(den_*other.num_);
            den_=(den_*other.den_);
        } 
        semplificazione();
        return *this;
    }
    /* Implementazione della differenza - */
    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other;
        return ret; 
    }
    
    /* Implementazione operazione *= */
    rational& operator*=(const rational& other) {
        if ((den_ ==0 && num_!=0) || (other.den_==0 && other.num_==1) ){
            num_=1;     // Inf * Inf =Inf
            den_=0;
        } else if ((den_==0 && num_==0) || (other.den_==0 && other.num_==0)){
            num_=0;     //Nan *NaN =NaN
            den_=0;
        } 
        else if ((den_==0 && num_==1) && (other.num_!=1 && other.num_!=0 && other.den_!=0)) {
            num_=1;         //Inf * numero = Inf 
            den_=0;
        }
        else { // moltiplicazione tra frazioni canonica 
            num_=(num_*other.num_);
            den_=(den_*other.den_);
        } 
        semplificazione();
        return *this;
    }
    /* Implementazione della moltiplicazione * */
    rational operator*(const rational& other) const {
        rational ret = *this;
        ret *= other;
        return ret; 
    }

    /* Implementazione operazione /= */
    rational& operator/=(const rational& other) {
        if ((den_ ==0 && num_==1) ||(other.den_==0 && other.num_==1)){
            num_=0;     //tratto l'inf/numero =NaN
            den_=0;
        } else if ((den_==0 && num_==0) || (other.den_==0 && other.num_==0)){
            num_=0;     //tratto il NaN/NaN=NaN
            den_=0;
        } 
        else if (( den_==0 && num_==1) && ( other.num_!=1 && other.den_!=0  && other.num_!=0)){
            num_=1;     // Inf/numero =Inf
            den_=0;
        }
        else if ((num_!=1 && num_!=0 && den_!=0)&&(other.num_==0 && other.den_==0)){
            num_=1;     //numero/NaN = Inf
            den_=0;
        }
        else { // divisione tra frazioni canonica 
            num_=(num_*other.den_);
            den_=(den_*other.num_);
        } 
        semplificazione();
        return *this;
    }
    /* Implementazione del rapporto */
    rational operator/(const rational& other) const {
        rational ret = *this;
        ret /= other;
        return ret; 
    }
    // semplificatori 
};


// quarto punto: definisco l'operatore di stampa
template<typename T>
std::ostream&
operator<<(std::ostream& os, const rational<T>& r)
{
    os << r.num() << "/" << r.den();
    return os;
}