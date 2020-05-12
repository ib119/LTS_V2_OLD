#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

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
    string title;
    vector<Component*> components{}; // not sure if we necesarily need this one
    vector<Component*> voltageSources{};
    vector<Component*> currentSources{};
    vector<Component*> conductanceSources{};
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
    void operator<<(iostream& input);
    // input helper functions
    float getValue(string val);
    Component* setUpResistor(string arg, iostream& file);

    // operation to solve for a given state
    // matrix solve_for_time(float time_step);

    // operation to update circuit based on values calculated
    // void update_from_solve(float )

    // operation to create A
    void setupA();

    // operation to adjust B
    void adjustB();
};

#endif