#ifndef WAVEFORM_HPP
#define WAVEFORM_HPP

#include <cmath>
#include <vector>
#include <string>

#include "component.hpp"
#include "enums.hpp"

using namespace std;

class Waveform{
private:
    // just for convenience
    const double PI = 3.1415926535897;

    // important
    enum::sourceTypes sourceType;

    //used for sin
    float offset, amplitude, frequency, timeDelay, dampingFactor, phase;
    
    void setupSin(float startTime, float _voltageOffset, float _voltageAmplitude, float _frequency, float _timeDelay, float _dampingFactor, float _phase);
    float updateSinVals(float time);

public:
    void setupWaveform(const Component* comp, vector<string> args, vector<float> extraInfo);

    float updateVals(float time);
};

#endif