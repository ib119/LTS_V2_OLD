#ifndef VOLTAGESOURCE_HPP
#define VOLTAGESOURCE_HPP

#include <vector>
#include <string>

#include "component.hpp"

class VoltageSource: public Component{
private:
    int sourceType;

    //used for dc
    float voltage;

    //used for sin
    float voltageOffset, voltageAmplitude, frequency, timeDelay, dampingFactor, phase;
public:
    VoltageSource(string _name, vector<string> args, vector<float> extraInfo);
    VoltageSource(string _name, float _voltage, int n1, int n2);
    ~VoltageSource() = default;

    void setupBasic(int n1, int n2);
    void setupDC(float voltage);
    void setupSin(float startTime, float voltageOffset, float voltageAmplitude, float frequency, float timeDelay, float dampingFactor, float phase);

    float getVoltage();

    void updateVals(float time);
    void updateSinVoltage(float time);

    vector<int> getNodes() const override;
};

#endif