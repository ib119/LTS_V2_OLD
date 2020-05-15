#!/bin/bash

g++ -o main -I./ main.cpp circuit/circuit.cpp component/component.cpp component/resistor.cpp component/capacitor.cpp component/inductor.cpp component/voltageSource.cpp component/currentSource.cpp component/waveform.cpp input/input.cpp output/output.cpp output/linearAnalysis.cpp