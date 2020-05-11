# Personal Log

## First Call (08/05/2020)

We used the first call to break down what tools we were going to use to organize ourselves "git-hub projects", and set up some basic tasks there to keep organized.

We shared some useful links with eachother, we made a basic overview of how the project was going to be broken down, and gave ourselves until monday to do some research on the subjects we need to cover. Namely how to do nodal analysis with matrixes, aswell as some basic thought into how to create a data structure for the circuits.

## Second Call (12/05/2020)

We used the call today to discuss the methods of solving our circuits. We discussed what we each researched about different solutions and came to a general understanding of how we're going to solve for the nodal voltages of a given circuit.

We also gave a more detailed look at what each of our classes were going to comprise of. That is what is necessary for the circuit class, the components class, and all of this children of the component class.

In terms of capacitors and inductors we still have two main ideas about how we're going to handle them. We're going to simplify them down to equivalent models with resisitors and V/I sources, however have two ideas about the implementation:

1) We have the component already converted to the relevant "sub components" when reading form the input SPICE file. This involves storing the spice file for regenerating circuit, or having the circuit remember what the main component was before breaking it down. It also needs to have the circuit store previous values of the voltage across the component.

2) We have the component simulate having two sub components. Storing the presets for both in the Capacitor class itself, and switching its behaviour when necessary. This involves having the presets for the component be set within the component instead of the circuit, and having the previous voltages updated within thi class instead of the circuit.

The main difference between the two methods is that one has "history" and "presets" stored in the circuit, whereas the other one stores them in the component.

We also concluded that the library we would use for the matrix manipulation is Eigen as it provided evidence of being faster for our specific needs.