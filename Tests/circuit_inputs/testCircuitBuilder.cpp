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

void onlyCurrentSources(){

}

void onlyVoltageSources(){

}

void exampleCircuit1(stringstream& buffer){
    buffer << "ExampleCircuit1" << endl;
    buffer << "Vb 1 0 30" << endl;
    buffer << "R1 1 2 5" << endl;
    buffer << "R2 2 0 3" << endl;
    buffer << "R3 2 0 10" << endl;
    buffer << "Is 2 0 2" << endl;
}

int main(){
    stringstream buffer;
    exampleCircuit1(buffer);

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
    cout << b.format(CleanFmt) << endl;
}