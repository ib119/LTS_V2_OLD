#ifndef RESISTOR_HPP
#define RESISTOR_HPP

#include <vector>
#include <string>

#include "component.hpp"

class Resistor: public Component{
private:
    float conductance;
public:
    Resistor(string _name, float r, int n1, int n2);
    ~Resistor() = default;

    float getConductance() const override;
    vector<int> getNodes() const override;
};

#endif