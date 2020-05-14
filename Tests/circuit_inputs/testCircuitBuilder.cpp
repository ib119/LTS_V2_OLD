#include <iostream>
#include <fstream>
#include <sstream>

#include "./../../main_project/circuit.hpp"
#include "./../../main_project/circuit.cpp"

#include "./../../main_project/component.hpp"
#include "./../../main_project/component.cpp"

#include "./../../main_project/resistor.hpp"
#include "./../../main_project/resistor.cpp"

#include "./../../main_project/currentSource.hpp"
#include "./../../main_project/currentSource.cpp"

#include "./../../main_project/voltageSource.hpp"
#include "./../../main_project/voltageSource.cpp"

#include "./../../main_project/inductor.hpp"
#include "./../../main_project/inductor.cpp"

#include "./../../main_project/inputModule/input.hpp"
#include "./../../main_project/inputModule/input.cpp"

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

// obviously going to spount nonsne since this circuit makes no sense
void onlySINVoltageSources(stringstream& buffer){
    buffer << "OnlyResistors" << endl;
    buffer << "V1 0 1 SIN(0, 1, 1)" << endl;
    buffer << "V2 1 2 SIN(0, 1, 1, 0)" << endl;
    buffer << "V3 2 3 SIN(0, 1, 1, 0, 0)" << endl;
    buffer << "V4 3 0 SIN(0, 1, 1, 0, 0, 0)" << endl;
}

void onlyCurrentSources(stringstream& buffer){
    buffer << "OnlyResistors" << endl;
    buffer << "I1 0 1 1" << endl;
    buffer << "I2 1 2 2" << endl;
    buffer << "I3 2 3 3" << endl;
    buffer << "I4 3 0 4" << endl;
}

void onlyInductors(stringstream& buffer){
    buffer << "OnlyResistors" << endl;
    buffer << "L1 0 1 1" << endl;
    buffer << "L2 1 2 2" << endl;
    buffer << "L3 2 3 3" << endl;
    buffer << "L4 3 0 4" << endl;
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

void exampleCircuit3(stringstream& buffer){
    buffer << "ExampleCircuit3" << endl;
    buffer << "R1 0 1 1" << endl;
    buffer << "R2 2 3 2" << endl;
    buffer << "R3 3 0 3" << endl;
    buffer << "Vs 2 1 5" << endl;
    buffer << "Vd 0 3 1000" << endl;
}

void exampleCircuit4(stringstream& buffer){
    buffer << "ExampleCircuit3" << endl;
    buffer << "Ra 0 1 1" << endl;
    buffer << "vb 2 1 1" << endl;
    buffer << "ic 2 0 1" << endl;
}

int main(){
    stringstream buffer;
    onlySINVoltageSources(buffer);

    Circuit c{};

    if(buffer){
        readSpice(c, buffer);
    }else{
        exit(1);
    }

    c.setupA();
    c.adjustB();
    c.computeA_inv();
    c.computeX();
    c.setupXMeaning();

    MatrixXf A = c.getA();
    VectorXf b = c.getB();
    VectorXf x = c.getX();
    vector<string> xMeaning = c.getXMeaning();

    IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    cout << A.format(CleanFmt) << endl << endl;
    cout << b.format(CleanFmt) << endl << endl;
    cout << x.format(CleanFmt) << endl <<endl;
    // cout << (A.inverse()*b).format(CleanFmt) << endl;

    for(int i{}; i<xMeaning.size(); i++){
        cout << i << ": " << xMeaning.at(i) << endl;
    }    
}