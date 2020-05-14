#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include <iostream>
#include <vector>
// #include <memory>
#include <Eigen/Dense>

#include "component.hpp"

using namespace std;
using namespace Eigen;

class Circuit
{
protected:
    string title;
    vector<Component*> components{}; // not sure if we necesarily need this one
    vector<Component*> voltageSources{};
    vector<Component*> currentSources{};
    vector<Component*> conductanceSources{};
    vector<Component*> timeUpdatables{};
    int highestNodeNumber; //more efficient to keep updating when parsing netlist (otherwise have to iterate through all components again)
    //all time is in seconds
    float currentTime;
    float simulationTime; //time when simulation ends
    float timeStep;
    bool hasNonLinear;
    MatrixXf A;
    MatrixXf A_inv;
    VectorXf b;
    VectorXf x;
    vector<string> xMeaning; // indicates what the values in x mean (need to know when outputing result)
public:
    // default constructor for initializing empty object
    Circuit();
    ~Circuit();

    //don't want to have default copy when using pointers (not even allowed to copy unique ptr)
    Circuit(const Circuit&) = delete;
    Circuit& operator=(const Circuit&) = delete;

    string getTitle() const;
    void setTitle(string _title);

    int getHighestNodeNumber() const;
    void setHighestNodeNumber(int _highestNodeNumber);

    float getCurrentTime() const;
    void setCurrentTime(float _currentTime);

    float getSimulationTime() const;
    void setSimulationTime(float _simulationTime);

    float getTimeStep() const;
    void setTimeStep(float _timeStep);

    bool hasNonLinearComponents() const;
    void setHasNonLinearComponents(bool _hasNonLinearComponents);

    // returns references to prevent inefficient copying
    vector<Component*>& getVoltageSourcesRef();
    vector<Component*>& getCurrentSourcesRef();
    vector<Component*>& getConductanceSourcesRef();

    // operator overload to add ability to read from iostream to set up circuit
    void operator<<(istream& input);

    // template function to add component, the class must have a constructor with the intputs as in the function bellow
    template <class comp>
    void addComponent(string name, vector<string> args);

    // update components that nead updating
    void updateComponents(float time);

    // operation to create A
    void setupA();
    MatrixXf getA() const;

    // compute inverse of A
    void computeA_inv();
    MatrixXf getA_inv() const;

    // operation to adjust B
    void adjustB();
    VectorXf getB() const;

    // operation to assign meaning to the result vector x
    void setupXMeaning();
    vector<string> getXMeaning() const;

    // A_inv must exist for this to work
    void computeX();
    VectorXf getX() const;
};

#endif