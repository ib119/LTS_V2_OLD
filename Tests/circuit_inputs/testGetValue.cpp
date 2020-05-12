#include <iostream>

#include "./../../main_project/circuit.hpp"
#include "./../../main_project/circuit.cpp"
#include "./../../main_project/circuitInput.cpp"

#include "./../../main_project/component.hpp"
#include "./../../main_project/component.cpp"

#include "./../../main_project/resistor.hpp"
#include "./../../main_project/resistor.cpp"

using namespace std;

int main(){
    bool pass = false;
    Circuit c{};
    
    pass |= 10e-15 == c.getValue("10u");
    pass |= 10 == c.getValue("10aksjdkjaskd");
    pass |= 0.01== c.getValue("10mlamsldkasdasd");
    pass |= 10000000 == c.getValue("10MEG");
    pass |= 202401 == c.getValue(".202401G");

    if(pass){
        cout << "SUCCESS";
    }else{
        cout << "FAIL";
    }
    cout << endl;
}