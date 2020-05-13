#include <iostream>
#include "./../../main_project/voltageSource.hpp"
#include "./../../main_project/currentSource.hpp"
#include "./../../main_project/resistor.hpp"
#include "./../../main_project/inductor.hpp"
#include "./../../main_project/circuit.hpp"

//this class enables us to initialize the private component lists for testing the class methods
class TestableCircuit: public Circuit{
public:
    void setComponents(){
        //pass for now
    }
    void setVoltageSources(){
        // voltageSources.push_back(new VoltageSource("V1", 32, 1, 0));
        // voltageSources.push_back(new VoltageSource("V2", 20, 3, 2));
    }
    void setCurrentSources(){
        currentSources.push_back(new CurrentSource("Is", 10, 1, 0));
        currentSources.push_back(new Inductor("L3", 0.01e-6, 2, 0, 0.1, 1));
    }
    void setConductanceSources(){
        conductanceSources.push_back(new Resistor("r1", 1, 1, 0));
        conductanceSources.push_back(new Resistor("r2", 1e3, 1, 2));
        conductanceSources.push_back(new Resistor("r3", 100e3, 2, 0));
        conductanceSources.push_back(new Inductor("L3", 0.01e-6, 2, 0, 0.1, 1));
    }

    TestableCircuit(){
        setComponents();
        setVoltageSources();
        setCurrentSources();
        setConductanceSources();
        highestNodeNumber = 3;
    }

    auto getA() const{
        return A;
    }
    auto getb() const{
        return b;
    }
};

/*
    IMPORTANT: Before testing, the "private" specifier of 
                the Circuit class must be changed to "protected"
*/

int main(){
    TestableCircuit circuit{};
    circuit.setupA();
    cout << "setupA() complete" <<endl;

    circuit.adjustB();
    cout << "adjustB() complete" <<endl;

    auto A = circuit.getA();
    auto b = circuit.getb();
    cout << "A:" << endl;
    cout << A;
    cout << endl <<endl << "b:" <<endl;
    cout << b;
    cout << endl;
}