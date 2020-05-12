#include <iostream>
#include <vector>
#include <memory>
#include <Eigen/Dense>

#include "component.hpp"

using namespace std;
using namespace Eigen;

class Circuit
{
private:
    vector<unique_ptr<Component>> components{}; // not sure if we necesarily need this one
    vector<unique_ptr<Component>> voltageSources{};
    vector<unique_ptr<Component>> currentSources{};
    vector<unique_ptr<Component>> cunductanceSources{};
    int highestNodeNumber; //more efficient to keep updating when parsing netlist (otherwise have to iterate through all components again)
    float time;
    float timeStep;
    bool hasNonLinear;
    MatrixXf A;
    MatrixXf A_inv;
    VectorXf b;
    VectorXf x;
public:
    // default constructor for initializing empty object
    Circuit();
    ~Circuit();

    //don't want to have default copy when using pointers (not even allowed to copy unique ptr)
    Circuit(const Circuit&) = delete;
    Circuit& operator=(const Circuit&) = delete;

    // operator overload to add ability to read from iostream to set up circuit
    void operator<<(iostream input);

    // operation to solve for a given state
    // matrix solve_for_time(float time_step);

    // operation to update circuit based on values calculated
    // void update_from_solve(float )

    // operation to create A
    void setupA();

    // operation to adjust B
    void adjustB();
};
