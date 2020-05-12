#include "component.hpp"
#include "./CustomExceptionClasses/notSupportedByComponentException.cpp"

using namespace std;

Component::Component(){};
Component::~Component() {}

// these functions should by default throw error unless overwritten by another child class down the line
// this allows to call an error if ever a function that shouldn't be returning a voltage or current or conductance
// is asked for one
float Component::getVoltage(){
    throw notSupportedByComponentException();
}

float Component::getCurrent(){
   throw notSupportedByComponentException();
}

float Component::getConductance(){
    throw notSupportedByComponentException();
}

float Component::updateVals(float v){
    throw notSupportedByComponentException();
}