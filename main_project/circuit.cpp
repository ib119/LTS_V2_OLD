#include <iostream>

#include "circuit.hpp"

using namespace std;

Circuit::Circuit()
{
    float time = 0;
    float timeStep = 0.1; // in seconds
}

Circuit::~Circuit()
{

}

// this should read one line of the iostream setup the proper components in the circuit and return the rest of the iostream
void Circuit::operator<<(iostream fileIn){
    string arg{};
    while(fileIn >> arg){
        // if arg = ... compare untill you reach End statement then quit loop
    }
}

// setupA definition
void Circuit::setupA(){
    
}

// setupB definition
void Circuit::adjustB(){

}