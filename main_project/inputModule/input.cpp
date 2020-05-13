#include "input.hpp"

#include "../circuit.hpp"
#include "../resistor.hpp"
#include "../currentSource.hpp"
#include "../voltageSource.hpp"

void readSpice(Circuit& c, istream& file){
    string title;
    getline(file, title);
    c.setTitle(title);

    string lineString{};

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

        if(compTypeC == "R" || compTypeC == "r"){
			c.addComponent<Resistor>(name, args);
		}else if(compTypeC == "V" || compTypeC == "v"){
			c.addComponent<VoltageSource>(name, args);
		}else if(compTypeC == "I" || compTypeC == "i"){
			c.addComponent<CurrentSource>(name, args);
		}
    }
}