#include <iostream>
#include <string>
#include <vector>

#include "circuit.hpp"
#include "component.hpp"

#include "voltageSource.hpp"
#include "currentSource.hpp"
#include "resistor.hpp"
#include "capacitor.hpp"
#include "inductor.hpp"

using namespace std;

// this should read one line of the iostream setup the proper components in the circuit and return the rest of the iostream
void Circuit::operator<<(iostream& file){
    getline(file, title);
    string arg{};

    Component* newComp{};
    string compType{};
    while(file >> arg){
        compType = arg[0];
        if(compType == "R" || compType == "r"){
            newComp = setUpResistor(arg, file);
            conductanceSources.push_back(newComp);
        }
        components.push_back(newComp);
        // if arg = ... compare untill you reach End statement then quit loop
    }
}

// helper function to parse string with units into float
float Circuit::getValue(string val){
    return 1;
}

// helper function to setup up resistor from specific inputs
Resistor* Circuit::setUpResistor(string arg, iostream& file){
    string name = arg.substr(1, arg.size()-1);
    file >> arg;
    int n1 = stoi(arg);
    file >> arg;
    int n2 = stoi(arg);
    file >> arg;
    float val = getValue(arg);
    return new Resistor(name, val, n1, n2);
}