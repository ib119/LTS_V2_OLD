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

#include "inputModule/input.hpp"

using namespace std;


int main(){
    Circuit c{};
    readSpice(c, cin);
}

