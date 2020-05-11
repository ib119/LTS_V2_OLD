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

---

## Transient Analysis (eCircuit)
Very basic and simply to understand explanation how to use backward-Euler and MNA to perform transient analysis. This avoids the having to solve differential equations and is similar to how SPICE does it (probably a little simplified).
The results look very promising (comparison with LTSpice transient simulation). A screenshot of the comparison is provided in the research folder.
<http://www.ecircuitcenter.com/SpiceTopics/Transient%20Analysis/Transient%20Analysis.htm>

---

## A Study of Numerical Integration Techniques for use in the Companion Circuit Method of Transient Circuit Analysis
Harder to understand but more detailed than eCircuit page above. Also seems like a good source to use.
Includes companion circuit models produced by different integration techniques. Also gives a detailed comparison of integration techniques (Will need to justify why we choose a particular one).
Page 27 (pdf page 37) gives the backward-Euler companion circuit for an inductor (eCircuit only gave the one for a capacitor). On this page, there are also all kinds of other companion circuits.
<https://docs.lib.purdue.edu/cgi/viewcontent.cgi?article=1301&context=ecetr>

---

## Inside Spice
A good book that explains methods used in SPICE. Especially useful for Newton-Raphson with non-linear components and for dynamic time step control (could be added in end if want greater accuracy while being fast).
<https://idoc.pub/download/kielkowski-inside-spice-d2nv6ogoxy4k>