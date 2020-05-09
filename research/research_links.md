# Some useful links regarding conductance matrices 

## “SPICE algorithms and internals” by Paul D. Mitcheson
Basic/easy to understand introduction how SPICE works through conduction matrices and Newton-Raphson method.

<http://www3.imperial.ac.uk/pls/portallive/docs/1/56133736.PDF>

---

## “In a Nutshell: How SPICE Works”
Very good reference that tells you quickly how SPICE does what. This can then be used to look it up in more detail somewhere else.

<http://www.emcs.org/acstrial/newsletters/summer09/HowSpiceWorks.pdf>

---

## An Algorithm for Modified Nodal Analysis (MNA)
A usable (little chaotic) explanation of how MNA works and how to obtain it algorithmically. MNA is used by SPICE as it can deal with voltage sources. Voltage sources cause a problem with conventional nodal analysis due to infinite conductance. 
Also includes reactive components (explanation even more chaotic…)

<https://lpsa.swarthmore.edu/Systems/Electrical/mna/MNA1.html>

---

## HELM Math by Nucinkis (From page 39 – actual pdf page = 41)
Easy to understand mathematical explanation of Newton-Raphson method
(For quick circuit analysis application example, see “SPICE algorithms and internals” above)

<http://nucinkis-lab.cc.ic.ac.uk/HELM/HELM_Workbooks_11-15/WB12-all.pdf>

---

## Spice source File Breakdown
Explains how source files work for spice files

<https://www.cpp.edu/~prnelson/courses/ece220/220-spice-notes.pdf>

---

## Techniques for circuit simulation
Tons of information about circuit simulation in lecture slide format. Start reading from pdf page 37 (Or skip further as MNA is explained better in link above). Also ignore STA analysis as it is less efficient than MNA.
Goes through topics such as Newton-Raphson method for non-linear components and transient analysis with capacitors.

<https://www.ee.iitb.ac.in/~sequel/circuit_sim_1.pdf>