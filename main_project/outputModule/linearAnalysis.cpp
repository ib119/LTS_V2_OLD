#include <vector>
#include <string>

#include "linearAnalysis.hpp"

#include "./../circuit.hpp"
#include "./../component.hpp"

#include "./../voltageSource.hpp"
#include "./../currentSource.hpp"
#include "./../resistor.hpp"
#include "./../capacitor.hpp"
#include "./../inductor.hpp"


//these don't change during simulation with linear components
void linearSetup(Circuit& c){
    c.setupA();
    c.computeA_inv();
    c.setupXMeaning();
}

string runTransience(Circuit& c){
    //get references to the components stored inside the circuit
    vector<Component*> voltageSources = c.getVoltageSourcesRef();
    vector<Component*> currentSources = c.getCurrentSourcesRef();
    vector<Component*> conductanceSources = c.getConductanceSourcesRef();
    int highestNodeNumber = c.getHighestNodeNumber();

    string outLine{};
    //compute x for the current timestep
    c.computeX();
    VectorXf x = c.getX();

    //output current time 
    c.setCurrentTime(t);
    outLine += to_string(t);

    //output node voltages
    for(int i{}; i<highestNodeNumber; i++){
        outLine += "," + to_string(x(i));
    }

    //output current through resistors
    vector<int> nodes{};
    float voltage{}; 
    float current{};
    for(const auto &gs : conductanceSources){
        nodes = gs->getNodes();

        voltage = x(nodes.at(0)-1) - x(nodes.at(1)-1);
        current = voltage * gs->getConductance();

        outLine += "," + to_string(current);
    }

    //output current through voltage sources
    for(int i{}; i<voltageSources.size(); i++){
        current = x(highestNodeNumber+i);

        outLine += "," + to_string(current);
    }

    //output current through current sources
    for(const auto &cs : currentSources){
        outLine += "," + to_string(cs->getCurrent());
    }

    //update b for calculations at next timestep
    c.adjustB();

    return outLine;
}