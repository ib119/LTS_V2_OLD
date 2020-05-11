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
    float time;
    float timeStep;
    MatrixXd A;
    MatrixXd A_inv;
    VectorXd b;
    VectorXd x;
public:
    // default constructor for initializing empty object
    Circuit();
    ~Circuit();

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
