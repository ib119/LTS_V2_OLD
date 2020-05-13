#include <iostream>
#include <Eigen>
#include <vector>
#include <fstream>

#include "circuit.hpp"
#include "component.hpp"
#include "resistor.hpp"
#include "voltageSource.hpp"
#include "currentSource.hpp"
#include "capacitor.hpp"
#include "inductor.hpp"

#include "inputModule/input.hpp"
#include "outputModule/output.hpp"

using namespace std;

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
    
    // setup circuit
    Circuit c{};
    readSpice(c, cin);

    // run simulation
    outputCSV(c, outputFileName, timeStep, simulationTime);
}

