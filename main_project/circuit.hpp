#include <iostream>
#include <vector>

#include "component.hpp"

using namespace std;

class Circuit
{
private:
    vector<Component*> components{}; // not sure if we necesarily need this one
    vector<Component*> voltageSources{};
    vector<Component*> currentSources{};
    vector<Component*> cunductanceSources{};
    // matrix A;
    // matrix A_inv or LU_decomposition;
    // matrix B;
    // matrix x;
public:
    // default constructor for initializing empty object
    Circuit();
    ~Circuit();

    // operator overload to add ability to read from iostream to set up circuit
    iostream operator<<(iostream input);

    // operation to solve for a given state
    // matrix solve_for_time(float t);

    // operation to create A
    void setupA();

    // operation to adjust B
    void adjustB();
};
