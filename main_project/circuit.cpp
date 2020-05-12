#include <iostream>
#include <Eigen/Dense>

#include "circuit.hpp"

using namespace std;
using namespace Eigen;

Circuit::Circuit()
{
    time = 0;
    timeStep = 0.1; // in seconds
    highestNodeNumber = 0;
}

Circuit::~Circuit()
{
    //if we use vectors of raw pointer, this must delete them
    //if we change to smart pointers, deletion will be done automatically by the pointer
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

MatrixXf Circuit::getA()
{
    return A;
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

MatrixXf Circuit::getB()
{
    return b;
}