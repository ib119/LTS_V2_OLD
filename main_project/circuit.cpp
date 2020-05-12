#include <iostream>
#include <Eigen/Dense>

#include "circuit.hpp"

using namespace std;
using namespace Eigen;

Circuit::Circuit()
{
    float time = 0;
    float timeStep = 0.1; // in seconds
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
        const int node1 = nodes.at(0);
        const int node2 = nodes.at(1);

        A(node1-1,node1-1) += conductance;

        if(node2 != 0){
            A(node2-1,node2-1) += conductance;
            A(node1-1,node2-1) -= conductance;
            A(node2-1,node1-1) -= conductance;
        }
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
    for(int i{highestNodeNumber}, j{}; i<highestNodeNumber+voltageSources.size(); i++, j++){
        b(i) = voltageSources.at(j)->getVoltage();
    }
}
