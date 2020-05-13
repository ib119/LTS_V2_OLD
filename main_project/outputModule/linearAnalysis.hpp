#ifndef OUTPUTMODULE_LINEARANALYSIS_HPP
#define OUTPUTMODULE_LINEARANALYSIS_HPP

#include <string>

#include "./../circuit.hpp"
#include "./../component.hpp"

#include "./../voltageSource.hpp"
#include "./../currentSource.hpp"
#include "./../resistor.hpp"
#include "./../capacitor.hpp"
#include "./../inductor.hpp"

void linearSetup(Circuit& c);
string runLinearTransience(Circuit& c, float t);

#endif