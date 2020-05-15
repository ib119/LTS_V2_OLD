#ifndef CURRENTSOURCE_HPP
#define CURRENTSOURCE_HPP

#include <vector>
#include <string>

#include "component.hpp"
#include "waveform.hpp"

class CurrentSource: public Component{
private:
    int sourceType;

    //used for dc
    float current;

    Waveform currentWaveform{};
public:
    CurrentSource(string _name, vector<string> args, vector<float> extraInfo);
    CurrentSource(string _name, float _current, int n1, int n2);
    ~CurrentSource() = default;

    void setupBasic(int n1, int n2);
    void setupDC(float current);

    void updateVals(float time);

    float getCurrent() const override;

    vector<int> getNodes() const override;
};

#endif