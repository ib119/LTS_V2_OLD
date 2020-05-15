#include <string>
#include <vector>

#include "currentSource.hpp"

CurrentSource::CurrentSource(string name, vector<string> args, vector<float> extraInfo)
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
                getValue(args[3]) // current
            );
        }else if(flow.size() > 4){ //checks if "flow" is long enough to be SIN(* where * is any character
            currentWaveform.setupWaveform(this, args, extraInfo);
            types.push_back(componentType::timeUpdatable);
        }
    }
}

CurrentSource::CurrentSource(string _name, float _current, int n1, int n2)
    :Component{_name}{
    setupBasic(n1, n2);
    setupDC(_current);
}

void CurrentSource::setupBasic(int n1, int n2){
    nodes.push_back(n1);
    nodes.push_back(n2);
    types.push_back(componentType::currentSource);
}

void CurrentSource::setupDC(float _current){
    current = _current;
}

float CurrentSource::getCurrent() const{
    return current;
}

void CurrentSource::updateVals(float time){
    current = currentWaveform.updateVals(time);
}

//currentSource is a two terminal device that has two nodes
vector<int> CurrentSource::getNodes() const{
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}