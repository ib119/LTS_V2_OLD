#define ARMA_NO_DEBUG //makes Armadillo more efficient (disables bound-chcking, etc.)

#include <iostream>
#include <chrono> 

#include <armadillo>
#include <Eigen/Dense>
#include <Eigen/LU>
 
using namespace Eigen;
using namespace arma;
using namespace std;
using namespace std::chrono; 

/*
    This code tests the performance differences between Armadillo's and Eigen3's fastest methods
*/
int main(){
    //constructing matrices for Armadillo
    mat A1(6,6);
    A1.zeros(); //fills matrix with zeros
    //set indiviudal elements:
    A1(0,0) = 2;
    A1(0,2) = 1;
    A1(0,4) = 6;
    A1(1,1) = 5;
    A1(1,5) = 1;
    A1(2,2) = 6;
    A1(2,4) = 9;
    A1(2,5) = 5;
    A1(3,3) = 8;
    A1(3,5) = 11;
    A1(4,0) = 6;
    A1(4,2) = 9;
    A1(4,4) = 1;
    A1(5,1) = 1;
    A1(5,2) = 5;
    A1(5,3) = 11;
    A1(5,5) = 12;
    vec b1(6);
    b1(0) = 1;
    b1(1) = 2;
    b1(2) = 5;
    b1(3) = 3;
    b1(4) = 1;
    b1(5) = 2;

    vec x1(6);

    //constructing matrices for Eigen3
    //could also use A2(i,j) to initialize but method below is faster
    MatrixXd A2(6,6);
    A2 <<   2, 0, 1, 0, 6, 0,
            0, 5, 0, 0, 0, 1,
            1, 0, 6, 0, 9, 5,
            0, 0, 0, 8, 0, 11,
            6, 0, 9, 0, 1, 0,
            0, 1, 5, 11, 0, 12;

    VectorXd b2(6);
    b2 << 1, 2, 5, 3, 1, 2;
    
    VectorXd x2(6);

    //Testing fastest Armadillo method
    auto start = high_resolution_clock::now(); 
    mat P, L, U;
    lu(L, U, P, A1);
    for(long i; i < 1000000; i++){
        x1 = solve(trimatu(U), solve(trimatl(L), P * b1));
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    auto count1 = duration.count();
    cout << "Time taken by Armadillo: "
         << count1 << " microseconds" << endl; 

    //Testing fastest Eigen3 method
    start = high_resolution_clock::now();
    MatrixXd A2inv = A2.inverse();
    for (long i; i < 1000000; i++)
    {
        x2 = A2inv * b2;
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    auto count2 = duration.count();
    cout << "Time taken by Eigen3: "
         << count2 << " microseconds" << endl;

    if(count1 < count2){
        cout << "Armadillo faster" <<endl;
    }else{
        cout << "Eigen faster" <<endl;
    }

    cout << "Armadillo's x: " <<endl;
    cout << x1 <<endl <<endl;
    cout << "Eigen3's x: " << endl;
    cout << x2;
    cout << endl;
}