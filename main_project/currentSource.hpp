#ifndef CURRENTSOURCE_HPP
#define CURRENTSOURCE_HPP

#include <vector>
#include <string>

#include "component.hpp"

class CurrentSource: public Component{
private:
    float current;
public:
    CurrentSource(string name, float _current, int n1, int n2);
    ~CurrentSource() = default;

    float getCurrent() override;
    vector<int> getNodes() override;
};

#endif