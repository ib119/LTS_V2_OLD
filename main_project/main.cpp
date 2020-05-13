#include <iostream>
#include <Eigen>
#include <vector>
#include <fstream>

#include "circuit.hpp"
#include "component.hpp"
#include "resistor.hpp"
#include "voltageSource.hpp"
#include "currentSource.hpp"
#include "capacitor.hpp"
#include "inductor.hpp"

using namespace std;

// this function will eventually read from file and convert to istream to pass into second overload
void readSpice(Circuit& c, string file);
// this function setsup component c from what it reads from istream
void readSpice(Circuit& c, istream& file);

int main(){
    Circuit c{};
    readSpice(c, cin);
}

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