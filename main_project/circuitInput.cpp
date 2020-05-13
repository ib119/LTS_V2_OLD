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

template <class comp>
void Circuit::addComponent(string name, vector<string> args){
	comp* newComp = new comp(name, args);
	vector<int> types = newComp.getTypes();
	for(int type : types){
		switch (type)
		{
		case 0:
			conductanceSources.push_back(newComp);
			break;
		case 1:
			voltageSources.push_back(newComp);
			break;
		case 2:
			currentSources.push_back(newComp);
			break;
		default:
			break;
		}
		components.push_back(newComp);
	}
}

void Circuit::setTitle(string _title){
	title = _title;
}

// this should read one line of the iostream setup the proper components in the circuit and return the rest of the iostream
void Circuit::operator<<(istream& file){
	getline(file, title);
	string arg{};

	Component* newComp;
	string compType{};
	while(file >> arg){
		compType = arg[0];
		if(compType == "R" || compType == "r"){
			newComp = setUpResistor(arg, file);
			conductanceSources.push_back(newComp);
		}else if(compType == "V" || compType == "v"){
			newComp = setUpVoltageSource(arg, file);
			voltageSources.push_back(newComp);
		}else if(compType == "I" || compType == "i"){
			newComp = setUpCurrentSource(arg, file);
			currentSources.push_back(newComp);
		}
		components.push_back(newComp);
		// if arg = ... compare untill you reach End statement then quit loop
	}
}