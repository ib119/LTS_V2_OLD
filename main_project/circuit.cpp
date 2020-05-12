#include <iostream>
#include <Eigen/Dense>

#include "circuit.hpp"

using namespace std;
using namespace Eigen;

Circuit::Circuit()
{
    time = 0;
    timeStep = 0.1; // in seconds
    highestNodeNumber = 0;
}

Circuit::~Circuit()
{
    //if we use vectors of raw pointer, this must delete them
    //if we change to smart pointers, deletion will be done automatically by the pointer
}

// setupA definition
void Circuit::setupA(){
    A = MatrixXf::Zero(highestNodeNumber+voltageSources.size(),highestNodeNumber+voltageSources.size());
    vector<int> nodes{};

    //constructing conductance part
    for(const auto &comp : conductanceSources){
        const float conductance = comp->getConductance();
        nodes = comp->getNodes();

        // I had to change the alogirthm to allow for node1 to be 0
        // Doing it this way also allows for multiple nodes per component
        // This code would get much cleaner if we have a node input to the gerConductnace method to return a positive or negative depending on the node order
        // But that's just a thought for the future
        for(int i = 0; i < nodes.size(); i++){
            if(nodes[i] == 0) continue;
            A(nodes[i]-1, nodes[i]-1) += conductance;
            for(int j = 0; j < nodes.size(); j++){
                if(i == j||nodes[j] == 0) continue;
                A(nodes[i]-1, nodes[j]-1) -= conductance;
            }
        }

        IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
        cout << A.format(CleanFmt) << endl << endl;
    }

    //voltage part
    for(int i{}; i<voltageSources.size(); i++){
        const auto &vs = voltageSources.at(i);
        nodes = vs->getNodes();
        const int node1 = nodes.at(0);
        const int node2 = nodes.at(1);

        A(node1-1,highestNodeNumber+i) = 1;
        A(highestNodeNumber+i,node1-1) = 1; //different when dealing with dependent sources
        
        if(node2 != 0){
            A(node2-1,highestNodeNumber+i) = -1;
            A(highestNodeNumber+i,node2-1) = -1; //different when dealing with dependent sources
        }
    }
}

MatrixXf Circuit::getA(){
    return A;
}

// setupB definition
void Circuit::adjustB(){
    b = VectorXf::Zero(highestNodeNumber+voltageSources.size());

    //adding currents
    for(const auto &cSource : currentSources){
        vector<int> nodes = cSource->getNodes();
        const int node1 = nodes.at(0);
        const int node2 = nodes.at(1);
        b(node1-1) += cSource->getCurrent();

        if(node2 != 0){
            b(node2-1) += -cSource->getCurrent();
        }
    }

    //adding voltages
    for(int i{highestNodeNumber}; i<highestNodeNumber+voltageSources.size(); i++){
        b(i) = voltageSources.at(i)->getVoltage();
    }
}

MatrixXf Circuit::getB(){
    return b;
}