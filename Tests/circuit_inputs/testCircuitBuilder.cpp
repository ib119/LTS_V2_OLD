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

#include "./../../main_project/currentSource.hpp"
#include "./../../main_project/currentSource.cpp"

#include "./../../main_project/voltageSource.hpp"
#include "./../../main_project/voltageSource.cpp"

using namespace std;

void onlyResistors(stringstream& buffer){
    buffer << "OnlyResistors" << endl;
    buffer << "R1 0 1 1" << endl;
    buffer << "R2 1 2 2" << endl;
    buffer << "R3 2 3 3" << endl;
    buffer << "r4 3 0 4" << endl;
}

// obviously going to spount nonsne since this circuit makes no sense
void onlyVoltageSources(stringstream& buffer){
    buffer << "OnlyResistors" << endl;
    buffer << "V1 0 1 1" << endl;
    buffer << "V2 1 2 2" << endl;
    buffer << "V3 2 3 3" << endl;
    buffer << "V4 3 0 4" << endl;
}

void onlyCurrentSources(stringstream& buffer){
    buffer << "OnlyResistors" << endl;
    buffer << "I1 0 1 1" << endl;
    buffer << "I2 1 2 2" << endl;
    buffer << "I3 2 3 3" << endl;
    buffer << "I4 3 0 4" << endl;
}

void exampleCircuit1(stringstream& buffer){
    buffer << "ExampleCircuit1" << endl;
    buffer << "Vb 1 0 30" << endl;
    buffer << "R1 1 2 5" << endl;
    buffer << "R2 2 0 3" << endl;
    buffer << "R3 2 0 10" << endl;
    buffer << "Is 2 0 2" << endl;
}

void exampleCircuit2(stringstream& buffer){
    buffer << "ExampleCircuit2" << endl;
    buffer << "V1 0 1 1" << endl;
    buffer << "V2 2 0 2" << endl;
    buffer << "R3 1 2 3k" << endl;
}

int main(){
    stringstream buffer;
    exampleCircuit2(buffer);

    Circuit c{};

    if(buffer){
        c << buffer;
    }else{
        exit(1);
    }

    c.setupA();
    c.adjustB();

    MatrixXf A = c.getA();
    MatrixXf b = c.getB();

    IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    cout << A.format(CleanFmt) << endl << endl;
    cout << b.format(CleanFmt) << endl << endl;
    cout << (A*b).format(CleanFmt) << endl;
}