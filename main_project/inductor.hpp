#ifndef inductor_hpp
#define inductor_hpp

class Inductor: public Component{
private:
	float inductance;
	float comp_current;//Value of the current source in the companion model
	float comp_conductance;//Conductance of the resistor in the companion model
	float voltage; //Voltage across inductor
	float prev_voltage; //Voltage across the inductor in the previous iteration.
	float current; 
	float prev_current;

public:
	Inductor(float l, int n1, int n2, float timeStep, int order);
	~Inductor();
	float getConductance() override;
	vector<int> getNodes();
	float getCurrent() override;
	void updateVals(int order); //Called at the end of every iteration, after calculating node voltages and component currents.




#endif
