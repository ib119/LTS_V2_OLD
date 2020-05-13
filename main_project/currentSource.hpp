#ifndef CURRENTSOURCE_HPP
#define CURRENTSOURCE_HPP

#include <vector>
#include <string>

#include "component.hpp"

class CurrentSource: public Component{
private:
    float current;
public:
    CurrentSource(string _name, vector<string> args);
    CurrentSource(string _name, float _current, int n1, int n2);
    ~CurrentSource() = default;

    float getCurrent() const override;
    vector<int> getNodes() const override;
};

#endif