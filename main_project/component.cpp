#include "component.hpp"

using namespace std;

Component::Component(){};
Component::~Component() {}

// these functions should by default return null unless overwritten by another child class down the line
// this allows to call an error if ever a function that shouldn't be returning a voltage or current or conductance
// is asked for one
// could replace null with exit() or something
float Component::getVoltage(){
    return NULL; 
    //what about throwing an error and executing code in try catch statement instead of returning NULL (defensive programming)?
    //if we don't catch the error, the program terminates and the user sees the error message (custom error object derived from error inheritance tree)
    //=> could be desired behaviour if receive invalid input or otherwise
}

float Component::getCurrent(){
    return NULL;
}

float Component::getConductance(){
    return NULL;
}

float Component::updateVals(float v){
    return NULL;
}