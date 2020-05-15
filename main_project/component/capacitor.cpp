#include <string>
#include <vector>
#include <CustomExceptionClasses/unsupportedIntegrationMethodOrderException.hpp>

#include "capacitor.hpp"

Capacitor::Capacitor(string name, vector<string> args, vector<float> extraInfo)
    :Component{name}
{
    int n1 = stoi(args[0]);
    int n2 = stoi(args[1]);
    float val = getValue(args[2]);
	int order = 1;

	subComponents = 2;
	nodes.push_back(n1);
	nodes.push_back(n2);	
	comp_current = 0;
	prev_current = 0; // previous comp_current
	prev_voltage = 0;
	
	if(order==1){ //Conductance of the capacitor will be the same as the companion model even at T=0 
		comp_conductance = (2.0f*val)/extraInfo[0];
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}

	types.push_back(componentType::conductanceSource);
	types.push_back(componentType::currentSource);
	types.push_back(componentType::vcUpdatable);
}

Capacitor::Capacitor(string _name,float c, int n1, int n2, float timeStep, int order)
	:Component{_name}, capacitance{c}{
	subComponents = 2;	
	nodes.push_back(n1);
	nodes.push_back(n2);	
	comp_current = 0;
	
	if(order==1){ //Conductance of the capacitor will be the same as the companion model even at T=0 
		comp_conductance = (2.0f*c)/timeStep;
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}

	types.push_back(componentType::conductanceSource);
	types.push_back(componentType::currentSource);
	types.push_back(componentType::vcUpdatable);
}

float Capacitor::getConductance() const{
	return comp_conductance;
}

float Capacitor::getCurrent() const{
	return comp_current;
}

float Capacitor::getTotalCurrent(int order) const{
	if(order == 1){ //companion model from Trapezoidal numerical integration method
		return 2.0*comp_conductance*comp_voltage - comp_current;
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}
}

void Capacitor::updateVals(float newVoltage, float newCurrent, int order){
	if(order==1){ //using companion model for the trapezoid integration method.
		// newCurrent = (comp_conductance*newVoltage) - comp_current; //Current into capacitor = current through companion conductance - (as current source pointing towards + node) current source current.		
		// comp_current = -comp_conductance*newVoltage - newCurrent;
		// comp_current = comp_conductance*newVoltage-comp_conductance*prev_voltage - comp_current;
		//comp_current = comp_conductance * newVoltage;		
		comp_current = (2.0*comp_conductance*newVoltage) - comp_current; //From trapezoid companion circuit diagram for capacitor. newVoltage = Vn, 		
		//prev_voltage = newVoltage;		
	//	prev_current = comp_current;		
		comp_voltage = newVoltage;
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}
		
}
vector<int> Capacitor::getNodes() const{
    vector<int> res{};
    res.push_back(nodes.at(0));
    res.push_back(nodes.at(1));
    return res;
}
