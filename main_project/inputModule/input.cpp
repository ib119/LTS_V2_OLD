#include "input.hpp"

#include "../circuit.hpp"
#include "../resistor.hpp"
#include "../currentSource.hpp"
#include "../voltageSource.hpp"
#include "../inductor.hpp"
#include "../capacitor.hpp"
#include "../component.hpp"

void readSpice(Circuit& c, istream& file){
    string title;
    getline(file, title);
    c.setTitle(title);

    string lineString{};
    int maxNode = 0;

    while(getline(file, lineString)){
        stringstream line;
        string compTypeC{};
        string name{};
        string arg{};
        vector<string> args{};

        line << lineString;
        line >> name;
        compTypeC = name[0];

        while(line >> arg){
            args.push_back(arg);
        }

        // for now this script will assume knowledge of components to get largest node values
        // will only work for components with two inputs, will fix this later
        int n1 = stoi(args[0]);
        int n2 = stoi(args[1]);
        
        if(n1 > maxNode) maxNode = n1;
        if(n2 > maxNode) maxNode = n2;

        if(compTypeC == "R" || compTypeC == "r"){
			c.addComponent<Resistor>(name, args);
		}else if(compTypeC == "V" || compTypeC == "v"){
			c.addComponent<VoltageSource>(name, args);
		}else if(compTypeC == "I" || compTypeC == "i"){
			c.addComponent<CurrentSource>(name, args);
		//}else if(compTypeC == "I" || compTypeC == "i"){ //Is this meant to be here twice?
		//	c.addComponent<CurrentSource>(name, args);
		}else if(compTypeC == "L" || compTypeC == "l"){
			c.addComponent<Inductor>(name, args);
		}else if(compTypeC =="C" || compTypeC == "c"){
			c.addComponent<Capacitor>(name,args);
		}
		
    }
    c.setHighestNodeNumber(maxNode);
}

void setupBasic(Circuit& c, float timeStep){
    c.setTimeStep(timeStep);
}
