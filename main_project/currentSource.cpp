#include "currentSource.hpp"

CurrentSource::CurrentSource(float _current, int n1, int n2)
    :current{_current}{

    nodes.push_back(n1);
    nodes.push_back(n2);
}

float CurrentSource::getCurrent(int node){
    return current;
}

//currentSource is a two terminal device that has two nodes
vector<int> CurrentSource::getNodes(){
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}