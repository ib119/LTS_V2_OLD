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
        voltageSources.push_back(make_unique<VoltageSource>(32, 1, 0));
        voltageSources.push_back(make_unique<VoltageSource>(20, 3, 2));
    }
    void setCurrentSources(){
        currentSources.push_back(make_unique<CurrentSource>(2, 2, 1));
    }
    void setConductanceSources(){
        cunductanceSources.push_back(make_unique<Resistor>(2, 2, 1));
        cunductanceSources.push_back(make_unique<Resistor>(8, 2, 0));
        cunductanceSources.push_back(make_unique<Resistor>(4, 3, 0));
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