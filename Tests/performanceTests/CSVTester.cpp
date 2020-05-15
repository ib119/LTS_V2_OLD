#include <iostream>
#include <vector>
#include <fstream>
#include <chrono> 
#include <iomanip>

#include <circuit/circuit.hpp>
#include <input/input.hpp>
#include <output/output.hpp>

using namespace std;
using namespace std::chrono; 


//simple test circuit that is used for dynamic timestep/ dynamic simulation time test
void timestep1(stringstream& buffer){
    buffer.clear();
    buffer << "timestep1" << endl;
    buffer << "V1 1 0 SIN(0 10 10)" << endl;
    buffer << "R1 2 0 1000" << endl;
    buffer << "R2 1 2 500" << endl;
}
//more complex test circuit that is used for dynamic timestep/ dynamic simulation time test
void timestep2(stringstream& buffer){
    buffer.clear();
    buffer << "timestep2" << endl;
    buffer << "V1 2 1 SIN(0 10 10)" << endl;
    buffer << "R1 3 2 2000" << endl;
    buffer << "L1 1 0 .1" << endl;
    buffer << "R2 3 0 5000" << endl;
    buffer << "I1 4 3 .5" << endl;
    buffer << "R3 4 0 10000" << endl;
    buffer << "C1 4 0 .000001" << endl;
}


//circuit containing variable number of series resistors
void seriesResistors(stringstream& buffer, u_int count){
    buffer.clear();
    buffer << "seriesResistors" <<endl;
    buffer << "V1 1 0 SIN(0 10 10)" <<endl;
    for(u_int i{1}; i<count; i++){
        buffer << "R" << i << " " << i << " " << i+1 << " 1000" <<endl;
    }
    buffer << "R" << count << " " << count << " 0 1000" <<endl;
}



//circuit containing variable number of series capacitors
void seriesCapacitors(stringstream& buffer, u_int count){
    buffer.clear();
    buffer << "seriesCapacitors" <<endl;
    buffer << "V1 1 0 SIN(0 10 10)" <<endl;
    for(u_int i{1}; i<count; i++){
        buffer << "C" << i << " " << i << " " << i+1 << " 0.000001" <<endl;
    }
    buffer << "C" << count << " " << count << " 0 0.000001" <<endl;
}



//circuit containing variable number of series inductors
void seriesInductors(stringstream& buffer, u_int count){
    buffer.clear();
    buffer << "seriesInductors" <<endl;
    buffer << "V1 1 0 SIN(0 10 10)" <<endl;
    for(u_int i{1}; i<count; i++){
        buffer << "L" << i << " " << i << " " << i+1 << " .1" <<endl;
    }
    buffer << "L" << count << " " << count << " 0 .1" <<endl;
}



//circuit containing variable number of constant voltage sources
void seriesVS(stringstream& buffer, u_int count){
    buffer.clear();
    buffer << "seriesVS" <<endl;
    buffer << "V1 1 0 SIN(0 10 10)" <<endl;
    for(u_int i{1}; i<count; i++){
        buffer << "V" << i << " " << i << " " << i+1 << " 10" <<endl;
    }
    buffer << "V" << count << " " << count << " 0 10" <<endl;
}


//circuit containing variable number of constant current sources
void seriesCS(stringstream& buffer, u_int count){
    buffer.clear();
    buffer << "seriesCS" <<endl;
    buffer << "V1 1 0 SIN(0 10 10)" <<endl;
    for(u_int i{1}; i<count; i++){
        buffer << "I" << i << " " << i << " " << i+1 << " 2" <<endl;
    }
    buffer << "I" << count << " " << count << " 0 2" <<endl;
}




int main(int argc, char **argv){
    //the following times will be default for the tests that don't involve changing of timestep and simulation time
    float timeStep = 0.0001; //seconds
    float simulationTime = 1; //seconds

    Circuit* c;
    stringstream buffer;
    ofstream outputFile;

    //timestep scaling test (simple circuit)
    c = new Circuit{};
    outputFile.open("output/timeStepTest.csv");

    ////// didin't really undestand what this one was doing

    delete c;
    outputFile.close();

    ///////////////////////////////////////////////////////////////////////////////////////////

    //timestep scaling test (more complicated circuit containing inductors/capacitors)
    c = new Circuit{};
    outputFile.open("output/timeStepTestComplex.csv");
    
    ////// didin't really undestand what this one was doing

    delete c;
    outputFile.close();

    ////////////////////////////////////////////////////////////////////////////////////////////

    //simulation time scaling test (simple circuit)
    c = new Circuit{};
    outputFile.open("output/timeScalingTest.csv");
    
    ////// didin't really undestand what this one was doing#

    delete c;
    outputFile.close();

    ////////////////////////////////////////////////////////////////////////////////////////////

    //simulation time scaling test (more complicated circuit containing inductors/capacitors)
    c = new Circuit{};
    outputFile.open("output/timeScalingTestComplex.csv");
    
    ////// didin't really undestand what this one was doing

    delete c;
    outputFile.close();

    ////////////////////////////////////////////////////////////////////////////////////////////

    //series resistor scaling test
    c = new Circuit{};

    outputFile.open("output/resistorsTest.csv");
    outputFile << "Resistor count, Simulation Time (seconds)" << endl;

    // how many resistors to use
    int minResistors = 0;
    int maxResistors = 100;
    int deltaResistors = 1;

    for(int resistorCount = minResistors; resistorCount < maxResistors; resistorCount += deltaResistors){
        seriesResistors(buffer, resistorCount);
        
        auto start = high_resolution_clock::now();

        setupBasic(*c, timeStep);
        readSpice(*c, buffer);
        outputCSV(*c, "output_ignore.txt", timeStep, simulationTime);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - stop);
        auto timeTaken = duration.count();
        outputFile << resistorCount << "," << timeTaken/1000.0f << endl;
    }

    outputFile.close();
    delete c;

    //////////////////////////////////////////////////////////////////////////////////////////////

    //series capacitor scaling test
    c = new Circuit{};

    outputFile.open("output/capacitorsTest.csv");
    outputFile << "Resistor count, Simulation Time (seconds)" << endl;

    // how many capacitor to use
    int minCapacitors = 0;
    int maxCapacitors = 100;
    int deltaCapacitors = 1;

    for(int capacitorCount = minCapacitors; capacitorCount < maxCapacitors; capacitorCount += deltaCapacitors){
        seriesCapacitors(buffer, capacitorCount);
        
        auto start = high_resolution_clock::now();

        setupBasic(*c, timeStep);
        readSpice(*c, buffer);
        outputCSV(*c, "output_ignore.txt", timeStep, simulationTime);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - stop);
        auto timeTaken = duration.count();
        outputFile << capacitorCount << "," << timeTaken/1000.0f << endl;
    }

    outputFile.close();
    delete c;

    //////////////////////////////////////////////////////////////////////////////////////////////

    //series inductor scaling test
    c = new Circuit{};

    outputFile.open("output/capacitorsTest.csv");
    outputFile << "Inductor count, Simulation Time (seconds)" << endl;

    // how many inductors to use
    int minInductors = 0;
    int maxInductors = 100;
    int deltaInductors = 1;

    for(int inductorCount = minInductors; inductorCount < maxInductors; inductorCount += deltaInductors){
        seriesInductors(buffer, inductorCount);
        
        auto start = high_resolution_clock::now();

        setupBasic(*c, timeStep);
        readSpice(*c, buffer);
        outputCSV(*c, "output_ignore.txt", timeStep, simulationTime);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - stop);
        auto timeTaken = duration.count();
        outputFile << inductorCount << "," << timeTaken/1000.0f << endl;
    }

    outputFile.close();
    delete c;

    //////////////////////////////////////////////////////////////////////////////////////////////

    //series vs scaling test
    c = new Circuit{};
    outputFile.open("output/seriesVsScaling.csv");
    
    ////// didin't really undestand what this one was doing

    delete c;
    outputFile.close();

    ////////////////////////////////////////////////////////////////////////////////////////////

    //series vs scaling test
    c = new Circuit{};
    outputFile.open("output/seriesVsScalingComplex.csv");
    
    ////// didin't really undestand what this one was doing

    delete c;
    outputFile.close();

    ////////////////////////////////////////////////////////////////////////////////////////////
}