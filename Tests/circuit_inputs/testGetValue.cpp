#include <iostream>

#include <circuit/circuit.hpp>
#include <circuit/circuit.cpp>

#include <component/component.hpp>
#include <component/component.cpp>

#include <component/resistor.hpp>
#include <component/resistor.cpp>

using namespace std;

int main(){
    bool pass = true;
    // sets up a component to allow acces to get value function
    Resistor c{"R1", 0, 0, 1};
    
    pass &= 10e-15 == c.getValue("10u");
    pass &= 10 == c.getValue("10aksjdkjaskd");
    pass &= 0.01== c.getValue("10mlamsldkasdasd");
    pass &= 10000000 == c.getValue("10MEG");
    pass &= 202401 == c.getValue(".202401G");

    if(pass){
        cout << "SUCCESS";
    }else{
        cout << "FAIL";
    }
    cout << endl;
}