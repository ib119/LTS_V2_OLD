# List of linear algebra libraries for C++
# These are all potential candidates but still need to be evaluated based on performance tests (Need to be able to create and calculate inverse of 100000+ matrices efficiently)
# All of the ones listed below already fullfil the first requirement: They are free. Also, they are widely used (big community) and are said to be efficient.


## Armadillo
Main website + documentation:
<http://arma.sourceforge.net/>

**Important:**
- "As Armadillo is a template library, we strongly recommend to enable optimisation when compiling programs (eg. when compiling with GCC or clang, use the -O2 or -O3 options)"
e.g. => *g++ example.cpp -o example -O2 -larmadillo*
- Insert *#define ARMA_NO_DEBUG* at top of program once everything is tested to maximize speed (e.g. disables bound checking)
- https://stackoverflow.com/questions/17940721/armadillo-c-lu-decomposition
---

## Eigen 3
Main website (get zip download from here):
<http://eigen.tuxfamily.org/index.php?title=Main_Page>

Documentation:
<https://eigen.tuxfamily.org/dox/GettingStarted.html>

**Important:**
- Need to compile using: *g++ -I /path/to/eigen my_program.cpp -o my_program*

---

## MTL4 => First two are more commonly used (skip testing this one as takes to much time)
Main website (quite useless -> better to go directly to documentation below):
<https://www.simunova.com/de/mtl4/>

Documentation:
<http://old.simunova.com/docs/mtl4/html/index.html>


## Comparison Armadillo and Eigen3
- Armadillo has cleaner syntax and is easier to use
- Both are very commonly used and hence have lots of documentation and support available