#pragma once
#include <string>
#include <platform.h>

#include "commonTypes.h"

// -- CONFIG ------------------------------------------------------------
#define FRATE   40          //Hz program main frame rate

// runtime flags for main functions -------------------------------------
extern bool b_BALISE;       //TRUE: console displays balise (without curses) 
extern bool b_NO_MUSIC;    //TRUE: music input & processing ; FALSE: music signal emulation 
extern bool b_NO_LED;      //TRUE: sends PCA9685 commands ; FALSE: ignores PCA9685 commands 
extern bool b_CURSES;       //TRUE : use curses HMI ; FALSE : use simple console output

extern bool b_test;
extern std::vector<std::string> vec_anim_id;


// Animator ColorPalette
const std::vector<color_vec> colorPalette = {color_vec{white, black},
                                              color_vec{red, blue},
                                              color_vec{red, gold},
                                              color_vec{purple, cyan}};


// Music Emulator
#define BPM 120          // BPM
#define BREAKDuration 16  // beats
#define DROPDuration  32 // beats

// -- CONFIG ------------------------------------------------------------
#define     MAX_CONT_FLASH      120000          // 120000
#define     TEMPO_ANIM_CHANGE   10000          // 240000
#define     MASTERDIMMER        1.0             //fraction --> must be decimal (literal float) !!!