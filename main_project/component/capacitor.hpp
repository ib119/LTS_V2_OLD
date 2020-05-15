#ifndef CAPACITOR_HPP
#define CAPACITOR_HPP

#include "component.hpp"

class Capacitor: public Component{
private:
	float capacitance;
	float comp_current;//Value of the current source in the companion model
	float comp_voltage; //value of the voltage across the capacitor
	float comp_conductance;//Conductance of the resistor in the companion model
	float prev_voltage; //Voltage across the Capacitor in the previous iteration.
	float prev_current;
	float prev_total_current;

public:
	Capacitor(string name, vector<string> args, vector<float> extraInfo);
	Capacitor(string _name, float l, int n1, int n2, float timeStep, int order);
	~Capacitor() = default;
	float getConductance() const override;
	vector<int> getNodes() const ;
	float getCurrent() const override;
	float getTotalCurrent(float voltage, int order = 1) override;
	void updateVals(float newVoltage, float newCurrent, int order) override; //Called at the end of every iteration, after calculating node voltages and component currents.
};

#endif
