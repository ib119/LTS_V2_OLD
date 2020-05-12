#ifndef VOLTAGESOURCE_HPP
#define VOLTAGESOURCE_HPP

#include <vector>

#include "component.hpp"

class VoltageSource: public Component{
private:
    float voltage;
public:
    VoltageSource(float _voltage, int n1, int n2);
    ~VoltageSource() = default;

    float getVoltage() override;
    vector<int> getNodes() override;
};

#endif