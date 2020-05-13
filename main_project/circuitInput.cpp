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