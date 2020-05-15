#include <iostream>
#include <chrono> 

#include <Eigen/Dense>
#include <Eigen/LU>
 
using namespace Eigen;
using namespace std;
using namespace std::chrono; 
 /*
    This code tests different methods from Eigen3 to solve A*x=b
    This test aims to find the most accurate/fastest equation solver for nonlinear transient analysis
    The test will operate under the conditions, that the solution must be fully recomputed at every iteration 
        (nothing like A_inv can be keept for the next iteration)
*/
int main()
{
    MatrixXd A = (MatrixXd::Random(30, 30).array() > 0.3).cast<double>() * MatrixXd::Random(30, 30).array();
    VectorXd b = VectorXd::Random(30);
    VectorXd x;

    //format for matrix printing
    //remove comments from print calls when want to compare result of different methods
    IOFormat CleanFmt(5, 0, ", ", "\n", "[", "]"); 

    //test1
    auto start = high_resolution_clock::now(); 
    for(long i{}; i < 100000; i++)
    {
        x = A.colPivHouseholderQr().solve(b);
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    auto count1 = duration.count();
    cout << "Time taken by colPivHouseholderQr: " << count1 << " microseconds" << endl; 
    
    // cout << x.format(CleanFmt) << endl << endl;


    // test2
    start = high_resolution_clock::now();
    for (long i{}; i < 100000; i++)
    {
        x = A.fullPivLu().solve(b);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    auto count2 = duration.count();
    cout << "Time taken by FullPivLU: " << count2 << " microseconds" << endl;

    // cout << x.format(CleanFmt) << endl << endl;


    // test3
    start = high_resolution_clock::now();
    for (long i{}; i < 100000; i++)
    {
        x = A.completeOrthogonalDecomposition().solve(b);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    auto count3 = duration.count();
    cout << "Time taken by CompleteOrthogonalDecomposition: " << count3 << " microseconds" << endl;
    
    // cout << x.format(CleanFmt) << endl << endl;


    // test4
    start = high_resolution_clock::now();
    for (long i{}; i < 100000; i++)
    {
        MatrixXd Ainv = A.inverse();
        x = Ainv * b;
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    auto count4 = duration.count();
    cout << "Time taken by inverse method: " << count4 << " microseconds" << endl;
    
    // cout << x.format(CleanFmt) << endl << endl;


    // test5
    start = high_resolution_clock::now();
    for (long i{}; i < 100000; i++)
    {
        FullPivLU<MatrixXd> LU(A);
        x = LU.solve(b);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    auto count5 = duration.count();
    cout << "Time taken by LU decomp: " << count5 << " microseconds" << endl;
    
    // cout << x.format(CleanFmt) << endl << endl;

    
    if (count1 < count2 && count1 < count3 && count1 < count4 && count1 < count5)
    {
        cout << "colPivHouseholderQr faster" << endl;
    }
    else if (count2 < count1 && count2 < count3 && count2 < count4 && count2 < count5)
    {
        cout << "FullPivLU faster" << endl;
    }
    else if (count3 < count1 && count3 < count2 && count3 < count4 && count3 < count5)
    {
        cout << "CompleteOrthogonalDecomposition faster" << endl;
    }
    else if (count4 < count1 && count4 < count2 && count4 < count3 && count4 < count5)
    {
        cout << "Inverse method faster" << endl;
    }
    else
    {
        cout << "LU decomp faster" << endl;
    }
    
    
}