#include <string>

#include "currentSource.hpp"

CurrentSource::CurrentSource(string name, vector<string> args)
    :Component{name}
{
    int n1 = stoi(args[0]);
    int n2 = stoi(args[1]);
    float val = getValue(args[2]);

    nodes.push_back(n1);
    nodes.push_back(n2);
    current = val;
    types.push_back(2);
}

CurrentSource::CurrentSource(string _name, float _current, int n1, int n2)
    :Component{_name}, current{_current}{

    nodes.push_back(n1);
    nodes.push_back(n2);
}

float CurrentSource::getCurrent() const{
    return current;
}

//currentSource is a two terminal device that has two nodes
vector<int> CurrentSource::getNodes() const{
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}