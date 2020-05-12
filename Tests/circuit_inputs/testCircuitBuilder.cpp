#include <iostream>
#include <fstream>
#include <sstream>

#include "./../../main_project/circuit.hpp"
#include "./../../main_project/circuit.cpp"
#include "./../../main_project/circuitInput.cpp"

#include "./../../main_project/component.hpp"
#include "./../../main_project/component.cpp"

#include "./../../main_project/resistor.hpp"
#include "./../../main_project/resistor.cpp"

using namespace std;

int main(){
    stringstream buffer;
    buffer << "OnlyResistors" << endl;
    buffer << "R1 0 1 1" << endl;
    buffer << "R2 1 2 2" << endl;
    buffer << "R3 2 3 3" << endl;
    buffer << "r4 3 0 4" << endl;

    Circuit c{};

    if(buffer){
        c << buffer;
    }else{
        exit(1);
    }

    
}