#include <string>
#include <cmath>

#include "voltageSource.hpp"

VoltageSource::VoltageSource(string name, vector<string> args, vector<float> extraInfo)
    :Component{name}
{
    int n1 = stoi(args[0]);
    int n2 = stoi(args[1]);

    setupBasic(n1, n2);

    if(args.size() == 3){
        float val = getValue(args[2]);
        voltage = val;
    }else{
        string flow = args[2];
        float val = getValue(args[3]);
        voltage = val;
        if(flow == "DC" || flow == "dc"){
            types.push_back(4);
        }
    }
}

VoltageSource::VoltageSource(string _name, float _voltage, int n1, int n2, int sourceType = sourceTypes::SIN)
    :Component{_name}{

    nodes.push_back(n1);
    nodes.push_back(n2);
    types.push_back(1);
}

void VoltageSource::setupBasic(int n1, int n2){
    nodes.push_back(n1);
    nodes.push_back(n2);
    types.push_back(1);
}

void VoltageSource::setupDC(float _voltage){
    voltage = _voltage;
    sourceType = sourceTypes::DC;
}

void VoltageSource::setupSin(float startTime, float _voltageOffset, float _voltageAmplitude, float _frequency, float _timeDelay = 0, float _dampingFactor = 0, float _phase = 0){
    voltageOffset = _voltageOffset;
    voltageAmplitude = _voltageAmplitude;
    frequency = _frequency;
    timeDelay = _timeDelay;
    dampingFactor = _phase;

    types.push_back(4);
    sourceType = sourceTypes::SIN;

    updateSinVoltage(startTime);
}

float VoltageSource::getVoltage(){
    return voltage;
}

void VoltageSource::updateVals(float time){
    switch(sourceType){
        case sourceTypes::SIN:
            updateSinVoltage(time);
            break;
        default:
            break;
    }
}

void VoltageSource::updateSinVoltage(float time){
    voltage = voltageOffset + voltageAmplitude * exp(-dampingFactor*(time - timeDelay)) * sin(2 * PI * frequency * (time - timeDelay) + (phase/360));
}

//voltageSource is a two terminal device that has two nodes
vector<int> VoltageSource::getNodes() const{
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}