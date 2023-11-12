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
const std::vector<color_vec> colorPalette = {   
                                                // Single color 
                                                color_vec{red},     
                                                color_vec{sodium},  
                                                color_vec{orange},  
                                                // color_vec{yellow},  
                                                color_vec{gold},    
                                                color_vec{white},   
                                                color_vec{cyan},    
                                                color_vec{blue},    
                                                color_vec{purple},  
                                                color_vec{magenta}, 
                                                color_vec{pink},    
                                                // color_vec{green},        
                                                
                                                // Color + White
                                                color_vec{white, red},  
                                                color_vec{white, sodium},
                                                // color_vec{white, orange},
                                                // color_vec{white, yellow},
                                                // color_vec{white, gold},
                                                // color_vec{white, white},
                                                color_vec{white, cyan},
                                                color_vec{white, blue},
                                                color_vec{white, purple},
                                                color_vec{white, magenta},
                                                color_vec{white, pink},
                                                // color_vec{white, green}
                                                
                                                // Color couples
                                                color_vec{cyan, magenta},
                                                color_vec{gold, red},
                                                color_vec{gold, orange},
                                                color_vec{gold, sodium},
                                                color_vec{red, blue},
                                                color_vec{red, purple},
                                                color_vec{orange, purple},
                                                color_vec{blue, purple},
                                                color_vec{pink, purple},
                                                color_vec{cyan, pink},
                                                color_vec{cyan, magenta},
                                                color_vec{cyan, red}

                                                };


// Music Emulator
#define BPM 120          // BPM
#define BREAKDuration 16  // beats
#define DROPDuration  32 // beats

// -- CONFIG ------------------------------------------------------------
#define     MAX_CONT_FLASH      120000          // 120000
#define     TEMPO_ANIM_CHANGE   10000          // 240000
#define     MASTERDIMMER        1.0             //fraction --> must be decimal (literal float) !!!