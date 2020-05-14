#include "component.hpp"
#include "./CustomExceptionClasses/notSupportedByComponentException.hpp"

using namespace std;

Component::Component(string _name)
    :name{_name}{};
Component::~Component(){}

// these functions should by default throw error unless overwritten by another child class down the line
// this allows to call an error if ever a function that shouldn't be returning a voltage or current or conductance
// is asked for one
float Component::getVoltage() const{
    throw notSupportedByComponentException();
}

float Component::getCurrent() const{
   throw notSupportedByComponentException();
}

float Component::getConductance() const{
    throw notSupportedByComponentException();
}

void Component::updateVals(float newVoltage, float newCurrent, int order){
    throw notSupportedByComponentException();
}

string Component::getName() const{
    return name;
}


// helper function to parse string with units into float
float Component::getValue(string val){
	string units{};
	float base{};//base number
	float mult{};//what we multiply the number by
	int ss = -1;//string start
	for(int i = 0; i < val.size(); i++){
		if(val[i] > '9'){
			ss = i;
			break;
		}
	}
	if(ss =! -1){
		base = stof(val.substr(0,ss));
		units = val.substr(ss, val.size() - 1 - ss);
		char u = units[0];
		switch(u){
			case 'F': case 'f':
				mult = 1e-15;
				break;
			case 'P': case 'p':
				mult = 1e-12;
				break;
			case 'N': case 'n':
				mult = 1e-9;
				break;
			case 'U': case 'u':
				mult = 1e-6;
				break;
			case 'K': case 'k':
				mult = 1e3;
				break;
			case 'G': case 'g':
				mult = 1e9;
				break;
			case 'T': case 't':
				mult = 1e12;
				break;
			case 'M': case 'm':
				if(units.size() > 2){
					if((units[1] == 'E' && units[2] == 'G') || (units[1] == 'e' && units[2] == 'g')){
						mult = 1e6;
						break;
					}else if((units[1] == 'I' && units[2] == 'L') || (units[1] == 'i' && units[2] == 'l')){
						mult = 25.4e-6;
						break;
					}
				}
				mult = 1e-3;
				break;
			default:
				mult = 1;
				break;
		}
		return base * mult;
	}else{
		return stof(val);
	}
}

vector<int> Component::getTypes() const{
	return types;
}
