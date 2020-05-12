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
    virtual float getConductance(int node);
    virtual float getVoltage(int node);
    virtual float getCurrent(int node);
    
    virtual vector<int> getNodes() = 0;

    // this should be used to update the value of the voltage accross a component after an iteration
    virtual float updateVals(float v);
};
