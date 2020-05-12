#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <vector>
#include <string>

using namespace std;

class Component
{
protected:
    string name;
    vector<int> nodes;
    int subComponents;
public:
    Component(string _name);
    virtual ~Component() = 0; //destructor of base class should be virtual (purely virtual as component should be abstract)

    //why is there a need to pass node to getter? A resistor has only one associated resistance?
    virtual float getConductance() const;
    virtual float getVoltage() const;
    virtual float getCurrent() const;
    
    virtual vector<int> getNodes() const = 0;

    // this should be used to update the value of the voltage accross a component after an iteration
    virtual float updateVals(float v);
};

#endif