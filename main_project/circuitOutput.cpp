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

void Circuit::executeTransientSimulation(string outputFileName, float _timeStep, float _simulationTime){
    //set simulation parameters
    timeStep = _timeStep;
    simulationTime = _simulationTime;

    //setup csv file
    ofstream outputFile;
    outputFile.open(outputFileName);

    //add headers to csv file
    //display time, node voltages, current through components
    outputFile << "time";
    for(int i{1}; i<=highestNodeNumber; i++){
        outputFile << ",v_" + to_string(i);
    }
    //conductance sources
    for(const auto &gs : conductanceSources){
        outputFile << ",i_R" + gs->getName();
    }
    //voltage sources
    for(const auto &vs : voltageSources){
        outputFile << ",i_V" + vs->getName();
    }
    //current sources (do we care about outputing current through current sources?)
    for(const auto &cs : currentSources){
        outputFile << ",i_I" + cs->getName();
    }
    outputFile << "\n";
    
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
            outputFile << to_string(t);

            //output node voltages
            for(int i{}; i<highestNodeNumber; i++){
                outputFile << "," + to_string(x(i));
            }

            //output current through resistors
            vector<int> nodes{};
            float voltage{}; 
            float current{};
            for(const auto &gs : conductanceSources){
                nodes = gs->getNodes();

                voltage = x(nodes.at(0)-1) - x(nodes.at(1)-1);
                current = voltage * gs->getConductance();

                outputFile << "," + to_string(current);
            }

            //output current through voltage sources
            for(int i{}; i<voltageSources.size(); i++){
                current = x(highestNodeNumber+i);

                outputFile << "," + to_string(current);
            }

            //output current through current sources
            for(const auto &cs : currentSources){
                outputFile << "," + to_string(cs->getCurrent());
            }

            //end current cvs row
            cout << "\n";

            //use current x to compute next b
            computeNextB();
        }
    }
    outputFile.close();
}