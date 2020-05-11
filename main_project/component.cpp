#include "component.hpp"

// these functions should by default return null unless overwritten by another child class down the line
// this allows to call an error if ever a function that shouldn't be returning a voltage or current or conductance
// is asked for one
// could replace null with exit() or something
float Component::getVoltage(int node){
    return NULL;
}

float Component::getCurrent(int node){
    return NULL
}

float Component::getConductance(int node){
    return NULL
}