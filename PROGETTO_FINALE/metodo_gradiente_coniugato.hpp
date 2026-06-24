#pragma once
#include <iostream> 
#include "Eigen/Eigen"
#include <optional>
#include <Eigen/Dense>
using namespace std;

optional<Eigen::VectorXd> pcg(const Eigen::MatrixXd& A, const Eigen::VectorXd& b,Eigen::VectorXd& x0, const double& tol){
    // faccio i check sulla matrice per vedere se è simmatrica
    if(A.rows()!= A.cols()){
        cerr<< "errore: la matrice non è quadrata! Dimensioni: "<< A.rows()<<"x"<< A.cols()<< endl;
        return nullopt;
    }
    if(!A.isApprox(A.transpose(),1e-12)){
        cerr<< "errore: la matrice A non è simmetrica!"<<endl;
        return nullopt;
    }
    // faccio il check per vedere se è definita positiva
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(A);
    auto autovalori=solver.eigenvalues();
    if (autovalori.minCoeff()<tol){
        cout<< "La matrice non è definita positiva"<<endl;
        return nullopt;
    }
    Eigen::VectorXd r0 = b-A*x0;
    Eigen::VectorXd p0=r0;
    double res_tol=1.0e-15;
    double r0_norm=r0.norm();
    double k=0;
    
    while ( k<A.rows() && r0.norm()>res_tol*r0_norm){
        Eigen::VectorXd Ap=A*p0;
        const double alpha_k=p0.dot(r0)/p0.dot(Ap);
        x0 = x0 + alpha_k*p0;
        r0=b-A*x0;
        Eigen::VectorXd Ar0 = A * r0; 
        double beta_k = p0.dot(Ar0) / p0.dot(Ap);
        p0= r0 - beta_k*p0;
        k++;
    }
    return x0;
}

