#include <vector>

using namespace std;

class Component
{
protected:
    vector<int> nodes;
    int subComponents;
public:
    Component();
    virtual ~Component() = 0; //destructor of base class should be virtual (purely virtual as component should be abstract)

    //why is there a need to pass node to getter? A resistor has only one associated resistance?
    virtual float getConductance();
    virtual float getVoltage();
    virtual float getCurrent();
    
    virtual vector<int> getNodes() = 0;

    // this should be used to update the value of the voltage and current accross a component after an iteration
    virtual void updateVals(float timeStep, int order) = 0;
};
