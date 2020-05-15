#include <iostream>
#include <fstream>
#include <sstream>

#include <input/input.hpp>
#include <input/input.cpp>

#include <circuit/circuit.hpp>
#include <circuit/circuit.cpp>

#include <component/component.cpp>
#include <component/resistor.cpp>
#include <component/capacitor.cpp>
#include <component/inductor.cpp>
#include <component/voltageSource.cpp>
#include <component/currentSource.cpp>
#include <component/waveform.cpp>

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
    buffer << "OnlySINVoltageSources" << endl;
    buffer << "V1 0 1 SIN(0 1 1)" << endl;
    buffer << "V2 1 2 SIN(0 1 1 0)" << endl;
    buffer << "V3 2 3 SIN(0 1 1 0 0)" << endl;
    buffer << "V4 3 0 SIN(0 1 1 0 0 0)" << endl;
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

void exampleCircuit5(stringstream& buffer){
    buffer << "ExampleCircuit1" << endl;
    buffer << "Vb 1 0 SIN(0 30 1)" << endl;
    buffer << "R1 1 2 5" << endl;
    buffer << "R2 2 0 3" << endl;
    buffer << "R3 2 0 10" << endl;
    buffer << "Is 2 0 2" << endl;
}

void exampleCircuit6(stringstream& buffer){
    buffer << "ExampleCircuit1" << endl;
    buffer << "V1 1 0 10" << endl;
    buffer << "R1 1 2 10000" << endl;
    buffer << "C1 2 0 0.000001" << endl;
}

void exampleCircuit7(stringstream& buffer){
    buffer << "ExampleCircuit1" << endl;
    buffer << "I1 1 0 10" << endl;
    buffer << "R1 1 0 1" << endl;
    buffer << "R2 2 1 2" << endl;
    buffer << "C1 2 0 1" << endl;
}

void exampleCircuit8(stringstream& buffer){
    buffer << "ExampleCircuit1" << endl;
    buffer << "Ib 1 0 SIN(0 30 1)" << endl;
    buffer << "R1 1 2 5" << endl;
    buffer << "R2 2 0 3" << endl;
    buffer << "R3 2 0 10" << endl;
    buffer << "Vs 2 0 2" << endl;
}

void testingUnits(stringstream& buffer){
    buffer << "ExampleCircuit1" << endl;
    buffer << "R1 0 1 1u" << endl;
    buffer << "R2 1 2 10" << endl;
    buffer << "R3 2 3 1MEG" << endl;
    buffer << "R4 3 0 .10K" << endl;
}

// pass |= 10e-15 == c.getValue("10u");
// pass |= 10 == c.getValue("10aksjdkjaskd");
// pass |= 0.01== c.getValue("10mlamsldkasdasd");
// pass |= 10000000 == c.getValue("10MEG");
// pass |= 202401 == c.getValue(".202401G");

int main(){
    stringstream buffer;
    testingUnits(buffer);

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