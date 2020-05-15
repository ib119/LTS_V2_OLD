#include <string>
#include <vector>
#include <CustomExceptionClasses/unsupportedIntegrationMethodOrderException.hpp>

#include "inductor.hpp"

Inductor::Inductor(string name, vector<string> args, vector<float> extraInfo)
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


	
	if(order==1){ //Conductance of the inductor will be the same as the companion model even at T=0 
		comp_conductance = extraInfo[0]/(2.0*val);
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}

	types.push_back(componentType::conductanceSource);
	types.push_back(componentType::currentSource);
	types.push_back(componentType::vcUpdatable);
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

	types.push_back(componentType::conductanceSource);
	types.push_back(componentType::currentSource);
	types.push_back(componentType::vcUpdatable);
}

float Inductor::getConductance() const{
	return comp_conductance;
}

float Inductor::getCurrent() const{
	return -comp_current; //So it's in the right direction, as current source points towards negative.
}

float Inductor::getTotalCurrent(int order) const{
	if(order == 1){ //companion model from Trapezoidal numerical integration method
		return -(2.0*comp_conductance*comp_voltage + comp_current); //negative as current flows from n1 to n2 of inductor
	}else{
		throw unsupportedIntegrationMethodOrderException();
	}
}

void Inductor::updateVals(float newVoltage, float newCurrent, int order){
	if(order==1){ //using companion model for the trapezoid integration method.
		//newCurrent = (comp_conductance*newVoltage) + comp_current; //Current into inductor = current through conductance + current source current		
		comp_current =(2.0*comp_conductance*newVoltage)+comp_current;
		comp_voltage = newVoltage;
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
