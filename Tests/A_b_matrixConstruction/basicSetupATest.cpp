#include <iostream>
#include <memory>
#include "./../../main_project/voltageSource.hpp"
#include "./../../main_project/currentSource.hpp"
#include "./../../main_project/resistor.hpp"
#include "./../../main_project/circuit.hpp"

//this class enables us to initialize the private component lists for testing the class methods
class TestableCircuit: public Circuit{
public:
    void setComponents(){
        //pass for now
    }
    void setVoltageSources(){
        voltageSources.push_back(make_unique<VoltageSource>(30, 1, 0));
    }
    void setCurrentSources(){
        currentSources.push_back(make_unique<CurrentSource>(2, 2, 0));
    }
    void setConductanceSources(){
        cunductanceSources.push_back(make_unique<Resistor>(5, 1, 2));
        cunductanceSources.push_back(make_unique<Resistor>(3, 2, 0));
        cunductanceSources.push_back(make_unique<Resistor>(10, 2, 0));
    }

    TestableCircuit(){
        setComponents();
        setVoltageSources();
        setCurrentSources();
        setConductanceSources();
    }
};

int main(){
    //to do
}