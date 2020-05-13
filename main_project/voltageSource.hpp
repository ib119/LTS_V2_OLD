#ifndef VOLTAGESOURCE_HPP
#define VOLTAGESOURCE_HPP

#include <vector>
#include <string>

#include "component.hpp"

class VoltageSource: public Component{
private:
    float voltage;
public:
    VoltageSource(string _name, vector<string> args, vector<float> extraInfo);
    VoltageSource(string _name, float _voltage, int n1, int n2);
    ~VoltageSource() = default;

    float getVoltage() const override;
    vector<int> getNodes() const override;
};

#endif