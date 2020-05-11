#include <iostream>
#include <armadillo>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace arma;
/*
    This code tests different methods from Armadillo to solve A*x=b
*/
int main()
{
    sp_mat As = sprandu<sp_mat>(1000, 1000, 0.1);
    mat A = mat(As);
    vec b = randu<vec>(1000);
    // mat B = randu<mat>(1000, 5);

    vec x{};

    // test1
    auto start = high_resolution_clock::now();
    for (long i; i < 100; i++)
    {
        spsolve(x, As, b, "lapack"); // use LAPACK  solver
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    auto count1 = duration.count();
    cout << "Time taken by LAPACK: "
         << count1 << " microseconds" << endl;

    // test2
    start = high_resolution_clock::now();
    for (long i; i < 100; i++)
    {
        spsolve(x, As, b, "superlu"); // use SuperLU solver
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    auto count2 = duration.count();
    cout << "Time taken by SuperLU: "
         << count2 << " microseconds" << endl;

    // test3
    mat P, L, U;
    start = high_resolution_clock::now();
    lu(L, U, P, A);
    for (long i; i < 100; i++)
    {
        x = solve(trimatu(U), solve(trimatl(L), P * b));
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    auto count3 = duration.count();
    cout << "Time taken by LU decomp: "
         << count3 << " microseconds" << endl;

    // test4
    start = high_resolution_clock::now();
    mat AINV = A.i();
    for (long i; i < 100; i++)
    {
        x = AINV * b;
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    auto count4 = duration.count();
    cout << "Time taken by Inverse method: "
         << count4 << " microseconds" << endl;

    if (count1 < count2 && count1 < count3 && count1 < count4)
    {
        cout << "LAPACK faster" << endl;
    }
    else if (count2 < count1 && count2 < count3 && count2 < count4)
    {
        cout << "SuperLU faster" << endl;
    }
    else if (count3 < count1 && count3 < count2 && count3 < count4)
    {
        cout << "LU decomp faster" << endl;
    }
    else
    {
        cout << "Inverse method faster" << endl;
    }
}