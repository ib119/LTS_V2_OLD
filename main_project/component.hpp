#include <vector>

using namespace std;

class Component
{
protected:
    vector<int> nodes;
    int subComponents;
public:
    Component();
    ~Component();

    virtual float getConductance(int node);
    virtual float getVoltage(int node);
    virtual float getCurrent(int node);
    // this should be used to update the value of the voltage accross a component after an iteration
    virtual float updateVals(float v);
};
