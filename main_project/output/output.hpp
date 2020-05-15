#ifndef OUTPUTMODULE_OUTPUT_HPP
#define OUTPUTMODULE_OUTPUT_HPP

#include <string>
#include <iostream>
#include <circuit/circuit.hpp>

void outputCSV(Circuit& c, string fileName, float timeStep, float simulationTime);
void runAnalysis(Circuit& c, ofstream& outputFile, float timeStep, float simulationTime);

#endif