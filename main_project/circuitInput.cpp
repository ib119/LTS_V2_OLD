#include <iostream>
#include <string>
#include <vector>

#include "circuit.hpp"
#include "component.hpp"

#include "voltageSource.hpp"
#include "currentSource.hpp"
#include "resistor.hpp"
#include "capacitor.hpp"
#include "inductor.hpp"

using namespace std;

// this should read one line of the iostream setup the proper components in the circuit and return the rest of the iostream
void Circuit::operator<<(iostream& file){
	getline(file, title);
	string arg{};

	Component* newComp;
	string compType{};
	while(file >> arg){
		compType = arg[0];
		if(compType == "R" || compType == "r"){
			newComp = setUpResistor(arg, file);
			conductanceSources.push_back(newComp);
		}
		components.push_back(newComp);
		// if arg = ... compare untill you reach End statement then quit loop
	}
}

// helper function to parse string with units into float
float Circuit::getValue(string val){
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


// helper function to setup up resistor from specific inputs
Component* Circuit::setUpResistor(string arg, iostream& file){
	string name = arg.substr(1, arg.size()-1);
	file >> arg;
	int n1 = stoi(arg);
	file >> arg;
	int n2 = stoi(arg);
	file >> arg;
	float val = getValue(arg);
	Resistor* out = new Resistor(name, val, n1, n2);
	return out;
}