#include <vector>

class Component
{
private:
    vector<int> nodes;
    int subComponents;
public:
    Component();
    ~Component();

    virtual float getConductance();
    virtual float getVoltage();
    virtual float getCurrent();
    // this should be used to update the value of the voltage accross a component after an iteration
    virtual float updateVals(float v);
};
