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
    
    float x = c.getValue("10f");
    pass &= (float)1e-14 == x;
    x = c.getValue("10aksjdkjaskd");
    pass &= (float)10.0 == x;
    x = c.getValue("10mlamsldkasdasd");
    pass &= abs((float)0.01 - x) < 0.00001; // has to be this way due to how binary binary numbers can't represent 0.01 exactly
    x = c.getValue("10MEG");
    pass &= (float)10000000 == x;
    x = c.getValue(".202401G");
    pass &= (float)202401000 == x;

    if(pass){
        cout << "SUCCESS";
    }else{
        cout << "FAIL";
    }
    cout << endl;
}