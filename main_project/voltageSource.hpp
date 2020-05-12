#ifndef VOLTAGESOURCE_HPP
#define VOLTAGESOURCE_HPP

#include <vector>
#include <string>

#include "component.hpp"

class VoltageSource: public Component{
private:
    float voltage;
public:
    VoltageSource(string name, float _voltage, int n1, int n2);
    ~VoltageSource() = default;

    float getVoltage() override;
    vector<int> getNodes() override;
};

#endif