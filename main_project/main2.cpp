#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Eigen/Dense>

#include "circuit.hpp"
#include "component.hpp"

#include "voltageSource.hpp"
#include "currentSource.hpp"
#include "resistor.hpp"
#include "capacitor.hpp"
#include "inductor.hpp"

using namespace std;
using namespace Eigen;

/*
    Optional input arguments:
    1.) outputFileName
    2.) timeStep
    3.) simulationTime (after what time in seconds the simulation should finish)
*/
int main(int argc, char **argv){
    //get optional input arguments
    string outputFileName = "out.csv";
    float timeStep = 0.1; //seconds
    float simulationTime = 10; //seconds
    if(argc > 1){
        outputFileName = argv[1];
    }
    if(argc > 2){
        timeStep = (float)atof(argv[2]);
    }
    if(argc > 3){
        simulationTime = (float)atof(argv[3]);
    }

    //circuit object (constructed at input part of this program)
    Circuit circuit{};

    //get references to the components stored inside the circuit
    vector<Component*> voltageSources = circuit.getVoltageSourcesRef();
    vector<Component*> currentSources = circuit.getCurrentSourcesRef();
    vector<Component*> conductanceSources = circuit.getConductanceSourcesRef();

    //setup csv file
    ofstream outputFile;
    outputFile.open(outputFileName);

    //add headers to csv file
    //display time, node voltages, current through components
    outputFile << "time";
    int highestNodeNumber = circuit.getHighestNodeNumber();
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
    
    if(!circuit.hasNonLinearComponents()){
        //these don't change during simulation with linear components
        circuit.setupA();
        circuit.computeA_inv();
        circuit.setupXMeaning();

        float simulationTime = circuit.getSimulationTime();
        float timeStep = circuit.getTimeStep();
        for(u_int t{}; t<=simulationTime; t+=timeStep){
            //compute x for the current timestep
            circuit.computeX();
            VectorXf x = circuit.getX();

            //output current time 
            circuit.setCurrentTime(t);
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
            outputFile << "\n";

            //update b for calculations at next timestep
            circuit.adjustB();
        }
    }
    outputFile.close();
}