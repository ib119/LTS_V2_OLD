#ifndef INDUCTOR_HPP
#define INDUCTOR_HPP

#include "component.hpp"

class Inductor: public Component{
private:
	float inductance;
	float comp_current;//Value of the current source in the companion model
	float comp_voltage; //value of the voltage across the inductor
	float comp_conductance;//Conductance of the resistor in the companion model
	float prev_voltage; //Voltage across the inductor in the previous iteration.
	float prev_current;
	float prev_total_current;

public:
	Inductor(string name, vector<string> args, vector<float> extraInfo);
	Inductor(string _name, float l, int n1, int n2, float timeStep, int order);
	~Inductor() = default;
	float getConductance() const override;
	vector<int> getNodes() const ;
	float getCurrent() const override;
	float getTotalCurrent(float voltage, int order = 1) override;
	void updateVals(float newVoltage, float newCurrent, int order) override; //Called at the end of every iteration, after calculating node voltages and component currents.
};

#endif
