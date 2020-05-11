#include <iostream>
#include <chrono> 

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/LU>
 
using namespace Eigen;
using namespace std;
using namespace std::chrono; 
 /*
    This code tests different methods from Eigen3 to solve A*x=b
*/
int main()
{
    MatrixXd A1 = (MatrixXd::Random(1000, 1000).array() > 0.3).cast<double>() * MatrixXd::Random(1000, 1000).array();
    SparseMatrix<double> A = A1.sparseView();
    VectorXd b = VectorXd::Random(1000);
    
    VectorXd x;
    
    auto start = high_resolution_clock::now(); 
    for(long i; i<100; i++){
        spsolve(x, A1, b, "lapack" );  // use LAPACK  solver
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    auto count1 = duration.count();
    cout << "Time taken by LAPACK: "
         << count1 << " microseconds" << endl; 
    
     = A.colPivHouseholderQr().solve(b);
}