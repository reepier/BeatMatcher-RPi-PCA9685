#pragma once
#include <string>

#include <platform.h>

// runtime flags for main functions
extern bool b_BALISE;       //TRUE: console displays balise (without curses) 
extern bool b_NO_MUSIC;    //TRUE: music input & processing ; FALSE: music signal emulation 
extern bool b_NO_LED;      //TRUE: sends PCA9685 commands ; FALSE: ignores PCA9685 commands 
extern bool b_CURSES;       //TRUE : use curses HMI ; FALSE : use simple console output

extern bool b_test;
extern std::vector<std::string> vec_anim_id;

// precompiler flags
/*  
    Uncomment the following line to compile a DEBUG version (no DMX Rx function,
    Serial plotter activated). Comment out the following line to reverse to
    "NORMAL MODE" (DMX Rx activated, Serial plotter unavailabe)
*/