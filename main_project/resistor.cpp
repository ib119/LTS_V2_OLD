#include "resistor.hpp"

Resistor::Resistor(float r, int n1, int n2){
    conductance = 1/r;
    nodes.push_back(n1);
    nodes.push_back(n2);
}

float Resistor::getConductance(int node){
    return conductance;
}