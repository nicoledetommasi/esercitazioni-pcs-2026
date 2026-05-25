#include <iostream> 
#include <optional>
#include <Eigen/Dense>
#include "metodo_gradiente_coniugato.hpp"
using namespace std;
int main(int argc, char **argv){
    Eigen::MatrixXd A1(5, 5);
    A1 << 9.0, 2.0, 1.0, 1.0, 0.0,
        2.0, 8.0, 3.0, 0.0, 1.0,
        1.0, 3.0, 10.0, 2.0, 2.0,
        1.0, 0.0, 2.0, 7.0, 3.0,
        0.0, 1.0, 2.0, 3.0, 9.0;
    Eigen::VectorXd x0=Eigen::VectorXd::Zero(5);
    Eigen::VectorXd x_es=Eigen::VectorXd::Ones(5);
    Eigen::VectorXd b=A1*x_es;
// test con matrice simmetrica e definita positiva 
    cout<< "=== INIZIO TEST 1 GRADIENTE CONIUGATO: matrice valida ---"<< endl;
    cout<< "Matrice A1: \n" <<A1<< "\n"<< endl;
    cout << "termine noto b:\n"<<b<< "\n "<< endl;
    double tol= 1.0e-12;
    auto sol=pcg(A1,b,x0,tol);
    if (sol.has_value()){
        cout<< " il metodo è corretto! "<<endl;
        double errore = (sol.value() - x_es).norm() / x_es.norm();
        cout << "Errore relativo rispetto alla soluzione esatta: " << errore << endl;
    } else {
        cout << "Errore: Il solutore ha fallito inaspettatamente." << endl;
    }
    cout << "-------------------------------------------" << endl;
// test con matrice NON simmetrica
    cout << "\n=== TEST 2: Matrice NON Simmetrica ===" << endl;
    Eigen::MatrixXd A2 = A1;
    A2(0, 1) = 10.0; // Rompiamo la simmetria (A(0,1) != A(1,0))

    auto sol2 = pcg(A2, b, x0, tol);
    if (!sol2.has_value()) {
        cout << "OK: Il solutore ha rifiutato correttamente la matrice non simmetrica." << endl;
    } else {
        cout << "ERRORE: Il solutore ha accettato una matrice non simmetrica!" << endl;
    }
    cout << "-------------------------------------------" << endl;
    // test matrice NON DEF POSITIVA 
    cout << "\n=== TEST 3: Matrice NON Definita Positiva ===" << endl;
    Eigen::MatrixXd A3 = A1;
    A3(0, 0) = -5.0; // Un valore negativo sulla diagonale distrugge la definita positività

    auto sol3 = pcg(A3, b, x0, tol);
    if (!sol3.has_value()) {
        cout << "OK: Il solutore ha rifiutato correttamente la matrice non definita positiva." << endl;
    } else {
        cout << "ERRORE: Il solutore ha accettato una matrice non definita positiva!" << endl;
    }
    cout << "-------------------------------------------" << endl;
    return 0;
}