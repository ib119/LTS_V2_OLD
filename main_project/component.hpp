#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <vector>
#include <string>

#include "enums.hpp"

using namespace std;

namespace sourceTypes
{
    enum{
        DC = 0,
        SIN = 1
    };
};

class Component
{
protected:
    string name;
    vector<int> nodes;
    vector<componentType> types; //indicates functionality of subComponents
    int subComponents;

    // just for convenience
    const double PI = 3.1415926535897;
public:
    Component(string _name);
    virtual ~Component() = 0; //destructor of base class should be virtual (purely virtual as component should be abstract)

    //why is there a need to pass node to getter? A resistor has only one associated resistance?
    virtual float getConductance() const;
    virtual float getVoltage() const;
    virtual float getCurrent() const;
    
    string getName() const;
    virtual vector<int> getNodes() const = 0;


    // this should be used to update the value of the voltage and current accross a component after an iteration
    virtual void updateVals(float newVoltage, float newCurrent, int order);
    // this should ebe used to update the time of the time dependant components
    virtual void updateVals(float time);

    float getValue(string val);
    vector<componentType> getTypes() const;
};

#endif
