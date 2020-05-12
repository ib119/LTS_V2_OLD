#include "inductor.hpp"
#include "circuit.hpp"


Inductor::Inductor(float l, int n1, int n2, float timeStep, int order){
	inductance = l;
	nodes.push_back(n1);
	nodes.push_back(n2);	
	comp_current = 0;
	
	if(order==1){	//Conductance of the inductor will be the same as the companion model even at T=0 
		comp_conductance = timeStep/(2.0*l);
	}
}

Inductor::~Inductor(){

}

float Inductor::getConductance(){
	return comp_conductance;
}

float Inductor::getCurrent(){
	return comp_current;
}

void Inductor::updateVals(int order){
	if(order==1){ //using companion model for the trapezoid integration method.
		prev_voltage = voltage;
		voltage = 0; //REPLACE WITH Voltage[A] - Voltage[B], where Voltage[A] is the voltage at node A.
		prev_current = current;
		current = 0; //REPLACE WITH current flowing into inductor
		comp_current = current + (comp_conductance*voltage)
	}
		


}


int main(){
Inductor l1(0.1,1,2,0.01,1);

}
