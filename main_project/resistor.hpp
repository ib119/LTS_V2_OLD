#include <vector>

#include "component.hpp"

class Resistor: public Component{
private:
    float conductance;
public:
    Resistor(float r, int n1, int n2);
    ~Resistor();

    float getConductance() override;
    vector<int> getNodes() override;
};