# Comparison of different numerical integration techniques that could be used to create companion model for transient analysis
### Need to choose minimum one but maybe two (If choose two, need to write algorithm that decides which one to use on a per case basis)

**Main reference used (assume everything from here if not specified otherwise):** Charles A. Thompson in 1992 --> <https://docs.lib.purdue.edu/cgi/viewcontent.cgi?article=1301&context=ecetr>
**2nd Source (used when 2nd in brackets):** eCircuit Center --> <http://www.ecircuitcenter.com/SpiceTopics/Transient%20Analysis/Transient%20Analysis.htm>

The methods below become more accurate as the time step decreases (see truncation error). However, a smaller time step means that more calculations need to be done and hence the algorithm will take longer. Need to find a good balance. SPICE can change time step dynamically to achieve good balance between time and accuracy.
Remark about choosing time step: "choose a time step which would give a decent resolution of the time: response (usually
at least one half the value of the smallest eigenvalue (time constant) of the circuit to be
analyzed)" (page 33, Charles A. Thompson)

*Self-starting* means that the method can be used from time step 0. If the method is not self-starting, we need to use another method to obtain the first few values. Either through solving differential equations or through using one of the self-starting methods.

The *truncation error* (difference between the exact solution and the approximation due to the truncation of the series after the nth position) associated with each integration step is described using Big O notation. Here, this will describe how the truncation error scales with increasing time step h. This only describes the importance of the time step on the truncation error of a particular method but not how the relative error compares between different numerical integration methods.

The *absolute error* is the absolute difference between the analytic and the numerical integration method solution

*Numerically stable* means that the total error (produced by summation of the local truncation errors) decays with time
**Regions of stability:** For a more detailed analysis of stability that includes the set of parameter values for which a particular method is numerically stable, see page 20-. This might be useful when we decide to use more than one integration method dynamically and want to use the specified parameters (e.g. time step) to determine which method to use to achieve stability.

*Memory requirements*: 2nd order methods require the storage of about twice the amount of data as 1st order methods. However, not a massive problem with modern computers (The reference thesis was written in the 90s).

## Forward Euler
- Integral is approximated by summing successive polygonal areas
- Approximation greater than the actual integral
- Self-starting 
- Order of approximation = 1
- Truncation error: O(h^2)
- Less accurate/less used than Backward Euler (2nd Source)
- Project description on Blackboard seems to suggest this method by indicating to replace inductor with simple current source and capacitor with simply voltage source
- bad accuracy

---

## Backward Euler 
- Integral is approximated by summing successive polygonal areas
- Approximation less than the actual integral
- Self-starting 
- Order of approximation = 1
- Truncation error: O(h^2)
- more accurate than Forward Euler but still not very accurate

---

## Trapezoidal Rule
- Combination of Forward- and Backward Euler (uses fact that one is greater and one less than actual integral)
- "the most widely used integration scheme for circuit analysis" (page 10, Charles A. Thompson)
- Integral is approximated by summing successive trapezoidal regions
- Self-starting 
- Order of approximation = 1
- Truncation error: O(h^3)
- excellent stability region
- decent accuracy (better than Euler)

---

## Simpson's Rule
- Integral is approximated using a second-order parabolic curve
- Not self-starting
- Order of approximation = 2
- Truncation error: O(h^5)
- tiny stability region (would need to check if in region before using)
- very accurate

---

## Parabolic (3rd order Adams-Moulton predictor formula)
- Integral is approximated using a second-order parabolic curve
- Not self-starting 
- Order of approximation = 2
- Truncation error: O(h^4)
- decent but not huge stability region (best to check if in region before using)
- best accuracy of methods presented here

---

## Gear's 2nd Order (Backward differentiation formula)
- Integral is approximated using derivatives that form the second order function
- Not self-starting 
- Order of approximation = 2
- Truncation error: O(h^3)
- excellent stability region
- good accuracy


## Evaluation:
The project description on Blackboard seems to suggest Forward Euler: "*inductors are treated as current sources* since their current cannot change instantaneously and it is effectively fixed during each simulation iteration. Similarly,
*capacitors are treated as voltage sources*".
However, this seems to be the least accurate method possible. Hence, I would suggest to mention this suggestion in the report but justify why we decided to use a more accurate (slightly more complex) method. It however also means, that going all the way to second order approximations is not expected and hence should only be done if we have plenty of time left and want to go a step further (after we have non-linear components working). In this case, I would suggest combining our initial first order method with a second order method to achieve improved accuracy.

**Suggested first order method: Trapezoidal Rule**
Suggested second order method: Parabolic (only go here if everything works and we have time left in the end)