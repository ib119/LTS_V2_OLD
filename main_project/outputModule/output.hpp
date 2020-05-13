#ifndef OUTPUTMODULE_OUTPUT_HPP
#define OUTPUTMODULE_OUTPUT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Eigen/Dense>

#include "linearAnalysis.hpp"

#include "./../circuit.hpp"
#include "./../component.hpp"

#include "./../voltageSource.hpp"
#include "./../currentSource.hpp"
#include "./../resistor.hpp"
#include "./../capacitor.hpp"
#include "./../inductor.hpp"

void outputCSV(Circuit& c, string fileName, float timeStep, float simulationTime);
void runAnalysis(Circuit& c, ofstream& outputFile, float timeStep, float simulationTime);

#endif