#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "circuit.hpp"
#include "component.hpp"

#include "voltageSource.hpp"
#include "currentSource.hpp"
#include "resistor.hpp"
#include "capacitor.hpp"
#include "inductor.hpp"

using namespace std;

void Circuit::executeTransientSimulation(string outputFileName, float _timeStep = 0.1, float _simulationTime = 10){
    //set simulation parameters
    timeStep = _timeStep;
    simulationTime = _simulationTime;

    //setup csv file
    ofstream outputFile;
    outputFile.open(outputFileName);

    //add headers to csv file
    //display time, node voltages, current through components
    outputFileName << "time";
    for(int i{1}; i<=highestNodeNumber; i++){
        outputFileName << ",v_" + to_string(i);
    }
    //conductance sources
    for(const auto &gs : conductanceSources){
        outputFileName << ",i_R" + to_string(gs->getName());
    }
    //voltage sources
    for(const auto &vs : voltageSources){
        outputFileName << ",i_V" + to_string(vs->getName());
    }
    //current sources (do we care about outputing current through current sources?)
    for(const auto &cs : currentSources){
        outputFileName << ",i_I" + to_string(cs->getName());
    }
    outputFileName << "\n";
    
    if(!hasNonLinear){
        //these don't change during simulation with linear components
        setupA();
        computeA_inv();
        setupXMeaning();

        for(u_int t{}; t<=simulationTime; t+=timeStep){
            //compute x for the current timestep
            computeX();

            //output current time 
            currentTime = t;
            outputFileName << to_string(t);

            //output node voltages
            for(int i{}; i<highestNodeNumber; i++){
                outputFileName << "," + to_string(x(i));
            }

            //output current through resistors
            vector<int> nodes{};
            float voltage{}; 
            float current{};
            for(const auto &gs : conductanceSources){
                nodes = gs->getNodes();

                voltage = x(nodes.at(0)-1) - x(nodes.at(1)-1);
                current = voltage * gs->getConductance();

                outputFileName << "," + to_string(current);
            }

            //output current through voltage sources
            for(int i{}; i<voltageSources.size(); i++){
                current = x(highestNodeNumber+i);

                outputFileName << "," + to_string(current);
            }

            //output current through current sources
            for(const auto &cs : currentSources){
                outputFileName << "," + to_string(cs->getCurrent());
            }

            //end current cvs row
            cout << "\n";

            //use current x to compute next b
            computeNextB();
        }
    }
    outputFile.close();
}