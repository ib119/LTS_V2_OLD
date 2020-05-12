#include <string>

#include "voltageSource.hpp"

VoltageSource::VoltageSource(string name, float _voltage, int n1, int n2)
    :voltage{_voltage}{

    nodes.push_back(n1);
    nodes.push_back(n2);
}

float VoltageSource::getVoltage(){
    return voltage;
}

//voltageSource is a two terminal device that has two nodes
vector<int> VoltageSource::getNodes(){
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}