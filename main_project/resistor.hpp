#ifndef RESISTOR_H
#define RESISTOR_H

#include <vector>
#include <string>

#include "component.hpp"

class Resistor: public Component{
private:
    float conductance;
public:
    Resistor(string name, float r, int n1, int n2);
    ~Resistor();

    float getConductance() override;
    vector<int> getNodes() override;
};

#endif