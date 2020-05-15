#ifndef OUTPUTMODULE_LINEARANALYSIS_HPP
#define OUTPUTMODULE_LINEARANALYSIS_HPP

#include <string>
#include <circuit/circuit.hpp>

void linearSetup(Circuit& c);
string runLinearTransience(Circuit& c, float t);

#endif