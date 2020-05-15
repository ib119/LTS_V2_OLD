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

## Third Call (13/05/2020)

We opened the call talking more about the implenmentation of capacitors and inductors again. We decided to go with a method more similar to the second option as shown above. The reason for this was that it seemed to make more sense for the component to control it's own values. This would allow us to take a more general approach to how the circuit class deals with components, as the circuit would only have to know if the component acts as a current source, voltage source, conducnatnce source, or several of them. With this set up as such we can then let components dictate how they manage their values independantly.

We also discuessd the method of development we are planning on taking. We think what we feel more comfortable with is AGILE development. Building something basic that works, and improvingit. Because of this we have already started considereng different areas our code structure that could be modified in future to add more functionality. We're also trying to take an approach which allows for scaling to be implmented with more ease.

The tasks we are looking at in the near future is to complete the input system, the capacitor and inductor system, and the matrix system. After this we're planning on building a good testing structure before moving on to more complex tasks.

One idea we were looking at for the future when condiering more complex components such as non-linear ones is how we are planning on implementing them. We have two main ideas moving forward.

1) Implenting them using their IV characteristics and using Newton method to solve the simultaneous equationsof each equation of nodal analysis

2) Using Newton method to find the operating point of a small signal equivalent model of each nonlinear component and then solving the system as a linear model

# A few days later

Since the last log, we've made a few key changes

1) We've separated our project into modules, this will allow us to have more flexability later on when we start adding feature. It also lets us consider each module as an independant library which simply comuicate with each other, and for the most part, are completely independant.

2) We've added CMake to our project, that way we can compile our projects quicker without having to worry about the increasing number of files that we are generating

3) We've added inductors and capacitors to our project, and they seem to be working proerperly

4) We have voltage and current sources that change over time. With this, we feel like we have just about implemented the minumum requirements needed to pass the module.

Looking into the near future, our main priorities are to implement a timing system we can use to test the efficiency of our code. So far it has been quite fast, but as we haven't yet implemented a timer, we can't be completely sure.

Since we feel like we have time, and could not find a good reason to choose one method over the other, we are plannig on implementing both models mentioned above for non linear components. With the added timing system we will then test for efficiency. While trying to produce equal accuracy with both methods. The modular nature of our software design allows us to easily swap in both methods with very minor changes. Quick prototyping then becomes easy and straight forward.