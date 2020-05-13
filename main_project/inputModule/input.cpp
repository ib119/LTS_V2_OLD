#include "input.hpp"

#include "../circuit.hpp"
#include "../resistor.hpp"
#include "../currentSource.hpp"
#include "../voltageSource.hpp"

void readSpice(Circuit& c, istream& file){
    string title;
    getline(file, title);
    c.setTitle(title);

    stringstream line;
    string lineString{};
    char compTypeC{};
    string name{};
    string arg{};
    vector<string> args;


    while(getline(file, lineString)){
        line << lineString;
        line.get(compTypeC);
        line >> name;

        while(line >> arg){
            args.push_back(arg);
        }

        if(compTypeC == 'R' || compTypeC == 'r'){
			c.addComponent<Resistor>(name, args);
		}else if(compTypeC == 'V' || compTypeC == 'v'){
			c.addComponent<VoltageSource>(name, args);
		}else if(compTypeC == 'I' || compTypeC == 'i'){
			c.addComponent<CurrentSource>(name, args);
		}
    }
}