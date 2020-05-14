#ifndef ENUMS
#define ENUMS

/*
    A collection of enums used in this project
*/
struct componentType{
    enum 
    { 
        conductanceSource = 0,
        voltageSource = 1, 
        currentSource = 2,
        vcUpdatable = 3,
        timeUpdatable = 4 
    };
};

#endif