#include <string>

#include "voltageSource.hpp"

VoltageSource::VoltageSource(string name, vector<string> args)
    :Component{name}
{
    int n1 = stoi(args[0]);
    int n2 = stoi(args[1]);
    float val = getValue(args[2]);

    nodes.push_back(n1);
    nodes.push_back(n2);
    voltage = val;
    types.push_back(1);
}

VoltageSource::VoltageSource(string _name, float _voltage, int n1, int n2)
    :Component{_name}, voltage{_voltage}{

    nodes.push_back(n1);
    nodes.push_back(n2);
}

float VoltageSource::getVoltage() const{
    return voltage;
}

//voltageSource is a two terminal device that has two nodes
vector<int> VoltageSource::getNodes() const{
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}