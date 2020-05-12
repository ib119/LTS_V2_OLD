#ifndef CURRENTESOURCE_HPP
#define CURRENTESOURCE_HPP

#include <vector>

#include "component.hpp"

class CurrentSource: public Component{
private:
    float current;
public:
    CurrentSource(string _name, float _current, int n1, int n2);
    ~CurrentSource() = default;

    float getCurrent() const override;
    vector<int> getNodes() const override;
};

#endif