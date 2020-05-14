#include <iostream>
#include <Eigen/Dense>
#include <vector>

#include "circuit.hpp"
#include "component.hpp"

#include "voltageSource.hpp"
#include "currentSource.hpp"
#include "resistor.hpp"
#include "capacitor.hpp"
#include "inductor.hpp"

using namespace std;
using namespace Eigen;

Circuit::Circuit()
{
    currentTime = 0;
    timeStep = 0.1; // in seconds
    highestNodeNumber = 0;
    hasNonLinear = false;
}

//dealocate raw pointers
Circuit::~Circuit()
{   
    //could just use component code below but decided to use
    //the other vectors as we might get rid of the component vector
    //later on 

    for(auto comp : components){
        delete comp;
    }
    // components.clear();
    // for(auto vs : voltageSources){
    //     delete vs;
    // }
    // voltageSources.clear();
    // for(auto cs : currentSources){
    //     delete cs;
    // }
    // currentSources.clear();
    // for(auto g : conductanceSources){
    //     delete g;
    // }
    // conductanceSources.clear();
}

string Circuit::getTitle() const{
    return title;
}
void Circuit::setTitle(string _title){
    title = _title;
}

int Circuit::getHighestNodeNumber() const{
    return highestNodeNumber;
}
void Circuit::setHighestNodeNumber(int _highestNodeNumber){
    highestNodeNumber = _highestNodeNumber;
}

float Circuit::getCurrentTime() const{
    return currentTime;
}
void Circuit::setCurrentTime(float _currentTime){
    currentTime = _currentTime;
}

float Circuit::getSimulationTime() const{
    return simulationTime;
}
void Circuit::setSimulationTime(float _simulationTime){
    simulationTime = _simulationTime;
}

float Circuit::getTimeStep() const{
    return timeStep;
}
void Circuit::setTimeStep(float _timeStep){
    timeStep = _timeStep;
}

bool Circuit::hasNonLinearComponents() const{
    return hasNonLinear;
}
void Circuit::setHasNonLinearComponents(bool _hasNonLinearComponents){
    hasNonLinear = _hasNonLinearComponents;
}

vector<Component*>& Circuit::getVoltageSourcesRef(){
    return voltageSources;
}
vector<Component*>& Circuit::getCurrentSourcesRef(){
    return currentSources;
}
vector<Component*>& Circuit::getConductanceSourcesRef(){
    return conductanceSources;
}

// setupA definition
void Circuit::setupA()
{
    A = MatrixXf::Zero(highestNodeNumber + voltageSources.size(), highestNodeNumber + voltageSources.size());
    vector<int> nodes{};

    //constructing conductance part
    for (const auto &comp : conductanceSources)
    {
        const float conductance = comp->getConductance();
        nodes = comp->getNodes();

        // I had to change the algorithm to allow for node1 to be 0
        // Doing it this way also allows for multiple nodes per component
        // This code would get much cleaner if we have a node input to the getConductnace method to return a positive or negative depending on the node order
        // But that's just a thought for the future

        // Isn't loop less efficient than using if statements? (Main objectives of LTS_V2 are accuracy and efficiency)
        // => Second loop will face multiple scenarios when we just continue. This is wasted time. Old method would just use two if statements with no going in circles (loop)
        // Not really significant for small circuits that don't consider nonlinear components
        // but could become significant for very large circuits and if we have to recompute A (kinda depends on the method we choose) for nonlinear components
        // For flexibility: I still cannot think of an example where there is a 3+ terminal device that would work with this exact algorithm (if there is, this would make the code even less efficient)
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i] == 0)
                continue;
            A(nodes[i] - 1, nodes[i] - 1) += conductance;
            for (int j = 0; j < nodes.size(); j++)
            {
                if (i == j || nodes[j] == 0)
                    continue;
                A(nodes[i] - 1, nodes[j] - 1) -= conductance;
            }
        }

        // code for debugging changes in A per itteration
        // IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
        // cout << A.format(CleanFmt) << endl << endl;
    }

    //voltage part
    for (int i{}; i < voltageSources.size(); i++)
    {
        const auto &vs = voltageSources.at(i);

        nodes = vs->getNodes();
        const int node1 = nodes.at(0);
        const int node2 = nodes.at(1);

        // I think we should consider the look at node functionallity so taht we can also implement this as a loop like above
        // for now the easiest thing to do is just write to if statements, given our current structure
        // I think the look at function would also help with the dependant sources problem with this implementation
        if (node1 != 0)
        {
            A(node1 - 1, highestNodeNumber + i) = 1;
            A(highestNodeNumber + i, node1 - 1) = 1; //different when dealing with dependent sources
        }

        if (node2 != 0)
        {
            A(node2 - 1, highestNodeNumber + i) = -1;
            A(highestNodeNumber + i, node2 - 1) = -1; //different when dealing with dependent sources
        }

        // code for debugging changes in A per itteration
        // IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
        // cout << A.format(CleanFmt) << endl << endl;
    }
}

MatrixXf Circuit::getA() const
{
    return A;
}

void Circuit::computeA_inv(){
    A_inv = A.inverse();
}

MatrixXf Circuit::getA_inv() const{
    return A_inv;
}

// setupB definition
void Circuit::adjustB()
{
    b = VectorXf::Zero(highestNodeNumber + voltageSources.size());

    //adding currents
    for (const auto &cSource : currentSources)
    {
        vector<int> nodes = cSource->getNodes();
        const int node1 = nodes.at(0);
        const int node2 = nodes.at(1);

        // same suggestion as above, would make the whole code base more flexible to new componetns
        if (node1 != 0)
        {
            b(node1 - 1) += cSource->getCurrent();
        }

        if (node2 != 0)
        {
            b(node2 - 1) -= cSource->getCurrent();
        }

        // code for debugging changes in A per itteration
        // IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
        // cout << b.format(CleanFmt) << endl
        //      << endl;
    }

    //adding voltages
    for (int i{highestNodeNumber}, j{}; i < highestNodeNumber + voltageSources.size(); i++, j++)
    {
        b(i) = voltageSources.at(j)->getVoltage();
    }
}

VectorXf Circuit::getB() const
{
    return b;
}

void Circuit::setupXMeaning(){
    xMeaning.clear();

    for(int i{1}; i<=highestNodeNumber; i++){
        xMeaning.push_back("v_" + to_string(i));
    }
    for(const auto &vs : voltageSources){
        xMeaning.push_back("I_V" + vs->getName());
    }
}

vector<string> Circuit::getXMeaning() const{
    return xMeaning;
}

void Circuit::computeX(){
    x = A_inv * b;
}

VectorXf Circuit::getX() const{
    return x;
}

template <class comp>
void Circuit::addComponent(string name, vector<string> args){
    vector<float> extraInfo; // extra info will be passed to constructors and used if necessary
    // we can change it to a vector of strings if we need non float data later on
    extraInfo.push_back(getTimeStep());//extraInfo[0] is timeStep of circuit
	comp* newComp = new comp(name, args, extraInfo);
	vector<int> types = newComp->getTypes();
	for(int type : types){
		switch (type)
		{
		case 0:
			conductanceSources.push_back(newComp);
			break;
		case 1:
			voltageSources.push_back(newComp);
			break;
		case 2:
			currentSources.push_back(newComp);
			break;
		case 4:
			timeUpdatables.push_back(newComp);
			break;
		default:
			break;
		}
	}
    components.push_back(newComp);
}

void Circuit::updateComponents(float time){
    for(auto comp : timeUpdatables){
        comp->updateVals(time);
    }
}