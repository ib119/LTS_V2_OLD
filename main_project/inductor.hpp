#ifndef inductor_hpp
#define inductor_hpp

#include "circuit.hpp"
class Inductor: public Component{
private:
	float inductance;
	float comp_current;//Value of the current source in the companion model
	float comp_conductance;//Conductance of the resistor in the companion model
	float prev_voltage; //Voltage across the inductor in the previous iteration.
	float prev_current;

public:
	Inductor(string _name, float l, int n1, int n2, float timeStep, int order);
	~Inductor();
	float getConductance() const override;
	vector<int> getNodes() const ;
	float getCurrent() const override;
	void updateVals(float voltage, float current,int order); //Called at the end of every iteration, after calculating node voltages and component currents.


};

#endif
