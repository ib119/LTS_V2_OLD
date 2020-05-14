#include <string>

#include "voltageSource.hpp"

VoltageSource::VoltageSource(string name, vector<string> args, vector<float> extraInfo)
    :Component{name}
{
    int n1 = stoi(args[0]);
    int n2 = stoi(args[1]);

    nodes.push_back(n1);
    nodes.push_back(n2);
    
    types.push_back(1);

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

VoltageSource::VoltageSource(string _name, float _voltage, int n1, int n2)
    :Component{_name}, voltage{_voltage}{

    nodes.push_back(n1);
    nodes.push_back(n2);
    types.push_back(1);
}

VoltageSource::VoltageSource(string _name, float _voltage, int n1, int n2, bool isAC)
    :Component{_name}, voltage{_voltage}{

    nodes.push_back(n1);
    nodes.push_back(n2);
    types.push_back(1);
    if(isAc) types.push_back(4);
}

float VoltageSource::getVoltage() const{
    return voltage;
}

//voltageSource is a two terminal device that has two nodes
vector<int> VoltageSource::getNodes() const{
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}