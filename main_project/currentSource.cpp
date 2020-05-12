#include <string>

#include "currentSource.hpp"

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