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
        setupDC(val);
    }else{
        string flow = args[2];
        if(flow == "DC" || flow == "dc"){
            setupDC(
                getValue(args[3]) // voltage
            );
        }else if(flow.size() > 4){ //checks if "flow" is long enough to be SIN(* where * is any character
            if(flow.substr(0,4) == "SIN(" || flow.substr(0,4) == "sin("){
                switch (args.size()) // switch statment depending on how many arguments were given as some are not required
                {
                case 5:
                    setupSin(
                        extraInfo[1], // start time
                        getValue(flow.substr(4, flow.size()-4)), // voltage offset
                        getValue(args[3]), // voltage amplitude
                        getValue(args[4].substr(0,args[4].size()-1)) // frequency
                    );
                    break;
                case 6:
                    setupSin(
                        extraInfo[1], // start time
                        getValue(flow.substr(4, flow.size()-4)), // voltage offset
                        getValue(args[3]), // voltage amplitude
                        getValue(args[4]), // frequency
                        getValue(args[5].substr(0,args[5].size()-1)) // time delay
                    );
                    break;
                case 7:
                    setupSin(
                        extraInfo[1], // start time
                        getValue(flow.substr(4, flow.size()-4)), // voltage offset
                        getValue(args[3]), // voltage amplitude
                        getValue(args[4]), // frequency
                        getValue(args[5]), // time delay
                        getValue(args[6].substr(0,args[6].size()-1)) // damping factor
                    );
                    break;
                case 8:
                    setupSin(
                        extraInfo[1], // start time
                        getValue(flow.substr(4, flow.size()-4)), // voltage offset
                        getValue(args[3]), // voltage amplitude
                        getValue(args[4]), // frequency
                        getValue(args[5]), // time delay
                        getValue(args[6]), // damping factor
                        getValue(args[7].substr(0,args[7].size()-1)) // phase
                    );
                    break;
                default:
                    cerr << "not enough arguments given for SIN voltage input" << endl;
                    exit(1);
                    break;
                }
                
            }
        }
    }
}

VoltageSource::VoltageSource(string _name, float _voltage, int n1, int n2)
    :Component{_name}{
    setupBasic(n1, n2);
    setupDC(_voltage);
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