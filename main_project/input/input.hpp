#ifndef INPUTMODULE_INPUT_HPP
#define INPUTMODULE_INPUT_HPP

#include <iostream>
#include <string>
#include <circuit/circuit.hpp>

using namespace std;

// this function will eventually read from file and convert to istream to pass into second overload
void readSpice(Circuit& c, string file);
// this function setsup component c from what it reads from istream
void readSpice(Circuit& c, istream& file);
// this function setsup basic variables for circuit
void setupBasic(Circuit& c, float timeStep);

#endif