#include <string>
#include <vector>

#include "resistor.hpp"

Resistor::Resistor(string name, vector<string> args, vector<float> extraInfo)
    :Component{name}
{
    int n1 = stoi(args[0]);
    int n2 = stoi(args[1]);
    float val = getValue(args[2]);

    nodes.push_back(n1);
    nodes.push_back(n2);
    conductance = 1/val;
    types.push_back(0);
}

Resistor::Resistor(string _name, float r, int n1, int n2)
    :Component{_name}, conductance{1/r}{

    nodes.push_back(n1);
    nodes.push_back(n2);
}

float Resistor::getConductance() const{
    return conductance;
}

//resistor is a two terminal device that has two nodes
vector<int> Resistor::getNodes() const{
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}