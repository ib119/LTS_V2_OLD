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
    string outputFileName = "linearTransientTestTemp.csv";
    //the following times will be default for the tests that don't involve changing of timestep and simulation time
    float timeStep = 0.0001; //seconds
    float simulationTime = 1; //seconds

    Circuit c{};
    stringstream buffer;


    //timestep scaling test (simple circuit)
    cout << "Timestep test using simple circuit 'timestep1' and a simulation time of " 
        << simulationTime << " seconds:" <<endl;
    cout << setw(20) << "Timestep (seconds): " << setw(25) << "Tame taken (seconds):" << endl;
    float smallestTimestep1 = 1e-6;
    for(float timeStep1{1}; timeStep1>=smallestTimestep1; timeStep1/=5){
        auto start = high_resolution_clock::now(); 
        timestep1(buffer);
        setupBasic(c, timeStep1);
        readSpice(c, buffer);
        outputCSV(c, outputFileName, timeStep1, simulationTime);
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        auto count = duration.count();
        cout << setw(15) << timeStep1 << setw(25) << count/1000.0f <<endl;
    }

    cout << endl << endl;
     
    //timestep scaling test (more complicated circuit containing inductors/capacitors)
    cout << "Timestep test using more complex circuit 'timestep2' and a simulation time of " 
        << simulationTime << " seconds:" <<endl;
    cout << setw(20) << "Timestep (seconds): " << setw(25) << "Tame taken (seconds):" << endl;
    float smallestTimestep2 = 1e-6;
    for(float timeStep1{1}; timeStep1>=smallestTimestep2; timeStep1/=5){
        auto start = high_resolution_clock::now(); 
        timestep2(buffer);
        setupBasic(c, timeStep1);
        readSpice(c, buffer);
        outputCSV(c, outputFileName, timeStep1, simulationTime);
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        auto count = duration.count();
        cout << setw(15) << timeStep1 << setw(25) << count/1000.0f <<endl;
    }

    cout << endl << endl;

    //simulation time scaling test (simple circuit)
    cout << "Simulation time test using simple circuit 'timestep1' and a timeStep of " 
        << timeStep << " seconds:" <<endl;
    cout << setw(25) << "Simulation time (seconds): " << setw(25) << "Tame taken (seconds):" << endl;
    float largestSimulationTime1 = 30;
    for(float simulationTime1{.1}; simulationTime1<=largestSimulationTime1; simulationTime1*=2){
        auto start = high_resolution_clock::now(); 
        timestep1(buffer);
        setupBasic(c, simulationTime1);
        readSpice(c, buffer);
        outputCSV(c, outputFileName, timeStep, simulationTime1);
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        auto count = duration.count();
        cout << setw(20) << simulationTime1 << setw(25) << count/1000.0f <<endl;
    }

    cout << endl << endl;

    //simulation time scaling test (more complicated circuit containing inductors/capacitors)
    cout << "Simulation time test using more complex circuit 'timestep2' and a timeStep of " 
        << timeStep << " seconds:" <<endl;
    cout << setw(25) << "Simulation time (seconds): " << setw(25) << "Tame taken (seconds):" << endl;
    float largestSimulationTime2 = 30;
    for(float simulationTime1{.1}; simulationTime1<=largestSimulationTime2; simulationTime1*=2){
        auto start = high_resolution_clock::now(); 
        timestep2(buffer);
        setupBasic(c, simulationTime1);
        readSpice(c, buffer);
        outputCSV(c, outputFileName, timeStep, simulationTime1);
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        auto count = duration.count();
        cout << setw(20) << simulationTime1 << setw(25) << count/1000.0f <<endl;
    }

    cout << endl << endl;

    //series resistor scaling test
    cout << "Series resistor test with a simulation time of " 
        << simulationTime << " seconds and a timestep of "
        << timeStep << "seconds: " << endl;
    cout << setw(20) << "Resistor count: " << setw(25) << "Tame taken (seconds):" << endl;
    float largestResistorNumber = 100;
    for(float resistorNumber{1}; resistorNumber<=largestResistorNumber; resistorNumber*=2){
        auto start = high_resolution_clock::now(); 
        seriesResistors(buffer, resistorNumber);
        setupBasic(c, timeStep);
        readSpice(c, buffer);
        outputCSV(c, outputFileName, timeStep, simulationTime);
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        auto count = duration.count();
        cout << setw(15) << resistorNumber << setw(25) << count/1000.0f <<endl;
    }

    cout << endl << endl;

    //series capacitor scaling test
    cout << "Series capacitor test with a simulation time of " 
        << simulationTime << " seconds and a timestep of "
        << timeStep << "seconds: " << endl;
    cout << setw(20) << "Capacitor count: " << setw(25) << "Tame taken (seconds):" << endl;
    float largestCapacitorNumber = 60;
    for(float capacitorNumber{1}; capacitorNumber<=largestCapacitorNumber; capacitorNumber*=2){
        auto start = high_resolution_clock::now(); 
        seriesCapacitors(buffer, capacitorNumber);
        setupBasic(c, timeStep);
        readSpice(c, buffer);
        outputCSV(c, outputFileName, timeStep, simulationTime);
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        auto count = duration.count();
        cout << setw(15) << capacitorNumber << setw(25) << count/1000.0f <<endl;
    }

    cout << endl << endl;

    //series inductor scaling test
    cout << "Series inductor test with a simulation time of " 
        << simulationTime << " seconds and a timestep of "
        << timeStep << "seconds: " << endl;
    cout << setw(20) << "Inductor count: " << setw(25) << "Tame taken (seconds):" << endl;
    float largestInductorNumber = 60;
    for(float inductorNumber{1}; inductorNumber<=largestInductorNumber; inductorNumber*=2){
        auto start = high_resolution_clock::now(); 
        seriesInductors(buffer, inductorNumber);
        setupBasic(c, timeStep);
        readSpice(c, buffer);
        outputCSV(c, outputFileName, timeStep, simulationTime);
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        auto count = duration.count();
        cout << setw(15) << inductorNumber << setw(25) << count/1000.0f <<endl;
    }

    cout << endl << endl;

    //series vs scaling test
    cout << "Series vs test with a simulation time of " 
        << simulationTime << " seconds and a timestep of "
        << timeStep << "seconds: " << endl;
    cout << setw(20) << "vs count: " << setw(25) << "Tame taken (seconds):" << endl;
    float largestVSNumber = 100;
    for(float vsNumber{1}; vsNumber<=largestVSNumber; vsNumber*=2){
        auto start = high_resolution_clock::now(); 
        seriesVS(buffer, vsNumber);
        setupBasic(c, timeStep);
        readSpice(c, buffer);
        outputCSV(c, outputFileName, timeStep, simulationTime);
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        auto count = duration.count();
        cout << setw(15) << vsNumber << setw(25) << count/1000.0f <<endl;
    }

    cout << endl << endl;

    //series vs scaling test
    cout << "Series vs test with a simulation time of " 
        << simulationTime << " seconds and a timestep of "
        << timeStep << "seconds: " << endl;
    cout << setw(20) << "vs count: " << setw(25) << "Tame taken (seconds):" << endl;
    float largestCSNumber = 100;
    for(float csNumber{1}; csNumber<=largestCSNumber; csNumber*=2){
        auto start = high_resolution_clock::now(); 
        seriesCS(buffer, csNumber);
        setupBasic(c, timeStep);
        readSpice(c, buffer);
        outputCSV(c, outputFileName, timeStep, simulationTime);
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        auto count = duration.count();
        cout << setw(15) << csNumber << setw(25) << count/1000.0f <<endl;
    }

    cout << endl << endl;
}