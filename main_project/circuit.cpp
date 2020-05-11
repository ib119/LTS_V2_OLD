#include <iostream>

#include "circuit.hpp"

using namespace std;

Circuit::Circuit()
{
    
}

Circuit::~Circuit()
{

}

// this should read one line of the iostream setup the proper components in the circuit and return the rest of the iostream
// function should be recursive calling itself untill fileIn can no longer be read from
// could be implemented in a different way, but I think the above is probably the best way to do this
iostream Circuit::operator<<(iostream fileIn){
    return fileIn;
}