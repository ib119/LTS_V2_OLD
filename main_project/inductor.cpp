#include "circuit.hpp"
#include "inductor.hpp"
#include "./CustomExceptionClasses/unsupportedIntegrationMethodOrderException.cpp"

Inductor::Inductor(string name, vector<string> args, float timeStep)
    :Component{name}
{
    int n1 = stoi(args[0]);
    int n2 = stoi(args[1]);
    float val = getValue(args[2]);
	int order = 0;

	subComponents = 2;
	nodes.push_back(n1);
	nodes.push_back(n2);	
	comp_current = 0;
	
	if(order==1){ //Conductance of the inductor will be the same as the companion model even at T=0 
		comp_conductance = timeStep/(2.0*l);
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}
}

Inductor::Inductor(string _name,float l, int n1, int n2, float timeStep, int order)
	:Component{_name}, inductance{l}{
	subComponents = 2;	
	nodes.push_back(n1);
	nodes.push_back(n2);	
	comp_current = 0;
	
	if(order==1){ //Conductance of the inductor will be the same as the companion model even at T=0 
		comp_conductance = timeStep/(2.0*l);
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}
}

float Inductor::getConductance() const{
	return comp_conductance;
}

float Inductor::getCurrent() const{
	return comp_current;
}

void Inductor::updateVals(float voltage, float current, int order){
	if(order==1){ //using companion model for the trapezoid integration method.
		comp_current = current + (comp_conductance*voltage);
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}
		
}
vector<int> Inductor::getNodes() const{
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}
