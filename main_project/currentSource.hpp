#include <vector>

#include "component.hpp"

class CurrentSource: public Component{
private:
    float current;
public:
    CurrentSource(float _current, int n1, int n2);
    ~CurrentSource() = default;

    float getCurrent(int node) override;
    vector<int> getNodes() override;
};