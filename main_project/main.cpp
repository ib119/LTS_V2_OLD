#include <iostream>
#include <vector>
#include <fstream>

#include "circuit.hpp"

// for debugging only
#include "circuit.cpp"
#include "component.cpp"
#include "resistor.cpp"
#include "voltageSource.cpp"
#include "currentSource.cpp"
#include "capacitor.cpp"
#include "inductor.cpp"

#include "inputModule/input.hpp"
#include "outputModule/output.hpp"
#include "outputModule/linearAnalysis.hpp"

// for debugging only
#include "inputModule/input.cpp"
#include "outputModule/output.cpp"
#include "outputModule/linearAnalysis.cpp"

using namespace std;

// for debugging only
void exampleCircuit7(stringstream& buffer){
    buffer << "ExampleCircuit1" << endl;
    buffer << "I1 1 0 10" << endl;
    buffer << "R1 1 0 1" << endl;
    buffer << "C1 2 0 0.00001" << endl;
    buffer << "R2 2 0 100000" << endl;
    buffer << "R3 1 2 1000" << endl;
}

void exampleCircuit6(stringstream& buffer){
    buffer << "ExampleCircuit1" << endl;
    buffer << "V1 1 0 10" << endl;
    buffer << "R1 1 2 10000" << endl;
    buffer << "C1 2 0 0.000001" << endl;
}

int main(int argc, char **argv){
    //get optional input arguments
    string outputFileName = "out.csv";
    float timeStep = 0.01; //seconds
    float simulationTime = 0.25; //seconds
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
    setupBasic(c, timeStep);
    // readSpice(c, cin);

    // debugging only
    stringstream buffer;
    exampleCircuit6(buffer);
    readSpice(c, buffer);

    // run simulation
    outputCSV(c, outputFileName, timeStep, simulationTime);
}


